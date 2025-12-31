/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:52 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:53 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	compute_perp_dist(t_data *cub3d, t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - cub3d->player.pos.x + (1 - ray->step_x) / 2)
			/ ray->ray_dir_x);
	return ((ray->map_y - cub3d->player.pos.y + (1 - ray->step_y) / 2)
		/ ray->ray_dir_y);
}

void	init_ray(t_data *cub3d, int x, t_ray *ray)
{
	double	camera_x;

	camera_x = 2.0 * x / (double)WIDTH - 1.0;
	ray->ray_dir_x = cub3d->player.dir.x + cub3d->player.plane.x * camera_x;
	ray->ray_dir_y = cub3d->player.dir.y + cub3d->player.plane.y * camera_x;
	ray->map_x = (int)cub3d->player.pos.x;
	ray->map_y = (int)cub3d->player.pos.y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	init_step(t_data *cub3d, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cub3d->player.pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cub3d->player.pos.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cub3d->player.pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cub3d->player.pos.y)
			* ray->delta_dist_y;
	}
}
