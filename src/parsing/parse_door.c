/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:52:15 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:46:47 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_door(t_data *cub3d, int x, int y)
{
	t_door	*door;

	if (cub3d->map.door_count >= MAX_DOORS)
		return ;
	door = &cub3d->map.doors[cub3d->map.door_count];
	door->x = x;
	door->y = y;
	door->openness = 0.0;
	door->opening = 0;
	cub3d->map.grid[y][x] = '2';
	cub3d->map.door_count++;
}
