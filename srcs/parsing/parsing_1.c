/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:05:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 17:08:54 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**append_map(char **c, char *s)
{
	int		i;
	char	**n;

	i = -1;
	if (c)
		while (c[++i])
			;
	else
		i = 0;
	n = malloc(sizeof(char *) * (i + 2));
	i = -1;
	if (c)
		while (c[++i])
			n[i] = c[i];
	else
		i = 0;
	n[i++] = s;
	n[i] = NULL;
	free(c);
	return (n);
}

char	**read_map(int fd)
{
	char	**map;
	char	*line;

	line = NULL;
	map = NULL;
	while (map == NULL || line != NULL)
	{
		line = get_next_line(fd);
		map = append_map(map, line);
	}
	return (map);
}

char	*get_path(char *str)
{
	char	*dst;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (str[i] && (str[i] != ' ' && str[i] != '\t'))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	dst = malloc(ft_strlen(str) - i + 1);
	while (str[i] && str[i] != '\n')
		dst[y++] = str[i++];
	dst[y] = '\0';
	return (dst);
}

void	free_color(char **t)
{
	int	i;

	i = -1;
	while (t[++i])
		free(t[i]);
	free(t);
}

int	get_color(char *s, int *e)
{
	unsigned int	c;
	char			**tmp;
	int				i;

	tmp = ft_split(s, ',');
	c = 0;
	i = -1;
	while (tmp && tmp[++i])
		if (!is_number(tmp[i]))
			*e = 1;
	if (i != 3 || *e)
		return (*e = 1, free_color(tmp), c);
	c = (ft_atoi(tmp[0]) << 16) + (ft_atoi(tmp[1]) << 8)
		+ (ft_atoi(tmp[2]) << 0);
	free_color(tmp);
	return (c);
}
