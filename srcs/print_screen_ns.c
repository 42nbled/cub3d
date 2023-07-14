/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_ns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:31:22 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 15:33:13 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	*get_pixel_north(t_data *data, t_vec *ray)
{
	unsigned int	*image_data;
	unsigned int	*pixel;
	double			column;

	image_data = (unsigned int *)mlx_get_data_addr(data->north_texture->texture,
			&(data->north_texture->bits_per_pixel),
			&(data->north_texture->line_length),
			&(data->north_texture->endian));
	column = (ray->x / 50 - (double)(int)(ray->x / 50))
		/ (1.0f / data->north_texture->y);
	pixel = image_data;
	pixel += (unsigned int)column;
	return (pixel);
}

void	print_texture_north(t_data *data, t_vec *ray, double len, double start)
{
	double			size;
	unsigned int	*pixel;
	unsigned int	color;
	int				i;

	size = len / data->north_texture->x;
	pixel = get_pixel_north(data, ray);
	i = 0;
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel += data->north_texture->y;
			i++;
		}
		pixel -= data->north_texture->y;
		i--;
	}
	while (i < data->north_texture->x && start + size * i < SCREEN_HEIGHT)
	{
		color = *pixel;
		print_line(data, start + size * i, start + size * (i + 1), color);
		pixel += data->north_texture->y;
		i++;
	}
}

unsigned int	*get_pixel_south(t_data *data, t_vec *ray)
{
	unsigned int	*image_data;
	unsigned int	*pixel;
	double			column;

	image_data = (unsigned int *)mlx_get_data_addr(data->south_texture->texture,
			&(data->south_texture->bits_per_pixel),
			&(data->south_texture->line_length),
			&(data->south_texture->endian));
	column = (ray->x / 50 - (double)(int)(ray->x / 50))
		/ (1.0f / data->south_texture->y);
	pixel = image_data;
	pixel += data->south_texture->x - 1 - (unsigned int)column;
	return (pixel);
}

void	print_texture_south(t_data *data, t_vec *ray, double len, double start)
{
	double			size;
	unsigned int	*pixel;
	unsigned int	color;
	int				i;

	size = len / data->south_texture->x;
	pixel = get_pixel_south(data, ray);
	i = 0;
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel += data->south_texture->y;
			i ++;
		}
		pixel -= data->south_texture->y;
		i --;
	}
	while (i < data->south_texture->x && start + size * i < SCREEN_HEIGHT)
	{
		color = *pixel;
		print_line(data, start + size * i, start + size * (i + 1), color);
		pixel += data->south_texture->y;
		i ++;
	}
}
