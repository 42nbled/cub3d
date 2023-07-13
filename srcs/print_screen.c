/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:56:26 by nbled             #+#    #+#             */
/*   Updated: 2023/07/13 13:41:06 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void print_texture_north(t_data *data, t_vec *ray, double len, double start)
{
	double size;
    unsigned int *image_data;
    unsigned int *pixel;  // Pointer to the first pixel of the image
	int	i;
	double	column;
	
    size = len / data->north_texture->x;
    image_data = (unsigned int *)mlx_get_data_addr(data->north_texture->texture,
			&(data->north_texture->bits_per_pixel),
			&(data->north_texture->line_length),
			&(data->north_texture->endian));
			
	column = (ray->x / 50 -(double)(int)(ray->x /50)) / (1.0f / data->north_texture->y);
    pixel = image_data;
	pixel += (unsigned int)column;
	(void)ray;
	i = 0;

	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel+=data->north_texture->y;
			i ++;
		}
		pixel-=data->north_texture->y;
		i --;
	}

    while (i < data->north_texture->x && start + size * i < SCREEN_HEIGHT)
    {
        unsigned int color = *pixel;
        print_square(data, data->num_ray, data->num_ray, start + size * i, start + size * (i + 1), color);
        pixel+=data->north_texture->y;
		i ++;
    }
}

void print_texture_south(t_data *data, t_vec *ray, double len, double start)
{
	double size;
    unsigned int *image_data;
    unsigned int *pixel;  // Pointer to the first pixel of the image
	int	i;
	double	column;
	
    size = len / data->south_texture->x;
    image_data = (unsigned int *)mlx_get_data_addr(data->south_texture->texture,
			&(data->south_texture->bits_per_pixel),
			&(data->south_texture->line_length),
			&(data->south_texture->endian));
			
	column = (ray->x / 50 -(double)(int)(ray->x /50)) / (1.0f / data->south_texture->y);
    pixel = image_data;
	pixel += data->south_texture->x - 1 - (unsigned int)column;
	(void)ray;
	i = 0;
	
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel+=data->south_texture->y;
			i ++;
		}
		pixel-=data->south_texture->y;
		i --;
	}

    while (i < data->south_texture->x && start + size * i < SCREEN_HEIGHT)
    {
        unsigned int color = *pixel;
        print_square(data, data->num_ray, data->num_ray, start + size * i, start + size * (i + 1), color);
        pixel+=data->south_texture->y;
		i ++;
    }
}

void print_texture_west(t_data *data, t_vec *ray, double len, double start)
{
	double size;
    unsigned int *image_data;
    unsigned int *pixel;  // Pointer to the first pixel of the image
	int	i;
	double	column;
	
    size = len / data->west_texture->x;
    image_data = (unsigned int *)mlx_get_data_addr(data->west_texture->texture,
			&(data->west_texture->bits_per_pixel),
			&(data->west_texture->line_length),
			&(data->west_texture->endian));
			
	column = (ray->y / 50 -(double)(int)(ray->y /50)) / (1.0f / data->west_texture->y);
    pixel = image_data;
	pixel += data->west_texture->x - 1 - (unsigned int)column;
	(void)ray;
	i = 0;
	
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel+=data->west_texture->y;
			i ++;
		}
		pixel-=data->west_texture->y;
		i --;
	}

    while (i < data->west_texture->x && start + size * i < SCREEN_HEIGHT)
    {
        unsigned int color = *pixel;
        print_square(data, data->num_ray, data->num_ray, start + size * i, start + size * (i + 1), color);
        pixel+=data->west_texture->y;
		i ++;
    }
}

void print_texture_est(t_data *data, t_vec *ray, double len, double start)
{
	double size;
    unsigned int *image_data;
    unsigned int *pixel;  // Pointer to the first pixel of the image
	int	i;
	double	column;
	
    size = len / data->est_texture->x;
    image_data = (unsigned int *)mlx_get_data_addr(data->est_texture->texture,
			&(data->est_texture->bits_per_pixel),
			&(data->est_texture->line_length),
			&(data->est_texture->endian));
			
	column = (ray->y / 50 -(double)(int)(ray->y /50)) / (1.0f / data->est_texture->y);
    pixel = image_data;
	pixel += (unsigned int)column;
	(void)ray;
	i = 0;
		
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel+=data->est_texture->y;
			i ++;
		}
		pixel-=data->est_texture->y;
		i --;
	}

    while (i < data->est_texture->x && start + size * i < SCREEN_HEIGHT)
    {
        unsigned int color = *pixel;
        print_square(data, data->num_ray, data->num_ray, start + size * i, start + size * (i + 1), color);
        pixel+=data->est_texture->y;
		i ++;
    }
}

int	get_sprite(t_data *data, t_vec *ray, double len, double start)
{
	if ((double)((int)(ray->x)) != ray->x && data->ray_angle > 0)												// SOUTH
		print_texture_south(data, ray, len, start);
	if ((double)((int)(ray->x)) != ray->x && data->ray_angle < 0)												// NORTH
		print_texture_north(data, ray, len, start);
	if ((double)((int)(ray->y)) != ray->y && (data->ray_angle > M_PI / 2 || data->ray_angle < M_PI / 2 * -1))	// WEST
		print_texture_west(data, ray, len, start);
	if ((double)((int)(ray->y)) != ray->y && (data->ray_angle < M_PI / 2 && data->ray_angle > M_PI / 2 * -1))	// EST
		print_texture_est(data, ray, len, start);
	return (0);
}

int	print_screen(t_data *data, t_vec *ray)
{
	double	len;
	double	start;

	len = sqrt(pow(fabs(ray->x - data->player_x * 50), 2) + pow(fabs(ray->y - data->player_y * 50), 2));
	len *= cos(data->ray_angle - data->player_angle);
	len = (SCREEN_HEIGHT / len) * 42;
	start = (SCREEN_HEIGHT - len) / 2;
	if (len <= SCREEN_HEIGHT)
	{
		print_square(data, data->num_ray, data->num_ray, 0, start, 0x17202A);
		get_sprite(data, ray, len, start);
		print_square(data,data->num_ray,data->num_ray,start + len,SCREEN_HEIGHT, 0x17202A);
	}
	else
	{
		get_sprite(data, ray, len, start);
	}
	if (data->num_ray == SCREEN_WIDTH / 2)
		print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 0x000000);
	return (0);
}
