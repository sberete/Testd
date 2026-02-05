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

static char	*next_trimmed_line(int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim_all(line);
		free(line);
		if (trimmed && !is_empty(trimmed))
			return (trimmed);
		free(trimmed);
		line = get_next_line(fd);
	}
	return (NULL);
}

static int	parse_lines(int fd, t_data *cub3d, bool *map_started)
{
	char	*trimmed;

	trimmed = next_trimmed_line(fd);
	while (trimmed)
	{
		if (!*map_started && is_map_line(trimmed))
		{
			*map_started = true;
			add_map_line(cub3d, trimmed);
		}
		else if (*map_started && process_map_line(cub3d, trimmed))
			return (free(trimmed), 1);
		else if (!*map_started && process_line_before_map(cub3d, trimmed))
			return (free(trimmed), 1);
		free(trimmed);
		trimmed = next_trimmed_line(fd);
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
