/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:42:07 by sberete           #+#    #+#             */
/*   Updated: 2026/02/03 20:42:30 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	add_door(t_data *cub3d, int x, int y)
{
	t_door	*door;

	door = &cub3d->map.doors[cub3d->map.door_count];
	door->x = x;
	door->y = y;
	door->openness = 0.0;
	door->opening = 0;
	cub3d->map.door_count++;
	cub3d->map.grid[y][x] = '2';
}

int	convert_rgb_string(char *str)
{
	int	r;
	int	g;
	int	b;

	if (!str)
		return (0);
	r = ft_atoi(str);
	str = ft_strchr(str, ',');
	if (!str)
		return (0);
	g = ft_atoi(++str);
	str = ft_strchr(str, ',');
	if (!str)
		return (0);
	b = ft_atoi(++str);
	return ((r << 16) | (g << 8) | b);
}

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

// trim tout ce qui n'est pas visible : espaces, tab, \n, \r
char	*ft_strtrim_all(char *s)
{
	int	start;
	int	end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	end = ft_strlen(s) - 1;
	while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'
			|| s[end] == '\r'))
		end--;
	return (ft_substr(s, start, end - start + 1));
}

void	init_player_from_map(t_data *cub3d, int x, int y, char c)
{
	cub3d->player.pos.x = x + 0.5;
	cub3d->player.pos.y = y + 0.5;
	set_player_dir(&cub3d->player, c);
	init_player_plane(&cub3d->player);
	cub3d->map.grid[y][x] = '0';
}

char	**fill_test_map(void)
{
	char	*template[] = {"111111111111111111111", "101000001000000000001",
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

int	load_texture(void *mlx_ptr, char *path, t_img *tex)
{
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

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
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

int	parse_cell(t_data *cub3d, int x, int y, char c)
{
	if (c == 'D')
	{
		add_door(cub3d, x, y);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		init_player_from_map(cub3d, x, y, c);
		return (1);
	}
	return (0);
}

void	parse_map_grid(t_data *cub3d)
{
	size_t	y;
	size_t	x;
	size_t	len;
	int		found;

	y = 0;
	found = 0;
	while (cub3d->map.grid[y])
	{
		len = ft_strlen(cub3d->map.grid[y]);
		if ((int)len > cub3d->map.width)
			cub3d->map.width = (int)len;
		cub3d->map.height++;
		x = 0;
		while (x < len && !found)
		{
			found = parse_cell(cub3d, x, y, cub3d->map.grid[y][x]);
			x++;
		}
		y++;
	}
}

int	is_texture_line(char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (1);
	if (!ft_strncmp(line, "SO ", 3))
		return (1);
	if (!ft_strncmp(line, "WE ", 3))
		return (1);
	if (!ft_strncmp(line, "EA ", 3))
		return (1);
	return (0);
}

int	is_color_line(char *line)
{
	if (!ft_strncmp(line, "F ", 2))
		return (1);
	if (!ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

int	parse_color(t_data *cub3d, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (!split || ft_tablen(split) != 2)
		return (free_tab(split), ft_putendl_fd("Invalid color line", 2), 1);
	if (split[0][0] == 'F')
		cub3d->map.color.floor = ft_strdup(split[1]);
	else if (split[0][0] == 'C')
		cub3d->map.color.ceiling = ft_strdup(split[1]);
	else
		return (free_tab(split), ft_putendl_fd("Unknown color identifier", 2),
			1);
	free_tab(split);
	return (0);
}

int	parse_texture(t_data *cub3d, char *line)
{
	char	**split;
	char	*tmp;

	split = ft_split(line, ' ');
	if (!split || ft_tablen(split) != 2)
	{
		free_tab(split);
		return (ft_putendl_fd("Invalid texture line", 2), 1);
	}
	// Nettoyage complet du path
	tmp = ft_strtrim_all(split[1]);
	if (!tmp)
	{
		free_tab(split);
		return (ft_putendl_fd("Texture path invalid", 2), 1);
	}
	if (!ft_strcmp(split[0], "NO"))
		cub3d->map.path.north = tmp;
	else if (!ft_strcmp(split[0], "SO"))
		cub3d->map.path.south = tmp;
	else if (!ft_strcmp(split[0], "WE"))
		cub3d->map.path.west = tmp;
	else if (!ft_strcmp(split[0], "EA"))
		cub3d->map.path.east = tmp;
	else
	{
		free(tmp);
		free_tab(split);
		return (ft_putendl_fd("Unknown texture identifier", 2), 1);
	}
	free_tab(split);
	return (0);
}

int	parse_cub_line(t_data *cub3d, char *line)
{
	if (is_empty(line))
		return (0);
	if (is_texture_line(line))
		return (parse_texture(cub3d, line));
	if (is_color_line(line))
		return (parse_color(cub3d, line));
	return (0);
	// if (is_map_line(line))
	// return (add_map_line(cub3d, line));
	return (ft_putendl_fd("Invalid line in .cub", 2), 1);
}

int	parse_cub_file(t_data *cub3d, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putendl_fd("Cannot open .cub file", 2), 1);
	while ((line = get_next_line(fd)))
	{
		if (parse_cub_line(cub3d, line))
			return (free(line), close(fd), 1);
		free(line);
	}
	close(fd);
	// if (!cub_config_complete(cub3d))
	// return (error("Missing configuration"));
	return (0);
}

int	parsing(t_data *cub3d, int argc, char **argv)
{
	if (argc != 2)
		return (ft_putendl_fd("Invalid argument count", 2), 1);
	cub3d->map.name = argv[1];
	cub3d->map.grid = fill_test_map();
	if (!cub3d->map.grid)
		return (1);
	if (parse_cub_file(cub3d, argv[1]))
		return (1);
	cub3d->map.color.floor_rgb = convert_rgb_string(cub3d->map.color.floor);
	cub3d->map.color.ceiling_rgb = convert_rgb_string(cub3d->map.color.ceiling);
	// printf("%d, %d\n", cub3d->map.color.floor_rgb,cub3d->map.color.ceiling_rgb);
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.door_count = 0;
	cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
	if (!cub3d->map.doors)
		return (1);
	parse_map_grid(cub3d);
	return (0);
}
