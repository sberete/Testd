/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 20:42:07 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:53:13 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parsing(t_data *cub3d, int argc, char **argv)
{
	if (argc != 2)
		return (ft_putendl_fd("Invalid argument count", 2), 1);
	if (!has_cub_extension(argv[1]))
		return (ft_putendl_fd("Error: file must have .cub extension", 2), 1);
	cub3d->map.name = argv[1];
	cub3d->map.grid = NULL;
	if (parse_cub_file(cub3d, argv[1]))
		return (1);
	if (!cub3d->map.color.floor || !cub3d->map.color.ceiling)
		return (ft_putendl_fd("Missing floor or ceiling color", 2), 1);
	if (!cub3d->map.path.north || !cub3d->map.path.south
		|| !cub3d->map.path.west || !cub3d->map.path.east)
		return (ft_putendl_fd("Missing texture", 2), 1);
	cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
	if (!cub3d->map.doors)
		return (ft_putendl_fd("Failed to allocate doors", 2), 1);
	parse_map_grid(cub3d);
	if (cub3d->player.count == 0)
		return (ft_putendl_fd("No player in map", 2), 1);
	if (!validate_map(cub3d))
		return (ft_putendl_fd("Invalid map: open spaces or holes", 2), 1);
	return (0);
}
