#include "cub3D.h"

static int	parse_cell(t_data *cub3d, int x, int y, char c)
{
	if (c == 'D')
	{
		add_door(cub3d, x, y);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (cub3d->player.count > 0)
			return (-1); // plusieurs joueurs
		cub3d->player.count++;
		init_player_from_map(cub3d, x, y, c);
		return (1);
	}
	return (0);
}

void	parse_map_grid(t_data *cub3d)
{
	size_t	len;
	int		res;

	size_t y, x;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->player.count = 0;
	y = 0;
	while (cub3d->map.grid[y])
	{
		len = ft_strlen(cub3d->map.grid[y]);
		if ((int)len > cub3d->map.width)
			cub3d->map.width = (int)len;
		cub3d->map.height++;
		x = 0;
		while (x < len)
		{
			res = parse_cell(cub3d, x, y, cub3d->map.grid[y][x]);
			if (res == -1)
			{
				ft_putendl_fd("Multiple players in map", 2);
				return ;
			}
			x++;
		}
		y++;
	}
}