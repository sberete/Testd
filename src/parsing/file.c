/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:58:44 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 22:17:02 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	process_line_before_map(t_data *cub3d, char *line)
{
	if (parse_cub_line(cub3d, line))
		return (1);
	return (0);
}

static int	process_map_line(t_data *cub3d, char *line)
{
	if (!is_map_line(line))
		return (ft_putendl_fd("Invalid line after map", 2), 1);
	add_map_line(cub3d, line);
	return (0);
}

static void	chomp_newline(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
		s[--len] = '\0';
}

char	*next_raw_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	chomp_newline(line);
	return (line);
}
static int	is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_lines(int fd, t_data *cub3d, bool *map_started)
{
	char	*line;
	char	*trimmed;

	line = next_raw_line(fd); // -> ligne RAW
	while (line)
	{
		trimmed = ft_strtrim_all(line); // OK pour tester/traiter les headers
		if (!trimmed)
			return (free(line), 1);
		if (!*map_started)
		{
			// ignorer lignes vides AVANT map
			if (is_empty_line(trimmed))
			{
				free(trimmed);
				free(line);
				line = next_raw_line(fd);
				continue ;
			}
			// map détectée sur la ligne RAW (pas trimmed !)
			if (is_map_line(line))
			{
				*map_started = true;
				add_map_line(cub3d, line); // stocke RAW
			}
			else
			{
				// ici tu appelles ton parse header (textures/couleurs)
				if (process_line_before_map(cub3d, trimmed))
					return (free(trimmed), free(line), 1);
			}
		}
		else
		{
			// après map: ligne vide => invalide
			if (is_empty_line(trimmed))
				return (free(trimmed), free(line),
					ft_putendl_fd("Invalid empty line inside/after map", 2), 1);
			// traiter ligne de map en RAW
			if (process_map_line(cub3d, line))
				return (free(trimmed), free(line), 1);
		}
		free(trimmed);
		free(line);
		line = next_raw_line(fd);
	}
	return (0);
}

int	parse_cub_file(t_data *cub3d, char *path)
{
	int		fd;
	bool	map_started;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Cannot open .cub file", 2), 1);
	map_started = false;
	if (parse_lines(fd, cub3d, &map_started))
		return (close(fd), 1);
	close(fd);
	if (!map_started)
		return (ft_putendl_fd("No map found in .cub file", 2), 1);
	normalize_map_grid(cub3d);
	return (0);
}
