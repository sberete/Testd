/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:49:48 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 23:06:56 by sberete          ###   ########.fr       */
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
		if (s[i++] < '0' || s[i - 1] > '9')
			return (0);
	return (1);
}

static int	trim_rgb_parts(char **split)
{
	char	*trimmed;

	trimmed = ft_strtrim_all(split[0]);
	if (!trimmed)
		return (free_tab(split), 1);
	free(split[0]);
	split[0] = trimmed;
	trimmed = ft_strtrim_all(split[1]);
	if (!trimmed)
		return (free_tab(split), 1);
	free(split[1]);
	split[1] = trimmed;
	trimmed = ft_strtrim_all(split[2]);
	if (!trimmed)
		return (free_tab(split), 1);
	free(split[2]);
	split[2] = trimmed;
	return (0);
}

int	convert_rgb_string(char *str)
{
	char	**split;
	int		rgb;
	int		r;
	int		g;
	int		b;

	if (!str)
		return (-1);
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (free_tab(split), -1);
	if (trim_rgb_parts(split))
		return (-1);
	if (!is_only_digits(split[0]) || !is_only_digits(split[1])
		|| !is_only_digits(split[2]))
		return (free_tab(split), -1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_tab(split);
	if (validate_rgb(r, g, b))
		return (-1);
	rgb = (r << 16) | (g << 8) | b;
	return (rgb);
}

static int	assign_color(t_color *color, char key, char *value, int rgb)
{
	if (key == 'F' && !color->floor)
	{
		color->floor = value;
		color->floor_rgb = rgb;
		return (0);
	}
	else if (key == 'C' && !color->ceiling)
	{
		color->ceiling = value;
		color->ceiling_rgb = rgb;
		return (0);
	}
	return (1);
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
	if (assign_color(&cub3d->map.color, key, value, rgb))
		return (free(value), ft_putendl_fd("Duplicate color line", 2), 1);
	return (0);
}
