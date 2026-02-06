/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sberete <sberete@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 21:25:04 by sberete           #+#    #+#             */
/*   Updated: 2026/02/06 21:25:05 by sberete          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabadd(char **tab, char *line)
{
	int		len;
	char	**new_tab;
	int		i;

	i = 0;
	len = ft_tablen(tab);
	new_tab = malloc(sizeof(char *) * (len + 2));
	if (!new_tab)
		return (NULL);
	while (i < len)
	{
		new_tab[i] = tab[i];
		i++;
	}
	new_tab[len] = line;
	new_tab[len + 1] = NULL;
	free(tab);
	return (new_tab);
}
