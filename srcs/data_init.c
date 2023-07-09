/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/09 00:06:14 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = ft_split("11111111n10100001n10100001n10100001n10000001n10000101n10000001n11111111n", 'n');
	//data->map = ft_split("11111111n11000001n10000111n10001101n10001001n10000101n10000001n11111111n", 'n');
	//data->map = ft_split("00000000n01111110n01010010n01000010n01001010n01000010n01111110n00000000n", 'n');
	data->map = ft_split("11111111n10001001n10111011n10101011n10000001n10101111n10100001n11111111n", 'n');
	//data->map = ft_split("11111111n10110001n10110111n10000111n11100001n11101101n10001101n11111111n", 'n');
	for (int i = 0; i < 6; i++)
		data->keys[i] = 0;
	data->mouse = 0;
	data->minimap = 0;
	data->player_x = 5.5;
	data->player_y = 4.5;
	data->player_angle = 0.0f;
}
