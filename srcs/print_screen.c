/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:56:26 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 15:54:24 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_sprite(t_data *data, t_vec *ray, double len, double start)
{
	if ((double)((int)(ray->x)) != ray->x
		&& data->ray_angle > 0)
		print_texture_south(data, ray, len, start);
	if ((double)((int)(ray->x)) != ray->x
		&& data->ray_angle < 0)
		print_texture_north(data, ray, len, start);
	if ((double)((int)(ray->y)) != ray->y
		&& (data->ray_angle > M_PI / 2 || data->ray_angle < M_PI / 2 * -1))
		print_texture_west(data, ray, len, start);
	if ((double)((int)(ray->y)) != ray->y
		&& (data->ray_angle < M_PI / 2 && data->ray_angle > M_PI / 2 * -1))
		print_texture_est(data, ray, len, start);
	return (0);
}

int	print_screen(t_data *data, t_vec *ray)
{
	double	len;
	double	start;

	len = sqrt(pow(fabs(ray->x - data->player_x * 50), 2)
			+ pow(fabs(ray->y - data->player_y * 50), 2));
	len *= cos(data->ray_angle - data->player_angle);
	len = (SCREEN_HEIGHT / len) * 42;
	start = (SCREEN_HEIGHT - len) / 2;
	if (len <= SCREEN_HEIGHT)
	{
		print_line(data, 0, start, data->ceil);
		get_sprite(data, ray, len, start);
		print_line(data, start + len, SCREEN_HEIGHT, data->floor);
	}
	else
		get_sprite(data, ray, len, start);
	return (0);
}
