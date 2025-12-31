/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:40 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:49:41 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_data *cub3d, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = cub3d->player.pos.x + dir_x * speed;
	new_y = cub3d->player.pos.y + dir_y * speed;
	if (!is_wall(cub3d, new_x, cub3d->player.pos.y))
		cub3d->player.pos.x = new_x;
	if (!is_wall(cub3d, cub3d->player.pos.x, new_y))
		cub3d->player.pos.y = new_y;
}

void	rotate_player(t_data *cub3d, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub3d->player.dir.x;
	old_plane_x = cub3d->player.plane.x;
	cub3d->player.dir.x = cub3d->player.dir.x * cos(angle) - cub3d->player.dir.y
		* sin(angle);
	cub3d->player.dir.y = old_dir_x * sin(angle) + cub3d->player.dir.y
		* cos(angle);
	cub3d->player.plane.x = cub3d->player.plane.x * cos(angle)
		- cub3d->player.plane.y * sin(angle);
	cub3d->player.plane.y = old_plane_x * sin(angle) + cub3d->player.plane.y
		* cos(angle);
}
