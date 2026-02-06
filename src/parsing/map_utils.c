/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:52:20 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 20:00:47 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	len = ft_tablen(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	while (i < len)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[len] = line;
	new_tab[len + 1] = NULL;
	free(tab);
	return (new_tab);
}

static int	map_linelen(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n' && s[i] != '\r')
		i++;
	return (i);
}

void	add_map_line(t_data *cub3d, char *line)
{
	char	*dup;
	int		len;

	len = map_linelen(line);
	dup = ft_substr(line, 0, len);
	if (!dup)
		return ;
	cub3d->map.grid = ft_tabadd(cub3d->map.grid, dup);
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
	i = 0;
	while (i < width)
	{
		if (i < len && line[i] != '\n' && line[i] != '\r')
		{
			if (line[i] == '\t')
				new_line[i] = ' ';
			else
				new_line[i] = line[i];
		}
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[width] = '\0';
	return (new_line);
}

void	normalize_map_grid(t_data *cub3d)
{
	int		max_width;
	int		y;
	int		len;
	char	*tmp;

	y = 0;
	max_width = 0;
	while (cub3d->map.grid[y])
	{
		len = ft_strlen(cub3d->map.grid[y]);
		if (len > max_width)
			max_width = len;
		y++;
	}
	y = 0;
	while (cub3d->map.grid[y])
	{
		tmp = normalize_map_line(cub3d->map.grid[y], max_width);
		free(cub3d->map.grid[y]);
		cub3d->map.grid[y] = tmp;
		y++;
	}
	cub3d->map.width = max_width;
}
