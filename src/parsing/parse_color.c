/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:48 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:39:55 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	validate_rgb(int r, int g, int b)
{
	return (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255);
}

static int	is_only_digits(char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	convert_rgb_string(char *str)
{
	char	*tmp1;
	char	*tmp2;
	char	*r_str;
	char	*g_str;
	char	*b_str;

	int r, g, b;
	if (!str)
		return (-1);
	tmp1 = ft_strchr(str, ',');
	if (!tmp1)
		return (-1);
	tmp2 = ft_strchr(tmp1 + 1, ',');
	if (!tmp2)
		return (-1);
	if (ft_strchr(tmp2 + 1, ','))
		return (-1); // trop de virgules ❌
	*tmp1 = '\0';
	*tmp2 = '\0';
	r_str = ft_strtrim_all(str);
	g_str = ft_strtrim_all(tmp1 + 1);
	b_str = ft_strtrim_all(tmp2 + 1);
	if (!is_only_digits(r_str) || !is_only_digits(g_str)
		|| !is_only_digits(b_str))
	{
		free(r_str);
		free(g_str);
		free(b_str);
		return (-1);
	}
	r = ft_atoi(r_str);
	g = ft_atoi(g_str);
	b = ft_atoi(b_str);
	free(r_str);
	free(g_str);
	free(b_str);
	if (validate_rgb(r, g, b))
		return (-1);
	return ((r << 16) | (g << 8) | b);
}
int	parse_color_line(t_data *cub3d, char *line)
{
	char	key;
	char	*value;
	int		rgb;

	if (!line || line[0] == '\0')
		return (ft_putendl_fd("Invalid color line", 2), 1);
	key = line[0];
	value = ft_strtrim_all(line + 1);
	if (!value || value[0] == '\0')
		return (ft_putendl_fd("Color value missing", 2), 1);
	rgb = convert_rgb_string(value);
	if (rgb == -1)
		return (free(value), ft_putendl_fd("Invalid color format", 2), 1);
	if (key == 'F' && !cub3d->map.color.floor)
		cub3d->map.color.floor = value, cub3d->map.color.floor_rgb = rgb;
	else if (key == 'C' && !cub3d->map.color.ceiling)
		cub3d->map.color.ceiling = value, cub3d->map.color.ceiling_rgb = rgb;
	else
		return (free(value), ft_putendl_fd("Duplicate color line", 2), 1);
	return (0);
}