/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:43 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:49:44 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_player_position(t_data *cub3d)
{
	double	move_speed;
	double	rot_speed;

	move_speed = 0.02;
	rot_speed = 0.03;
	if (cub3d->player.move.rotate_left)
		rotate_player(cub3d, -rot_speed);
	if (cub3d->player.move.rotate_right)
		rotate_player(cub3d, rot_speed);
	if (cub3d->player.move.forward)
		move_player(cub3d, cub3d->player.dir.x, cub3d->player.dir.y,
			move_speed);
	if (cub3d->player.move.backward)
		move_player(cub3d, -cub3d->player.dir.x, -cub3d->player.dir.y,
			move_speed);
	if (cub3d->player.move.left)
		move_player(cub3d, cub3d->player.dir.y, -cub3d->player.dir.x,
			move_speed);
	if (cub3d->player.move.right)
		move_player(cub3d, -cub3d->player.dir.y, cub3d->player.dir.x,
			move_speed);
}
