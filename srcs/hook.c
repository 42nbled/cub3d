/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:57 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 18:25:08 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[UP] = 1;
	if (keycode == KEY_S)
		data->keys[DOWN] = 1;
	if (keycode == KEY_A)
		data->keys[STRAF_L] = 1;
	if (keycode == KEY_D)
		data->keys[STRAF_R] = 1;
	if (keycode == KEY_LEFT)
		data->keys[LEFT] = 1;
	if (keycode == KEY_RIGHT)
		data->keys[RIGHT] = 1;
	if (keycode == KEY_M && data->minimap == 0)
		data->minimap = 1;
	else if (keycode == KEY_M && data->minimap == 1)
		data->minimap = 0;
	else if (keycode == KEY_ESC)
		ft_close(data);
	return (0);
}

int	handle_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[UP] = 0;
	if (keycode == KEY_S)
		data->keys[DOWN] = 0;
	if (keycode == KEY_A)
		data->keys[STRAF_L] = 0;
	if (keycode == KEY_D)
		data->keys[STRAF_R] = 0;
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		data->keys[LEFT] = 0;
	if (keycode == KEY_E || keycode == KEY_RIGHT)
		data->keys[RIGHT] = 0;
	return (0);
}
