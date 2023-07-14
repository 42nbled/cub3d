/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:08:57 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 15:38:10 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	sign(double n)
{
	return ((n > 0) - (n < 0));
}

void	resolve_x_collision(t_data *data, t_vec v, int dx)
{
	if (dx == -1 && (data->player_x - (int)data->player_x) <= .15f)
		data->player_x = (int)data->player_x + 0.14f;
	else if (dx == 1 && data->player_x - (int)data->player_x >= .85f)
		data->player_x = (int)data->player_x + 0.86f;
	else
		data->player_x += v.x;
}

void	resolve_y_collision(t_data *data, t_vec v, int dy)
{
	if (dy == -1 && data->player_y - (int)data->player_y <= .15f)
		data->player_y = (int)data->player_y + 0.14f;
	else if (dy == 1
		&& (double)data->player_y - (double)(int)data->player_y >= .85f)
		data->player_y = (int)data->player_y + 0.86f;
	else
		data->player_y += v.y;
}

void	apply_mov(t_data *data, t_vec v)
{
	int		dx;
	int		dy;

	dx = sign(v.x);
	dy = sign(v.y);
	norm_vec(&v);
	if (data->map[(int)data->player_y][(int)data->player_x + dx] == '1')
		resolve_x_collision(data, v, dx);
	else
		data->player_x += v.x;
	if (data->map[(int)data->player_y + dy][(int)data->player_x] == '1')
		resolve_y_collision(data, v, dy);
	else
		data->player_y += v.y;
}

void	player_movement(t_data *data)
{
	t_vec	dir;

	dir = (t_vec){0};
	if (data->keys[UP])
		vec_add(&dir,
			(t_vec){cos(data->player_angle), sin(data->player_angle)});
	if (data->keys[DOWN])
		vec_add(&dir,
			(t_vec){-cos(data->player_angle), -sin(data->player_angle)});
	if (data->keys[STRAF_L])
	{
		dir.x += cos(data->player_angle - M_PI_2);
		dir.y += sin(data->player_angle - M_PI_2);
	}
	if (data->keys[STRAF_R])
	{
		dir.x += cos(data->player_angle + M_PI_2);
		dir.y += sin(data->player_angle + M_PI_2);
	}
	if (data->keys[LEFT])
		data->player_angle -= ROT_SPEED / 180.f * M_PI;
	if (data->keys[RIGHT])
		data->player_angle += ROT_SPEED / 180.f * M_PI;
	if (dir.x || dir.y)
		apply_mov(data, dir);
}
