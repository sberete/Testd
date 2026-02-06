/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:37 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:49:38 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(t_data *cub3d, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;
	t_door	*door;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= cub3d->map.height || map_x < 0
		|| map_x >= cub3d->map.width)
		return (1);
	cell = cub3d->map.grid[map_y][map_x];
	if (cell == '1' || cell == ' ' || cell == '\t')
		return (1);
	if (cell == '2')
	{
		door = find_door(&cub3d->map, map_x, map_y);
		if (door && door->openness < 0.95)
			return (1);
	}
	return (0);
}
