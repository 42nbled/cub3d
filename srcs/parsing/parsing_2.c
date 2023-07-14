/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:05:49 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 17:33:55 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_size_of_map(t_map *data, char **map, int i)
{
	int	start;
	int	max_width;

	max_width = -1;
	start = i;
	while (map[i] && map[++i])
	{
		if ((ft_strlen(map[i]) == 0)
			|| (ft_strlen(map[i]) == 1 && map[i][0] == '\n'))
			return (1);
		if (ft_strlen(map[i]) > max_width)
			max_width = ft_strlen(map[i]);
	}
	data->width = max_width;
	data->height = i - start;
	if (max_width == -1)
		return (1);
	return (0);
}

int	check_validity(t_map *data)
{
	int	y;
	int	x;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (!strchr(" 01NSEW", data->map[y][x]))
				return (2);
			if (data->map[y][x] == '0')
			{
				if (y == 0 || x == 0
					|| y == data->height - 1 || x == data->width - 1)
					return (3);
				if (data->map[y - 1][x] == ' '
					|| data->map[y + 1][x] == ' '
					|| data->map[y][x - 1] == ' '
					|| data->map[y][x + 1] == ' ')
					return (4);
			}
		}
	}
	return (0);
}

int	copy_map(t_map *data, char **src, int i)
{
	int	x;
	int	y;

	y = -1;
	data->map = malloc(sizeof(char **) * (data->height + 1));
	if (!data->map)
		return (1);
	while (++y < data->height)
	{
		data->map[y] = malloc(sizeof(char *) * (data->width + 1));
		if (!data->map[y])
			return (1);
		x = -1;
		while (++x < ft_strlen(src[y + i]))
		{
			if (src[y + i][x] != '\n')
				data->map[y][x] = src[y + i][x];
			else
				data->map[y][x] = ' ';
		}
		while (x < data->width)
			data->map[y][x++] = ' ';
		data->map[y][x] = '\0';
	}
	return (data->map[y] = NULL, 0);
}

int	condition_tex(t_parse_textures *tex, int fc)
{
	return ((!tex->nstr
			|| !tex->sstr
			|| !tex->wstr
			|| !tex->estr
			|| !(fc & 1)
			|| !(fc & 2)));
}

int	get_textures(char **map, t_parse_textures *tex, int *e)
{
	int	i;
	int	fc;

	i = -1;
	fc = 0;
	while (map[++i] && condition_tex(tex, fc) && *e == 0)
	{
		if (!map[i][0])
			continue ;
		if (condition_get_all(tex, map[i], &fc) == 1)
			*e = 1;
	}
	if (condition_tex(tex, fc))
		*e = 1;
	return (i);
}
