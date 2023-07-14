/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:06:29 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 17:33:56 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	struct_init(t_map *data)
{
	data->textures = (t_parse_textures){0};
	data->map = NULL;
	data->width = -1;
	data->height = -1;
}

void	finalise_tex(t_parse_textures *tex, int *e)
{
	tex->floor = get_color(tex->fstr, e);
	tex->ceil = get_color(tex->cstr, e);
}

int	parse(char **map, t_map *data)
{
	int	error;
	int	i;

	error = 0;
	i = get_textures(map, &(data->textures), &error);
	if (error)
		return (free_parse(data), error);
	while (map[i] && map[i][0] == '\n')
		i++;
	if (get_size_of_map(data, map, i))
		return (1);
	if (copy_map(data, map, i))
		return (free_parse(data));
	error = check_validity(data);
	if (error)
		return (free_parse(data));
	finalise_tex(&(data->textures), &error);
	if (error)
		return (free_parse(data));
	error = get_startpos(data);
	if (error)
		return (free_parse(data));
	return (error);
}
