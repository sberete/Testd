#include "cub3D.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != '2' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'D' && line[i] != ' ' && line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

char	**ft_tabadd(char **tab, char *line)
{
	int		len;
	char	**new_tab;
	int		i;

	len = ft_tablen(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	for (i = 0; i < len; i++)
		new_tab[i] = tab[i];
	new_tab[len] = line;
	new_tab[len + 1] = NULL;
	free(tab);
	return (new_tab);
}
void	add_map_line(t_data *cub3d, char *line)
{
	cub3d->map.grid = ft_tabadd(cub3d->map.grid, ft_strdup(line));
}
char	*normalize_map_line(char *line, int width)
{
	int		len;
	char	*new_line;
	int		i;

	len = ft_strlen(line);
	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	for (i = 0; i < width; i++)
	{
		if (i < len)
		{
			if (line[i] == ' ' || line[i] == '\t')
				new_line[i] = '1';
			else
				new_line[i] = line[i];
		}
		else
			new_line[i] = '1';
	}
	new_line[width] = '\0';
	return (new_line);
}

void	normalize_map_grid(t_data *cub3d)
{
	int max_width;
	int y;
	int len;
	char *tmp;

	max_width = 0;
	for (y = 0; cub3d->map.grid[y]; y++)
	{
		len = ft_strlen(cub3d->map.grid[y]);
		if (len > max_width)
			max_width = len;
	}
	for (y = 0; cub3d->map.grid[y]; y++)
	{
		tmp = normalize_map_line(cub3d->map.grid[y], max_width);
		free(cub3d->map.grid[y]);
		cub3d->map.grid[y] = tmp;
	}
	cub3d->map.width = max_width;
}