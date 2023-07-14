/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:08:57 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 15:09:37 by cde-sede         ###   ########.fr       */
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
	t_vec	movement;
	double	dx;
	double	dy;

	dx = cos(data->player_angle);
	dy = sin(data->player_angle);
	movement.x = 0;
	movement.y = 0;
	if (data->keys[UP])
	{
		movement.x += dx;
		movement.y += dy;
	}
	if (data->keys[DOWN])
	{
		movement.x -= dx;
		movement.y -= dy;
	}
	if (data->keys[STRAF_L])
	{
		dx = cos(data->player_angle - M_PI_2);
		dy = sin(data->player_angle - M_PI_2);
		movement.x += dx;
		movement.y += dy;
	}
	if (data->keys[STRAF_R])
	{
		dx = cos(data->player_angle + M_PI_2);
		dy = sin(data->player_angle + M_PI_2);
		movement.x += dx;
		movement.y += dy;
	}
	if (data->keys[LEFT])
		data->player_angle -= ROT_SPEED / 180.f * M_PI;
	if (data->keys[RIGHT])
		data->player_angle += ROT_SPEED / 180.f * M_PI;
	if (movement.x || movement.y)
		apply_mov(data, movement);
}
