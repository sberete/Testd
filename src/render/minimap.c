//
	/* ************************************************************************** */
//
	/*                                                                            */
//
	/*                                                        :::      ::::::::   */
//
	/*   minimap.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+        
	+:+     */
// /*   By: sberete <sberete@student.42.fr>            +#+  +:+      
	+#+        */
// /*                                                +#+#+#+#+#+  
	+#+           */
//
	/*   Created: 2025/11/18 13:52:44 by sberete           #+#    #+#             */
//
	/*   Updated: 2025/11/18 13:52:45 by sberete          ###   ########.fr       */
//
	/*                                                                            */
//
	/* ************************************************************************** */

// #include "cub3D.h"

// void	draw_tile_minimap(t_data *cub3d, t_point pos, int size, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			put_pixel(&cub3d->img, MINIMAP_OFFSET_X + pos.x + j,
// 				MINIMAP_OFFSET_Y + pos.y + i, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	draw_player_minimap(t_data *cub3d)
// {
// 	int		size;
// 	int		player_size;
// 	t_point	pos;

// 	size = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
// 	player_size = size / 2;
// 	pos.x = (int)(cub3d->player.pos.x * size) - player_size / 2;
// 	pos.y = (int)(cub3d->player.pos.y * size) - player_size / 2;
// 	draw_tile_minimap(cub3d, pos, player_size, RED);
// }

// void	draw_minimap(t_data *cub3d)
// {
// 	char	**map;
// 	int		size;
// 	int		y;
// 	int		x;
// 	t_point	pos;

// 	map = cub3d->map.grid;
// 	size = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
// 	y = 0;
// 	while (map[y])
// 	{
// 		x = 0;
// 		while (map[y][x])
// 		{
// 			pos.x = x * size;
// 			pos.y = y * size;
// 			if (map[y][x] == '1')
// 				draw_tile_minimap(cub3d, pos, size, COLOR_WALL);
// 			else
// 				draw_tile_minimap(cub3d, pos, size, COLOR_FLOOR);
// 			x++;
// 		}
// 		y++;
// 	}
// 	draw_player_minimap(cub3d);
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 13:52:44 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:00:00 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Dessine un carré à la position donnée
void	draw_tile_minimap(t_data *cub3d, t_point pos, int size, int color)
{
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			put_pixel(&cub3d->img, MINIMAP_OFFSET_X + pos.x + j,
				MINIMAP_OFFSET_Y + pos.y + i, color);
}

// Dessine le joueur sur la minimap
void	draw_player_minimap(t_data *cub3d, int tile_size)
{
	int		player_size;
	t_point	pos;

	player_size = tile_size / 2;
	pos.x = (int)(cub3d->player.pos.x * tile_size) - player_size / 2;
	pos.y = (int)(cub3d->player.pos.y * tile_size) - player_size / 2;
	draw_tile_minimap(cub3d, pos, player_size, RED);
}

// Dessine la minimap complète
void	draw_minimap(t_data *cub3d)
{
	char	**map;
	int		tile_w;
	int		tile_h;
	t_point	pos;

	map = cub3d->map.grid;
	tile_w = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
	tile_h = (int)((HEIGHT * MINIMAP_SCALE) / cub3d->map.height);
	int size = (tile_w < tile_h) ? tile_w : tile_h; // taille optimale
	for (int y = 0; map[y]; y++)
	{
		for (int x = 0; map[y][x]; x++)
		{
			pos.x = x * size;
			pos.y = y * size;
			if (map[y][x] == '1')
				draw_tile_minimap(cub3d, pos, size, COLOR_WALL);
			else if (map[y][x] == '2')
				draw_tile_minimap(cub3d, pos, size, COLOR_DOOR);
			else
				draw_tile_minimap(cub3d, pos, size, COLOR_FLOOR);
		}
	}
	draw_player_minimap(cub3d, size);
}
