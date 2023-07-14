/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 13:53:38 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 17:00:30 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(const char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		size1;
	int		size2;
	int		i;

	i = -1;
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (size1 + size2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (++i < size1)
		str[i] = s1[i];
	while (i < size1 + size2)
	{
		str[i] = s2[i - size1];
		i++;
	}
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*i_want_to_break_free(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (NULL);
}
