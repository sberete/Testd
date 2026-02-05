#include "cub3D.h"

static int	has_xpm_extension(char *path)
{
	int	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (!ft_strcmp(path + len - 4, ".xpm"));
}

static int	has_cub_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (!ft_strcmp(filename + len - 4, ".cub"));
}

char	*ft_strtrim_all(char *s)
{
	int	start;
	int	end;

	if (!s)
		return (NULL);
	start = 0;
	while (s[start] == ' ' || s[start] == '\t')
		start++;
	end = ft_strlen(s) - 1;
	while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\n'
			|| s[end] == '\r'))
		end--;
	return (ft_substr(s, start, end - start + 1));
}

int	is_empty(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}