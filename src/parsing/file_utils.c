/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 21:21:40 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 21:23:42 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	process_line_before_map(t_data *cub3d, char *line)
{
	if (parse_cub_line(cub3d, line))
		return (1);
	return (0);
}

int	process_map_line(t_data *cub3d, char *line)
{
	if (!is_map_line(line))
		return (ft_putendl_fd("Invalid line after map", 2), 1);
	add_map_line(cub3d, line);
	return (0);
}

static void	chomp_newline(char *s)
{
	int	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
		s[--len] = '\0';
}

char	*next_raw_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	chomp_newline(line);
	return (line);
}

int	is_empty_line(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
