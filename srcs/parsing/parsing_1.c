/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:05:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 14:32:31 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**read_map(int fd)
{
	char	**map;
	char	*line;
	char	*s;

	s = NULL;
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		s = ft_strjoin(s, line);
		free(line);
	}
	map = ft_split(s, '\n');
	free(s);
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
	dst = malloc(strlen(str) - i + 1);
	while (str[i] && str[i] != '\n')
		dst[y++] = str[i++];
	dst[y] = '\0';
	return (dst);
}

int	get_color(char *s, int *e)
{
	unsigned int	c;
	char			**tmp;
	int				i;

	tmp = ft_split(s, ',');
	c = 0;
	i = -1;
	while (tmp[++i])
		;
	if (i != 3)
		return (*e = 1, c);
	c = (atoi(tmp[0]) << 16) + (atoi(tmp[1]) << 8) + (atoi(tmp[2]) << 0);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (c);
}

void	struct_init(t_map *data)
{
	data->textures = (t_parse_textures){0};
	data->map = NULL;
	data->width = -1;
	data->height = -1;
}
