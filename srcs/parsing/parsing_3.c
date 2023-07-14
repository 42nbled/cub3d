/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:06:29 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 14:16:32 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	copy_map(data, map, i);
	error = check_validity(data);
	finalise_tex(&(data->textures), &error);
	error = get_startpos(data);
	if (error)
		return (free_parse(data));
	return (error);
}

void	finalise_tex(t_parse_textures *tex, int *e)
{
	tex->floor = get_color(tex->fstr, e);
	tex->ceil = get_color(tex->cstr, e);
}
