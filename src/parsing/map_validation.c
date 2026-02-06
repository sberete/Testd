/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 20:51:36 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 20:01:04 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	flood_fill(t_data *cub3d, int x, int y)
{
	char	**grid;

	grid = cub3d->map.grid;
	if (x < 0 || x >= cub3d->map.width || y < 0 || y >= cub3d->map.height)
		return (0);
	if (grid[y][x] == ' ' || grid[y][x] == '\0')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill(cub3d, x + 1, y))
		return (0);
	if (!flood_fill(cub3d, x - 1, y))
		return (0);
	if (!flood_fill(cub3d, x, y + 1))
		return (0);
	if (!flood_fill(cub3d, x, y - 1))
		return (0);
	return (1);
}

int	validate_map(t_data *cub3d)
{
	t_data	copy_cub;
	char	**copy_grid;
	int		valid;

	copy_grid = ft_tabdup(cub3d->map.grid);
	if (!copy_grid)
		return (0);
	copy_cub = *cub3d;
	copy_cub.map.grid = copy_grid;
	valid = flood_fill(&copy_cub, (int)cub3d->player.pos.x,
			(int)cub3d->player.pos.y);
	free_tab(copy_grid);
	return (valid);
}
