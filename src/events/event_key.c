/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:10 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:11 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_data *cub3d)
{
	if (keycode == XK_Escape)
		free_all_and_exit(cub3d);
	if (keycode == XK_w)
		cub3d->player.move.forward = 1;
	if (keycode == XK_s)
		cub3d->player.move.backward = 1;
	if (keycode == XK_a)
		cub3d->player.move.left = 1;
	if (keycode == XK_d)
		cub3d->player.move.right = 1;
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 1;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 1;
	if (keycode == XK_e)
		interact(cub3d);
	return (0);
}

int	key_release(int keycode, t_data *cub3d)
{
	if (keycode == XK_w)
		cub3d->player.move.forward = 0;
	if (keycode == XK_s)
		cub3d->player.move.backward = 0;
	if (keycode == XK_a)
		cub3d->player.move.left = 0;
	if (keycode == XK_d)
		cub3d->player.move.right = 0;
	if (keycode == XK_Left)
		cub3d->player.move.rotate_left = 0;
	if (keycode == XK_Right)
		cub3d->player.move.rotate_right = 0;
	return (0);
}
