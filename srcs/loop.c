/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:20 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 15:12:44 by cde-sede         ###   ########.fr       */
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

void	norm_vec(t_vec *v)
{
	double	l;

	l = (sqrt(v->x * v->x + v->y * v->y));
	v->x /= l;
	v->y /= l;
	v->x *= PLAYER_SPEED;
	v->y *= PLAYER_SPEED;
}

void	mouse_movement(t_data *data)
{
	int		x;
	int		y;
	double	dx;
	double	da;

	x = 0;
	y = 0;
	mlx_mouse_get_pos(data->mlx, data->win, &x, &y);
	if (data->mouse == 1)
		mlx_mouse_move(data->mlx, data->win,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	dx = (x - SCREEN_WIDTH / 2.0f) / (SCREEN_WIDTH / 2.f);
	da = pow(fabs(dx), 1.714f) * 40;
	if (data->mouse == 1 && x < SCREEN_WIDTH / 2)
		data->player_angle -= da * ROT_SPEED / 180.f * M_PI * 20;
	else if (data->mouse == 1 && x > SCREEN_WIDTH / 2)
		data->player_angle += da * ROT_SPEED / 180.f * M_PI * 20;
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
			data->ray_angle = 0.000001;
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
