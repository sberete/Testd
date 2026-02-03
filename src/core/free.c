/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:23:15 by sberete           #+#    #+#             */
/*   Updated: 2026/02/02 19:13:45 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(t_map *map)
{
	if (map->grid)
		free_tab(map->grid);
	free(map->doors);
	if (map->color.ceiling)
		free(map->color.ceiling);
	if (map->color.floor)
		free(map->color.floor);
	if (map->path.east)
		free(map->path.east);
	if (map->path.north)
		free(map->path.north);
	if (map->path.west)
		free(map->path.west);
	if (map->path.south)
		free(map->path.south);
}

void	free_all(t_data *cub3D)
{
	if (cub3D->mlx.win)
		mlx_destroy_window(cub3D->mlx.ptr, cub3D->mlx.win);
	if (cub3D->img.img_ptr)
		mlx_destroy_image(cub3D->mlx.ptr, cub3D->img.img_ptr);
	if (cub3D->map.texture.north.img_ptr)
		mlx_destroy_image(cub3D->mlx.ptr, cub3D->map.texture.north.img_ptr);
	if (cub3D->map.texture.south.img_ptr)
		mlx_destroy_image(cub3D->mlx.ptr, cub3D->map.texture.south.img_ptr);
	if (cub3D->map.texture.west.img_ptr)
		mlx_destroy_image(cub3D->mlx.ptr, cub3D->map.texture.west.img_ptr);
	if (cub3D->map.texture.east.img_ptr)
		mlx_destroy_image(cub3D->mlx.ptr, cub3D->map.texture.east.img_ptr);
	if (cub3D->mlx.ptr)
	{
		mlx_destroy_display(cub3D->mlx.ptr);
		free(cub3D->mlx.ptr);
	}
	free_map(&cub3D->map);
}

int	free_all_and_exit(t_data *cub3D)
{
	free_all(cub3D);
	exit(0);
	return (0);
}
