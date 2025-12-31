/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:23:15 by sberete           #+#    #+#             */
/*   Updated: 2025/12/25 21:07:27 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_map(t_map *map)
{
	if (map->grid)
		free_tab(map->grid);
	free(map->doors);
	/*if (map->color.ceiling)
		free(map->color.ceiling);
	if (map->color.floor)
		free(map->color.floor);
	if (map->texture.east)
		free(map->texture.east);
	if (map->texture.north)
		free(map->texture.north);
	if (map->texture.west)
		free(map->texture.west);
	if (map->texture.south)
		free(map->texture.south);*/
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
