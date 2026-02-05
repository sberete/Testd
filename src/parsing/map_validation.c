#include "cub3D.h"

static int	flood_fill(char **grid, int width, int height, int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill(grid, width, height, x + 1, y))
		return (0);
	if (!flood_fill(grid, width, height, x - 1, y))
		return (0);
	if (!flood_fill(grid, width, height, x, y + 1))
		return (0);
	if (!flood_fill(grid, width, height, x, y - 1))
		return (0);
	return (1);
}

int	validate_map(t_data *cub3d)
{
	char **copy;
	int valid;

	copy = ft_tabdup(cub3d->map.grid);
	valid = flood_fill(copy, cub3d->map.width, cub3d->map.height,
			(int)cub3d->player.pos.x, (int)cub3d->player.pos.y);
	free_tab(copy);
	return (valid);
}
