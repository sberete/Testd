/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:50:09 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 20:00:08 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_tile_minimap(t_data *cub3d, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			put_pixel(&cub3d->img, MINIMAP_OFFSET_X + pos.x + j,
				MINIMAP_OFFSET_Y + pos.y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_data *cub3d, int tile_size)
{
	int		player_size;
	t_point	pos;

	player_size = tile_size / 2;
	pos.x = (int)(cub3d->player.pos.x * tile_size) - player_size / 2;
	pos.y = (int)(cub3d->player.pos.y * tile_size) - player_size / 2;
	draw_tile_minimap(cub3d, pos, player_size, RED);
}

static void	draw_minimap_tile(t_data *cub3d, char c, t_point pos, int size)
{
	if (c == ' ')
		return ;
	if (c == '1')
		draw_tile_minimap(cub3d, pos, size, COLOR_WALL);
	else if (c == '2')
		draw_tile_minimap(cub3d, pos, size, COLOR_DOOR);
	else if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		draw_tile_minimap(cub3d, pos, size, COLOR_FLOOR);
}

static int	get_minimap_tile_size(t_data *cub3d)
{
	int	w;
	int	h;

	w = (int)((WIDTH * MINIMAP_SCALE) / cub3d->map.width);
	h = (int)((HEIGHT * MINIMAP_SCALE) / cub3d->map.height);
	if (h < w)
		return (h);
	return (w);
}

void	draw_minimap(t_data *cub3d)
{
	char	**map;
	int		size;
	int		x;
	int		y;
	t_point	pos;

	map = cub3d->map.grid;
	size = get_minimap_tile_size(cub3d);
	y = 0;
	while (y < cub3d->map.height)
	{
		x = 0;
		while (x < cub3d->map.width)
		{
			pos.x = x * size;
			pos.y = y * size;
			draw_minimap_tile(cub3d, map[y][x], pos, size);
			x++;
		}
		y++;
	}
	draw_player_minimap(cub3d, size);
}
