/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:51:17 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 15:54:24 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	vec_add(t_vec *a, t_vec b)
{
	a->x += b.x;
	a->y += b.y;
}

void	calc_droite_x(t_data *data, t_vec *pos)
{
	double	m;
	double	c;

	m = sin(data->ray_angle) / cos(data->ray_angle);
	c = (data->player_y - m * data->player_x) * 50;
	pos->y = m * pos->x + c;
}

t_vec	get_dist_x(t_data *data, t_vec dir, int signe1, int signe2)
{
	t_vec	pos;

	pos.x = (double)((int)(data->player_x + 1 - signe2) * 50);
	calc_droite_x(data, &pos);
	if (pos.x >= 0 && pos.x < data->map_widht * 50 && pos.y > 0
		&& pos.y < data->map_height * 50)
		if (data->map[(int)(pos.y / 50)][(int)(pos.x / 50) - signe2] == '1')
			return (pos);
	dir.x = pos.x;
	dir.y = pos.y;
	pos.x += 50 * signe1;
	calc_droite_x(data, &pos);
	dir.x = pos.x - dir.x;
	dir.y = pos.y - dir.y;
	while (pos.x >= 0 && pos.x < data->map_widht * 50 && pos.y > 0
		&& pos.y < data->map_height * 50)
	{
		if (data->map[(int)(pos.y / 50)][(int)(pos.x / 50) - signe2] == '1')
			return (pos);
		vec_add(&pos, dir);
	}
	return (pos);
}

void	calc_droite_y(t_data *data, t_vec *pos)
{
	double	m;
	double	c;

	m = cos(data->ray_angle) / sin(data->ray_angle);
	c = (data->player_x - m * data->player_y) * 50;
	pos->x = m * pos->y + c;
}

t_vec	get_dist_y(t_data *data, t_vec dir, int signe1, int signe2)
{
	t_vec	pos;
	t_vec	tmp;

	pos.y = (double)((int)(data->player_y + 1 - signe2) * 50);
	calc_droite_y(data, &pos);
	if (pos.x >= 0 && pos.x < data->map_widht * 50 && pos.y > 0
		&& pos.y < data->map_height * 50)
		if (data->map[(int)(pos.y / 50) - signe2][(int)(pos.x / 50)] == '1')
			return (pos);
	tmp.x = pos.x;
	tmp.y = pos.y;
	pos.y += 50 * signe1;
	calc_droite_y(data, &pos);
	dir.x = pos.x - tmp.x;
	dir.y = pos.y - tmp.y;
	while (pos.x >= 0 && pos.x < data->map_widht * 50 && pos.y > 0
		&& pos.y < data->map_height * 50)
	{
		if (data->map[(int)(pos.y / 50) - signe2][(int)(pos.x / 50)] == '1')
			return (pos);
		vec_add(&pos, dir);
	}
	return (pos);
}
