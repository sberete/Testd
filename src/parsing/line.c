#include "cub3D.h"

int	parse_cub_line(t_data *cub3d, char *line)
{
	char	*trimmed;
	int		res;

	if (!line || is_empty(line))
		return (0);
	trimmed = ft_strtrim_all(line);
	if (!trimmed)
		return (1);
	printf("Parsing line: '%s'\n", trimmed); // <-- DEBUG
	if (!ft_strncmp(trimmed, "NO", 2) || !ft_strncmp(trimmed, "SO", 2)
		|| !ft_strncmp(trimmed, "WE", 2) || !ft_strncmp(trimmed, "EA", 2))
	{
		res = parse_texture_line(cub3d, trimmed);
		free(trimmed);
		return (res);
	}
	if (trimmed[0] == 'F' || trimmed[0] == 'C')
	{
		res = parse_color_line(cub3d, trimmed);
		free(trimmed);
		return (res);
	}
	free(trimmed);
	return (ft_putendl_fd("Invalid line in .cub", 2), 1);
}
