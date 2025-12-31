/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:53:18 by sberete           #+#    #+#             */
/*   Updated: 2025/11/22 16:55:30 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	render_loop(t_data *cub3d)
{
	update_player_position(cub3d);
	draw_scene(cub3d);
	return (0);
}

void	mlx_hookes(t_data *cub3d)
{
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, key_press, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, key_release, cub3d);
	mlx_hook(cub3d->mlx.win, 17, 0, free_all_and_exit, cub3d);
	mlx_hook(cub3d->mlx.win, MotionNotify, PointerMotionMask, mouse_move,
		cub3d);
	mlx_loop_hook(cub3d->mlx.ptr, render_loop, cub3d);
}
