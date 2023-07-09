/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:56:26 by nbled             #+#    #+#             */
/*   Updated: 2023/07/09 04:37:37 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_sprite(t_data *data, t_vec *ray)
{
	if ((double)((int)(ray->x)) != ray->x && data->ray_angle > 0)												// SOUTH
		print_square(data, data->num_ray, data->num_ray, 5, 5, 0xFF0000);
	if ((double)((int)(ray->x)) != ray->x && data->ray_angle < 0)												// NORTH
		print_square(data, data->num_ray, data->num_ray, 5, 5, 0x00FF00);
	if ((double)((int)(ray->y)) != ray->y && (data->ray_angle > M_PI / 2 || data->ray_angle < M_PI / 2 * -1))	// EST
		print_square(data, data->num_ray, data->num_ray, 5, 5, 0x00FFFF);
	if ((double)((int)(ray->y)) != ray->y && (data->ray_angle < M_PI / 2 && data->ray_angle > M_PI / 2 * -1))	// WEST
		print_square(data, data->num_ray, data->num_ray, 5, 5, 0xFFFF00);
		
	if (data->num_ray == SCREEN_WIDTH / 2)
		printf("%f\t%f\n",ray->x / 50-(double)(int)(ray->x /50),ray->y / 50 - (double)(int)(ray->y /50));
	return (0);
}

int	print_screen(t_data *data, t_vec *ray)
{
	double	len;
	double	start;

	len = sqrt(pow(fabs(ray->x - data->player_x * 50), 2) + pow(fabs(ray->y - data->player_y * 50), 2));
	len *= cos(data->ray_angle - data->player_angle);
	len = (SCREEN_HEIGHT / len) * 16;
	start = (SCREEN_HEIGHT - len) / 2;
	if (len <= SCREEN_HEIGHT)
	{
		print_square(data, data->num_ray, data->num_ray, 0, start, 0x17202A);
		if (0x17202A + len < 1515766)
			print_square(data, data->num_ray, data->num_ray, start, start + len, 0x17202A + len);
		else
			print_square(data, data->num_ray, data->num_ray, start, start + len, 1515766);
		print_square(data,data->num_ray,data->num_ray,start + len,SCREEN_HEIGHT, 0x17202A);
	}
	else
	{
		
		if (ray->x == (double)((int)ray->x))
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 1515766 );
		else
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 1515766);
	}
	if (data->num_ray == SCREEN_WIDTH / 2)
		print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 0x000000);
	get_sprite(data, ray);
	return (0);
}
