/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:02 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:03 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_texture(void *mlx_ptr, char *path, t_img *tex)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
		return (1);
	tex->pixels_ptr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->pixels_ptr)
		return (1);
	return (0);
}

int	load_all_textures(t_data *cub3d)
{
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.north,
			&cub3d->map.texture.north))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.south,
			&cub3d->map.texture.south))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.west,
			&cub3d->map.texture.west))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.east,
			&cub3d->map.texture.east))
		return (1);
	return (0);
}
