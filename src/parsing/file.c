#include "cub3D.h"

int	parse_cub_file(t_data *cub3d, char *path)
{
	int fd;
	char *line;
	bool map_started;
	char *trimmed;

	fd = open(path, O_RDONLY);
	map_started = false;
	if (fd < 0)
		return (ft_putendl_fd("Cannot open .cub file", 2), 1);
	while ((line = get_next_line(fd)))
	{
		trimmed = ft_strtrim_all(line);
		free(line);
		if (!trimmed)
			continue ;
		if (is_empty(trimmed))
		{
			free(trimmed);
			continue ; // ignore lignes vides
		}
		if (!map_started && is_map_line(trimmed))
		{
			map_started = true;
			add_map_line(cub3d, trimmed);
		}
		else if (map_started)
		{
			if (!is_map_line(trimmed))
			{
				free(trimmed);
				close(fd);
				return (ft_putendl_fd("Invalid line after map", 2), 1);
			}
			add_map_line(cub3d, trimmed);
		}
		else
		{
			if (parse_cub_line(cub3d, trimmed))
			{
				free(trimmed);
				close(fd);
				return (1);
			}
		}
		free(trimmed);
	}
	close(fd);
	if (!map_started)
		return (ft_putendl_fd("No map found in .cub file", 2), 1);
	normalize_map_grid(cub3d);
	return (0);
}