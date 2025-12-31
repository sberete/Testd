/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:52:15 by sberete           #+#    #+#             */
/*   Updated: 2025/12/27 01:50:18 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_door(t_data *cub3d, int x, int y)
{
	t_door	*door;

	door = &cub3d->map.doors[cub3d->map.door_count];
	door->x = x;
	door->y = y;
	door->openness = 0.0;
	door->opening = 0;
	cub3d->map.door_count++;
	cub3d->map.grid[y][x] = '2';
}
