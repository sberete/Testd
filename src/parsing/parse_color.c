/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:48 by sberete           #+#    #+#             */
/*   Updated: 2025/11/26 09:49:49 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
