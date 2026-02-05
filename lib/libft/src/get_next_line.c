/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:51:56 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 19:49:46 by sxriimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*remove_line(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		len;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	len = ft_strlen(str);
	new_str = NULL;
	if (str[i] == '\n' && str[i + 1] != '\0')
	{
		new_str = malloc(sizeof(char) * (len - i));
		if (!new_str)
			return (NULL);
		j = 0;
		i++;
		while (str[i])
			new_str[j++] = str[i++];
		new_str[j] = '\0';
	}
	free(str);
	return (new_str);
}

static int	read_fd(int fd, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes <= 0)
		return (bytes);
	buffer[bytes] = '\0';
	if (!*str)
		*str = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(*str, buffer);
		free(*str);
		*str = tmp;
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read_fd(fd, &str);
		if (bytes < 0)
			return (NULL);
	}
	if (!str || !*str)
		return (NULL);
	line = extract_line(str);
	str = remove_line(str);
	return (line);
}
