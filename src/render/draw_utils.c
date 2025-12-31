/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:50:43 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:50:44 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	compute_draw_limits(double dist, int *line_h, int *start, int *end)
{
	*line_h = (int)(HEIGHT / dist);
	*start = -(*line_h) / 2 + HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = *line_h / 2 + HEIGHT / 2;
	if (*end >= HEIGHT)
		*end = HEIGHT - 1;
}
