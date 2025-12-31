/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:39:18 by sberete           #+#    #+#             */
/*   Updated: 2025/11/19 18:43:02 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cub3d_init(t_data *cub3d)
{
	cub3d->mlx.ptr = mlx_init();
	if (!cub3d->mlx.ptr)
		mlx_failure(cub3d, "MLX init failed");
	if (load_all_textures(cub3d))
		mlx_failure(cub3d, "Texture creation failed");
	cub3d->mlx.win = mlx_new_window(cub3d->mlx.ptr, WIDTH, HEIGHT,
			cub3d->map.name);
	if (!cub3d->mlx.win)
		mlx_failure(cub3d, "Window creation failed");
	cub3d->img.img_ptr = mlx_new_image(cub3d->mlx.ptr, WIDTH, HEIGHT);
	if (!cub3d->img.img_ptr)
		mlx_failure(cub3d, "Image creation failed");
	cub3d->img.pixels_ptr = mlx_get_data_addr(cub3d->img.img_ptr,
			&cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
	mlx_hookes(cub3d);
}
