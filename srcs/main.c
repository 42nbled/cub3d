/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 06:59:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 16:10:44 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (data->mouse == 0 && keycode == 1)
	{
		data->mouse = 1;
		mlx_mouse_hide(data->mlx, data->win);
	}
	return (0);
}

int	is_file_empty(char *argv)
{
	int		fd;
	char	str[1];

	fd = open(argv, O_RDONLY);
	if (!read(fd, str, 1))
	{
		printf("Error ! Empty file\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	map_data;

	if (SCREEN_WIDTH == 0 || SCREEN_WIDTH > 1920
		|| SCREEN_HEIGHT == 0 || SCREEN_HEIGHT > 1080)
		return (printf("Invalid screen parameters"), 1);
	if (ac != 2)
		return (printf("Not enough arguments"), 1);
	if (is_file_empty(av[1]) == 0)
		return (printf("Empty file"), 1);
	map_data = (t_map){0};
	if (data_init(&data, &map_data, av[1]))
	{
		printf("Parsing error");
		return (1);
	}
	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_release, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_press, &data);
	mlx_hook(data.win, 17, 0, ft_close, &data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
}
