/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:02 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:53:22 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	load_texture(void *mlx_ptr, char *path, t_img *tex)
{
	if (!path)
	{
		fprintf(stderr, "Texture path not set\n");
		return (1);
	}
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
	{
		fprintf(stderr, "Failed to load XPM: %s\n", path);
		return (1);
	}
	tex->pixels_ptr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->pixels_ptr)
	{
		fprintf(stderr, "Failed to get data addr: %s\n", path);
		return (1);
	}
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

int	parse_texture_line(t_data *cub3d, char *line)
{
	char	*key;
	char	*path;

	if (!line || ft_strlen(line) < 2)
		return (ft_putendl_fd("Invalid texture line", 2), 1);
	key = ft_substr(line, 0, 2);
	path = ft_strtrim_all(line + 2);
	if (!path || path[0] == '\0')
		return (free(key), ft_putendl_fd("Texture path missing", 2), 1);
	if (path[ft_strlen(path) - 1] == '/')
		return (free(key), free(path), ft_putendl_fd("Invalid texture path", 2),
			1);
	if (!has_xpm_extension(path))
		return (free(key), free(path), ft_putendl_fd("Texture must be .xpm", 2),
			1);
	if (!ft_strcmp(key, "NO") && !cub3d->map.path.north)
		cub3d->map.path.north = path;
	else if (!ft_strcmp(key, "SO") && !cub3d->map.path.south)
		cub3d->map.path.south = path;
	else if (!ft_strcmp(key, "WE") && !cub3d->map.path.west)
		cub3d->map.path.west = path;
	else if (!ft_strcmp(key, "EA") && !cub3d->map.path.east)
		cub3d->map.path.east = path;
	else
		return (free(key), free(path),
			ft_putendl_fd("Duplicate or invalid texture", 2), 1);
	free(key);
	return (0);
}
