/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:40 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:41 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_column(t_data *cub3d, t_ray *ray, int x)
{
	double		perp;
	double		wall_x;
	int			line_h;
	t_col		c;
	t_texinfo	t;

	perp = compute_perp_dist(cub3d, ray);
	if (perp < 0.0001)
		perp = 0.0001;
	compute_draw_limits(perp, &line_h, &c.start, &c.end);
	c.x = x;
	c.line_h = line_h;
	t.tex = get_texture(cub3d, ray);
	wall_x = compute_wall_x(cub3d, ray, perp);
	t.tex_x = (int)(wall_x * t.tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
			&& ray->ray_dir_y < 0))
		t.tex_x = t.tex->width - t.tex_x - 1;
	draw_tex_stripe(cub3d, t, c);
}

void	draw_scene_3d(t_data *cub3d)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(cub3d, x, &cub3d->ray);
		init_step(cub3d, &cub3d->ray);
		perform_dda(cub3d, &cub3d->ray);
		draw_column(cub3d, &cub3d->ray, x);
		x++;
	}
}
