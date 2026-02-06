/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:58:44 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 21:28:06 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	handle_before_map(char *line, char *trimmed,
								t_data *cub3d, bool *map_started)
{
	if (is_empty_line(trimmed))
		return (0);
	if (is_map_line(line))
	{
		*map_started = true;
		add_map_line(cub3d, line);
		return (0);
	}
	if (process_line_before_map(cub3d, trimmed))
		return (1);
	return (0);
}

static int	handle_map(char *line, char *trimmed, t_data *cub3d)
{
	if (is_empty_line(trimmed))
	{
		ft_putendl_fd("Invalid empty line inside/after map", 2);
		return (1);
	}
	if (process_map_line(cub3d, line))
		return (1);
	return (0);
}

static int	parse_lines(int fd, t_data *cub3d, bool *map_started)
{
	char	*line;
	char	*trimmed;

	line = next_raw_line(fd);
	while (line)
	{
		trimmed = ft_strtrim_all(line);
		if (!trimmed)
			return (free(line), 1);
		if (!*map_started)
		{
			if (handle_before_map(line, trimmed, cub3d, map_started))
				return (free(trimmed), free(line), 1);
		}
		else
		{
			if (handle_map(line, trimmed, cub3d))
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
