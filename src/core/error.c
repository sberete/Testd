/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:36:04 by sberete           #+#    #+#             */
/*   Updated: 2025/11/03 14:19:46 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	mlx_failure(t_data *cub3D, char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free_all_and_exit(cub3D);
}

void	param_available(void)
{
	ft_putstr_fd("Error\nUsage: ./cub3D <map_path.cub>\n", 2);
	exit(1);
}
