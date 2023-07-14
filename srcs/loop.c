/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:20 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 12:44:50 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	get_angle(t_data *data)
{
	t_vec	focal;
	t_vec	range;

	focal.x = cos(data->player_angle) + data->player_x;
	focal.y = sin(data->player_angle) + data->player_y;
	focal.x += cos(data->player_angle - M_PI_2);
	focal.y += sin(data->player_angle - M_PI_2);
	range.x = cos(data->player_angle - M_PI_2) / (SCREEN_WIDTH / 2);
	range.y = sin(data->player_angle - M_PI_2) / (SCREEN_WIDTH / 2);
	focal.x -= range.x * data->num_ray;
	focal.y -= range.y * data->num_ray;
	data->ray_angle = atan2(focal.y - data->player_y, focal.x - data->player_x);
}

double length(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

int	sign(double n)
{
	return ((n > 0) - (n < 0));
}

void	player_movement(t_data *data)
{
	t_vec	movement;
	double	speed;
	double	rotation_speed;
	double	dx;
	double	dy;

	speed = 0.02;
	rotation_speed = 0.4;
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
		dx = cos(data->player_angle - M_PI_2 );
		dy = sin(data->player_angle - M_PI_2 );
		movement.x += dx;
		movement.y += dy;
	}
	if (data->keys[STRAF_R])
	{
		dx = cos(data->player_angle + M_PI_2 );
		dy = sin(data->player_angle + M_PI_2 );
		movement.x += dx;
		movement.y += dy;
	}
	if (data->keys[LEFT])
		data->player_angle -= rotation_speed / 180.f * M_PI;
	if (data->keys[RIGHT])
		data->player_angle += rotation_speed / 180.f * M_PI;

	double l = length(movement);
	if (l)
	{
		movement.x /= l;
		movement.y /= l;
		movement.x *= speed;
		movement.y *= speed;
	}

	int	ddx, ddy;

	ddx = sign(movement.x);
	ddy = sign(movement.y);
	if (data->map[(int)data->player_y][(int)data->player_x + ddx] == '1')
	{
		if (ddx == -1 && (data->player_x - (int)data->player_x) <= .15f)
			data->player_x = (int)data->player_x + 0.14f;
		else if (ddx == 1 && data->player_x - (int)data->player_x >= .85f)
			data->player_x = (int)data->player_x + 0.86f;
		else
			data->player_x += movement.x;
	}
	else
		data->player_x += movement.x;
	if (data->map[(int)data->player_y + ddy][(int)data->player_x] == '1')
	{
		if (ddy == -1 && data->player_y - (int)data->player_y <= .15f)
			data->player_y = (int)data->player_y + 0.14f;
		else if (ddy == 1 && (double)data->player_y - (double)(int)data->player_y >= .85f)
			data->player_y = (int)data->player_y + 0.86f;
		else
			data->player_y += movement.y;
	}
	else
		data->player_y += movement.y;
}

void    mouse_movement(t_data *data)
{
    double    rotation_speed;
    int        x;
    int        y;

    x = 0;
    y = 0;
    rotation_speed = 0.5;
    mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
    if (data->mouse == 1)
        mlx_mouse_move(data->mlx ,data->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    double dx = (x - SCREEN_WIDTH / 2.0f) / (SCREEN_WIDTH / 2.f);
    double da = pow(fabs(dx), 1.714f) * 40;
    if (data->mouse == 1 && x < SCREEN_WIDTH / 2)
        data->player_angle -= da * rotation_speed / 180.f * M_PI * 20;
    else if (data->mouse == 1 && x > SCREEN_WIDTH / 2)
        data->player_angle += da * rotation_speed / 180.f * M_PI * 20;
}

int	loop(t_data *data)
{
	t_vec	ray;

	player_movement(data);
	mouse_movement(data);
	data->num_ray = 0;
	while (data->num_ray < SCREEN_WIDTH)
	{
		get_angle(data);
		if (data->ray_angle == 0)
			data->ray_angle =  0.000001;
		ray = raycasting(data);
		(void)ray;
		if (!isnan(ray.x))
			print_screen(data, &ray);
		data->num_ray ++;
	}
	if (data->minimap == 1)
	{
		print_map(data);
		print_player(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}