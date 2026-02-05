/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:51:56 by sberete           #+#    #+#             */
/*   Updated: 2026/02/05 22:12:29 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(char *str)
{
	char	*new_line;
	int		i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (new_line == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		new_line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		new_line[i++] = '\n';
	new_line[i] = '\0';
	return (new_line);
}

static char	*get_newline(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	new_str = NULL;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	len = ft_strlen(str);
	if (str[i] == '\n' && str[i + 1] != '\0')
	{
		new_str = malloc(sizeof(char) * (len - i + 1));
		if (new_str == NULL)
			return (NULL);
		j = 0;
		while (str[++i] != '\0')
			new_str[j++] = str[i];
		new_str[j] = '\0';
	}
	free(str);
	return (new_str);
}

static char	*append_buffer(char *str, char *buffer)
{
	char	*tmp;

	if (!str)
		return (ft_strdup(buffer));
	tmp = ft_strjoin(str, buffer);
	free(str);
	return (tmp);
}

static char	*extract_line(char **str)
{
	char	*line;

	line = get_line(*str);
	*str = get_newline(*str);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && (!str || !ft_strchr(str, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		str = append_buffer(str, buffer);
		if (!str)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (extract_line(&str));
}
