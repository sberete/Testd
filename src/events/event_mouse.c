/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:13 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:14 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mouse_move(int x, int y, t_data *cub3d)
{
	int		delta_x;
	double	rot_speed;
	int		center_x;
	int		center_y;

	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	(void)y;
	rot_speed = 0.002;
	if (x == center_x)
		return (0);
	delta_x = x - center_x;
	if (delta_x != 0)
		rotate_player(cub3d, delta_x * rot_speed);
	mlx_mouse_move(cub3d->mlx.ptr, cub3d->mlx.win, center_x, center_y);
	return (0);
}
