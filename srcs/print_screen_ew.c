/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_screen_ew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:32:05 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 15:32:57 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	*get_pixel_west(t_data *data, t_vec *ray)
{
	unsigned int	*image_data;
	unsigned int	*pixel;
	double			column;

	image_data = (unsigned int *)mlx_get_data_addr(data->west_texture->texture,
			&(data->west_texture->bits_per_pixel),
			&(data->west_texture->line_length),
			&(data->west_texture->endian));
	column = (ray->y / 50 - (double)(int)(ray->y / 50))
		/ (1.0f / data->west_texture->y);
	pixel = image_data;
	pixel += data->west_texture->x - 1 - (unsigned int)column;
	return (pixel);
}

void	print_texture_west(t_data *data, t_vec *ray, double len, double start)
{
	double			size;
	unsigned int	*pixel;
	unsigned int	color;
	int				i;

	size = len / data->west_texture->x;
	pixel = get_pixel_west(data, ray);
	i = 0;
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel += data->west_texture->y;
			i ++;
		}
		pixel -= data->west_texture->y;
		i --;
	}
	while (i < data->west_texture->x && start + size * i < SCREEN_HEIGHT)
	{
		color = *pixel;
		print_line(data, start + size * i, start + size * (i + 1), color);
		pixel += data->west_texture->y;
		i ++;
	}
}

unsigned int	*get_pixel_est(t_data *data, t_vec *ray)
{
	unsigned int	*image_data;
	unsigned int	*pixel;
	double			column;

	image_data = (unsigned int *)mlx_get_data_addr(data->est_texture->texture,
			&(data->est_texture->bits_per_pixel),
			&(data->est_texture->line_length),
			&(data->est_texture->endian));
	column = (ray->y / 50 - (double)(int)(ray->y / 50))
		/ (1.0f / data->est_texture->y);
	pixel = image_data;
	pixel += (unsigned int)column;
	return (pixel);
}

void	print_texture_est(t_data *data, t_vec *ray, double len, double start)
{
	double			size;
	unsigned int	*pixel;
	unsigned int	color;
	int				i;

	size = len / data->est_texture->x;
	pixel = get_pixel_est(data, ray);
	i = 0;
	if (start + size * i < 0)
	{
		while (start + size * i < 0)
		{
			pixel += data->est_texture->y;
			i ++;
		}
		pixel -= data->est_texture->y;
		i --;
	}
	while (i < data->est_texture->x && start + size * i < SCREEN_HEIGHT)
	{
		color = *pixel;
		print_line(data, start + size * i, start + size * (i + 1), color);
		pixel += data->est_texture->y;
		i ++;
	}
}
