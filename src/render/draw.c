/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:52:34 by sberete           #+#    #+#             */
/*   Updated: 2025/11/22 16:36:53 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->pixels_ptr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static void	draw_floor_ceiling(t_data *cub3d)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&cub3d->img, x, y, cub3d->map.color.ceiling_rgb);
			else
				put_pixel(&cub3d->img, x, y, cub3d->map.color.floor_rgb);
			x++;
		}
		y++;
	}
}

void	draw_scene(t_data *cub3d)
{
	memset(cub3d->img.pixels_ptr, 0, cub3d->img.line_len * HEIGHT);
	draw_floor_ceiling(cub3d);
	update_doors(&cub3d->map);
	draw_scene_3d(cub3d);
	draw_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx.ptr, cub3d->mlx.win, cub3d->img.img_ptr,
		0, 0);
}
