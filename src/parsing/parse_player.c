/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:57 by sberete           #+#    #+#             */
/*   Updated: 2025/12/27 01:56:55 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player_plane(t_player *player)
{
	double	fov_factor;

	fov_factor = 0.66;
	if (player->dir.x == 0 && player->dir.y == -1)
	{
		player->plane.x = fov_factor;
		player->plane.y = 0.0;
	}
	else if (player->dir.x == 0 && player->dir.y == 1)
	{
		player->plane.x = -fov_factor;
		player->plane.y = 0.0;
	}
	else if (player->dir.x == 1 && player->dir.y == 0)
	{
		player->plane.x = 0.0;
		player->plane.y = fov_factor;
	}
	else if (player->dir.x == -1 && player->dir.y == 0)
	{
		player->plane.x = 0.0;
		player->plane.y = -fov_factor;
	}
}

void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir.x = 0.0;
		p->dir.y = -1.0;
	}
	else if (c == 'S')
	{
		p->dir.x = 0.0;
		p->dir.y = 1.0;
	}
	else if (c == 'E')
	{
		p->dir.x = 1.0;
		p->dir.y = 0.0;
	}
	else if (c == 'W')
	{
		p->dir.x = -1.0;
		p->dir.y = 0.0;
	}
}

void	init_player_from_map(t_data *cub3d, int x, int y, char c)
{
	cub3d->player.pos.x = x + 0.5;
	cub3d->player.pos.y = y + 0.5;
	set_player_dir(&cub3d->player, c);
	init_player_plane(&cub3d->player);
	cub3d->map.grid[y][x] = '0';
}
