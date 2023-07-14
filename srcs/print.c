/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:00:46 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 14:45:51 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < SCREEN_WIDTH && y < SCREEN_HEIGHT)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	print_line(t_data *data, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y <= y_end)
		pixel_put(data, data->num_ray, y++, color);
	return (0);
}

void	while_print_map(t_data *data, double pos_y, int screen_y)
{
	int		screen_x;
	double	pos_x;

	screen_x = 0;
	pos_x = -5;
	while (screen_x < 100)
	{
		if (screen_y == 0 || screen_x == 0
			|| screen_y == 99 || screen_x == 99)
			pixel_put(data, screen_x + 25, screen_y + 25, 0xFFFFFF);
		else if ((data->player_x + pos_x) >= 0
			&& (data->player_y + pos_y) >= 0
			&& (int)(data->player_x + pos_x) < data->map_widht
			&& (int)(data->player_y + pos_y) < data->map_height
			&& data->map[(int)(data->player_y
					+ pos_y)][(int)(data->player_x + pos_x)] == '1')
			pixel_put(data, screen_x + 25, screen_y + 25, 0x999999);
		pos_x += 0.1;
		screen_x++;
	}
}

void	print_map(t_data *data)
{
	int		screen_y;
	double	pos_y;

	screen_y = 0;
	pos_y = -5;
	while (screen_y < 100)
	{
		while_print_map(data, pos_y, screen_y);
		pos_y += 0.1;
		screen_y++;
	}
}

void	print_player(t_data *data)
{
	int	x;
	int	y;

	y = 73;
	x = 73;
	while (y <= 77)
	{
		x = 73;
		while (x <= 77)
			pixel_put(data, x++, y, 0xFF0000);
		y++;
	}
}
