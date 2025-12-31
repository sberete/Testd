/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:26:49 by sberete           #+#    #+#             */
/*   Updated: 2025/12/31 01:36:12 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
Du coup la je t'ai mis ce que j'aurais besoin que tu me remplisse
Ca sera tout les structures en bas dans le commentaire

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_texture;

typedef struct s_color
{
	char		*floor;
	char		*ceiling;
}				t_color;

typedef struct s_map
{
	char		*name;
	t_texture	texture;
	t_color		color;
	char		**grid;
	int			width;
	int			height;
}				t_map;

typedef struct s_direction
{
	double		x;
	double		y;
}				t_direction;

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_player
{
	t_direction	dir;
	t_position	pos;
}				t_player;
*/
static char	**fill_test_map(void)
{
	static char	*template[] = {"111111111111111111111", "101000001000000000001",
			"101010101011111110001", "100010100010000010001",
			"111110101111101011101", "100000101000101000001",
			"101111101011101111111", "101000001010100000101",
			"101011111010111110101", "101010001010100010101",
			"101110101010101010101", "100000101010001010001",
			"111111101011111011101", "100000101000100010001",
			"101110101110101110111", "101000100000100010101",
			"101011111111111010101", "100010000000000010001",
			"1D10101110111111111D1", "1N0000000000000000001",
			"111111111111111111111", NULL};

	return (ft_tabdup(template));
}

int	parsing(t_data *cub3d, int argc, char **argv)
{
	int		found;
	char	*line;
	size_t	len;
	char	c;

	if (argc != 2)
		return (1);
	cub3d->map.name = argv[1];
	cub3d->map.grid = fill_test_map();
	if (!cub3d->map.grid)
		return (1);
	cub3d->map.path.north = "./textures/metal_rust.xpm";
	cub3d->map.path.west = "./textures/metal_rust.xpm";
	cub3d->map.path.east = "./textures/metal_rust.xpm";
	cub3d->map.path.south = "./textures/metal_rust.xpm";
	cub3d->map.color.floor = "164,169,20";
	cub3d->map.color.ceiling = "153,204,255";
	cub3d->map.color.floor_rgb = convert_rgb_string(cub3d->map.color.floor);
	cub3d->map.color.ceiling_rgb = convert_rgb_string(cub3d->map.color.ceiling);
	// cub3d->map.width = 0;
	// cub3d->map.height = 0;
	found = 0;
	// cub3d->map.door_count = 0;
	cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
	if (!cub3d->map.doors)
		return (1);
	for (int y = 0; cub3d->map.grid[y]; y++)
	{
		line = cub3d->map.grid[y];
		len = ft_strlen(line);
		if ((int)len > cub3d->map.width)
			cub3d->map.width = (int)len;
		cub3d->map.height++;
		for (size_t x = 0; x < len && !found; x++)
		{
			c = line[x];
			if (c == 'D')
			{
				cub3d->map.doors[cub3d->map.door_count].x = x;
				cub3d->map.doors[cub3d->map.door_count].y = y;
				cub3d->map.doors[cub3d->map.door_count].openness = 0.0;
				cub3d->map.doors[cub3d->map.door_count].opening = 0;
				cub3d->map.door_count++;
				cub3d->map.grid[y][x] = '2';
				continue ;
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cub3d->player.pos.x = (double)x + 0.5;
				cub3d->player.pos.y = (double)y + 0.5;
				cub3d->map.grid[y][x] = '0';
				if (c == 'N')
				{
					cub3d->player.dir.x = 0.0;
					cub3d->player.dir.y = -1.0;
				}
				else if (c == 'S')
				{
					cub3d->player.dir.x = 0.0;
					cub3d->player.dir.y = 1.0;
				}
				else if (c == 'E')
				{
					cub3d->player.dir.x = 1.0;
					cub3d->player.dir.y = 0.0;
				}
				else if (c == 'W')
				{
					cub3d->player.dir.x = -1.0;
					cub3d->player.dir.y = 0.0;
				}
				init_player_plane(&cub3d->player);
				found = 1;
			}
		}
	}
	return (0);
}

// static int	parse_cell(t_data *cub3d, int x, int y, char c)
// {
// 	if (c == 'D')
// 	{
// 		add_door(cub3d, x, y);
// 		return (0);
// 	}
// 	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 	{
// 		init_player_from_map(cub3d, x, y, c);
// 		return (1);
// 	}
// 	return (0);
// }

// static void	parse_map_grid(t_data *cub3d)
// {
// 	size_t	y;
// 	size_t	x;
// 	size_t	len;
// 	int		found;

// 	y = 0;
// 	found = 0;
// 	while (cub3d->map.grid[y])
// 	{
// 		len = ft_strlen(cub3d->map.grid[y]);
// 		if ((int)len > cub3d->map.width)
// 			cub3d->map.width = (int)len;
// 		cub3d->map.height++;

// 		x = 0;
// 		while (x < len && !found)
// 		{
// 			found = parse_cell(cub3d, x, y,
// 					cub3d->map.grid[y][x]);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	parsing(t_data *cub3d, int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (1);

// 	cub3d->map.name = argv[1];
// 	cub3d->map.grid = fill_test_map();
// 	if (!cub3d->map.grid)
// 		return (1);

// 	cub3d->map.path.north = "./textures/metal_rust.xpm";
// 	cub3d->map.path.south = "./textures/metal_rust.xpm";
// 	cub3d->map.path.east = "./textures/metal_rust.xpm";
// 	cub3d->map.path.west = "./textures/metal_rust.xpm";

// 	cub3d->map.color.floor = "164,169,20";
// 	cub3d->map.color.ceiling = "153,204,255";
// 	cub3d->map.color.floor_rgb =
// 		convert_rgb_string(cub3d->map.color.floor);
// 	cub3d->map.color.ceiling_rgb =
// 		convert_rgb_string(cub3d->map.color.ceiling);

// 	cub3d->map.width = 0;
// 	cub3d->map.height = 0;
// 	cub3d->map.door_count = 0;

// 	cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
// 	if (!cub3d->map.doors)
// 		return (1);

// 	parse_map_grid(cub3d);
// 	return (0);
// }
