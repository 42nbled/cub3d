/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:00:46 by nbled             #+#    #+#             */
/*   Updated: 2023/07/06 17:48:03 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	print_square(t_data *data, int x_start, int x_end, int y_start, int y_end, int color)
{
	int	x;
	int	y;

	y = y_start;
	x = x_start;
	while (y <= y_end)
	{
		x = x_start;
		while (x <= x_end)
		{
			pixel_put(data, x++, y, color);
		}
		y++;
	}
	return (0);
}

void	print_map(t_data *data)
{
	int x;
	int	y;

	x = 0;
	y = 0;
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			if (data->map[y][x] == '1')
				print_square(data, x * 50 + 1, (x + 1) * 50 - 1, y * 50 + 1, (y + 1) * 50 - 1, 0x454545);
			else
				print_square(data, x * 50 + 1, (x + 1) * 50 - 1, y * 50 + 1, (y + 1) * 50 - 1, 0x999999);
			x++;
		}
		y++;
	}
}

void	print_player(t_data *data)
{
	print_square(data,
		data->player_x * 50 - 2,
		data->player_x * 50 + 2,
		data->player_y * 50 - 2,
		data->player_y * 50 + 2, 0xFFFF00);
}
