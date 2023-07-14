/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:02:32 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 14:43:09 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	x;

	x = -1;
	while (map[++x])
		free(map[x]);
	free(map);
}

int	free_parse(t_map *data)
{
	if (data->map)
		free_map(data->map);
	if (data->textures.nstr)
		free(data->textures.nstr);
	if (data->textures.sstr)
		free(data->textures.sstr);
	if (data->textures.estr)
		free(data->textures.estr);
	if (data->textures.wstr)
		free(data->textures.wstr);
	if (data->textures.fstr)
		free(data->textures.fstr);
	if (data->textures.cstr)
		free(data->textures.cstr);
	return (1);
}

int	rotate_start(char c)
{
	if (c == 'N')
		return (-90);
	if (c == 'S')
		return (90);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (180);
	return (0);
}

int	get_startpos(t_map *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (strchr("NSEW", data->map[y][x]))
			{
				data->start_pos.x = x + .5f;
				data->start_pos.y = y + .5f;
				data->start_angle = (double)rotate_start(data->map[y][x])
					/ 180 * M_PI;
				return (0);
			}
		}
	}
	return (1);
}

int	parsing(int fd, t_map *data)
{
	char	**map;

	map = read_map(fd);
	struct_init(data);
	if (parse(map, data) == 1)
		return (free_map(map), 1);
	free_map(map);
	return (0);
}
