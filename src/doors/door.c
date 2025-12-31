/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:22 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:23 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_door	*find_door(t_map *map, int x, int y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].x == x && map->doors[i].y == y)
			return (&map->doors[i]);
		i++;
	}
	return (NULL);
}

void	update_doors(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		if (map->doors[i].opening != 0)
		{
			map->doors[i].openness += map->doors[i].opening * 0.05;
			if (map->doors[i].openness >= 1.0)
			{
				map->doors[i].openness = 1.0;
				map->doors[i].opening = 0;
			}
			if (map->doors[i].openness <= 0.0)
			{
				map->doors[i].openness = 0.0;
				map->doors[i].opening = 0;
			}
		}
		i++;
	}
}

void	interact(t_data *cub3d)
{
	int		x;
	int		y;
	t_door	*door;

	x = (int)(cub3d->player.pos.x + cub3d->player.dir.x);
	y = (int)(cub3d->player.pos.y + cub3d->player.dir.y);
	door = find_door(&cub3d->map, x, y);
	if (door)
	{
		if (door->openness < 1.0)
			door->opening = 1;
		else
			door->opening = -1;
	}
}
