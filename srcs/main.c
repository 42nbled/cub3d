/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 06:59:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/09 03:36:08 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_hook(int keycode, int x,int y, t_data *data)
{
	(void)x;
	(void)y;
	if (data->mouse == 0 && keycode == 1)
	{
		data->mouse = 1;
		mlx_mouse_hide(data->mlx,data->win);
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data_init(&data);
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_release, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_press, &data);
	mlx_hook(data.win, 17, 0, ft_close, &data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
}