/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:51:07 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:51:12 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	dda_advance_x(t_ray *ray)
{
	ray->side_dist_x += ray->delta_dist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

static void	dda_advance_y(t_ray *ray)
{
	ray->side_dist_y += ray->delta_dist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

static int	dda_hit_check(t_data *cub3d, t_ray *ray)
{
	char	cell;
	t_door	*door;

	cell = cub3d->map.grid[ray->map_y][ray->map_x];
	if (cell == '1')
		return (1);
	if (cell == '2')
	{
		door = find_door(&cub3d->map, ray->map_x, ray->map_y);
		if (!door || door->openness < 1.0)
			return (1);
	}
	return (0);
}

void	perform_dda(t_data *cub3d, t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			dda_advance_x(ray);
		else
			dda_advance_y(ray);
		if (dda_hit_check(cub3d, ray))
			break ;
	}
}
