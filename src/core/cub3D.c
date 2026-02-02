/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:00 by sberete           #+#    #+#             */
/*   Updated: 2026/01/03 00:15:33 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_data	cub3d;

	ft_bzero(&cub3d, sizeof(t_data));
	if (parsing(&cub3d, argc, argv))
	{
		mlx_failure(&cub3d, "Usage: ./cub3D <map_path.cub>");
		return (1);
	}
	cub3d_init(&cub3d);
	mlx_loop(cub3d.mlx.ptr);
}
