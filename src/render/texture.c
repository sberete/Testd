/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:55 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:56 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	compute_wall_x(t_data *cub3d, t_ray *ray, double perp_dist)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = cub3d->player.pos.y + perp_dist * ray->ray_dir_y;
	else
		wall_x = cub3d->player.pos.x + perp_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

t_img	*get_texture(t_data *cub3d, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (&cub3d->map.texture.west);
		else
			return (&cub3d->map.texture.east);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (&cub3d->map.texture.north);
		else
			return (&cub3d->map.texture.south);
	}
}

void	draw_tex_stripe(t_data *cub3d, t_texinfo t, t_col c)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * t.tex->height / c.line_h;
	tex_pos = (c.start - HEIGHT / 2 + c.line_h / 2) * step;
	y = c.start;
	while (y <= c.end)
	{
		tex_y = (int)tex_pos & (t.tex->height - 1);
		tex_pos += step;
		color = *(int *)(t.tex->pixels_ptr + tex_y * t.tex->line_len + t.tex_x
				* (t.tex->bpp / 8));
		put_pixel(&cub3d->img, c.x, y, color);
		y++;
	}
}
