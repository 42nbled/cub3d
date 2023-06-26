/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 06:59:35 by nbled             #+#    #+#             */
/*   Updated: 2023/06/26 16:12:22 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// ----- DESSIN ---------------------------

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_square(t_data *data, int x_start, int x_end, int y_start, int y_end, int color)
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
}

void	print_black(t_data *data, int x_start, int x_end, int y_start, int y_end, int color)
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
			if (x == x_start || x == x_end || y == y_start || y == y_end)
				pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
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
			{
				print_square(data, x * 50 + 1, (x + 1) * 50 - 1, y * 50 + 1, (y + 1) * 50 - 1, 0x454545);
				print_black(data, x * 50, (x + 1) * 50, y * 50, (y + 1) * 50, 0x000000);
			}
			else
			{
				print_square(data, x * 50 + 1, (x + 1) * 50 - 1, y * 50 + 1, (y + 1) * 50 - 1, 0x999999);
				print_black(data, x * 50, (x + 1) * 50, y * 50, (y + 1) * 50, 0x000000);
			}
			x++;
		}
		y++;
	}
}

void	print_player(t_data *data)
{
	print_square(data,
		data->player_x * 50 - 5,
		data->player_x * 50 + 5,
		data->player_y * 50 - 5,
		data->player_y * 50 + 5, 0xFFFF00);
}

// ---- RAYCASTING ------------------------

void	calc_droite(t_data *data, t_vec *pos)
{
	double	m;
	double	c;

	m = (data->player_y + sin(data->player_angle) - data->player_y) / (data->player_x + cos(data->player_angle) - data->player_x);
	c = (data->player_y - m * data->player_x) * 50;
	pos->y = m * pos->x + c;
}

void	vec_add(t_vec *a, t_vec b)
{
	a->x += b.x;
	a->y += b.y;
}

void	vec_sub(t_vec *a, t_vec b)
{
	a->x -= b.x;
	a->y -= b.y;
}

t_vec	get_dist(t_data *data, t_vec dir)
{
	t_vec	pos;

	pos.x = (double)((int)(data->player_x + 1) * 50);
	calc_droite(data, &pos);
	if (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
		if (data->map[(int)(pos.y /50)][(int)(pos.x /50)] == '1')
			return (pos);
	dir.x = pos.x;
	dir.y = pos.y;
	pos.x += 50;
	calc_droite(data, &pos);
	dir.x = pos.x - dir.x;
	dir.y = pos.y - dir.y;
	while (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
	{
		if (data->map[(int)(pos.y /50)][(int)(pos.x /50)] == '1')
			return (pos);
		vec_add(&pos, dir);
	}
	return (pos);
}

t_vec	get_dist_negative(t_data *data, t_vec dir)
{
	t_vec	pos;

	pos.x = (double)((int)(data->player_x) * 50);
	calc_droite(data, &pos);
	if (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
		if (data->map[(int)(pos.y /50)][(int)(pos.x /50) - 1] == '1')
			return (pos);
	dir.x = pos.x;
	dir.y = pos.y;
	pos.x -= 50;
	calc_droite(data, &pos);
	dir.x = pos.x - dir.x;
	dir.y = pos.y - dir.y;
	while (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
	{
		if (data->map[(int)(pos.y /50) ][(int)(pos.x /50) - 1] == '1')
			return (pos);
		vec_add(&pos, dir);
	}
	return (pos);
}

/*
printf("pos[%f][%f]\t", pos.y / 50, pos.x / 50 - 1);
		printf("%c\t", data->map[(int)(pos.y /50) - 1][(int)(pos.x /50)]);
		printf("[%d][%d]\n", (int)(pos.y /50) - 1, (int)(pos.x /50));
*/

int	raycasting(t_data *data)
{
	t_vec	dir;
	t_vec	pos;
	t_vec	end;

	dir.x = cos(data->player_angle);
	dir.y = sin(data->player_angle);
	if (dir.x > 0)
	{
		end = get_dist(data, dir);
		dir.x = cos(data->player_angle);
		dir.y = sin(data->player_angle);
		pos.x = data->player_x * 50;
		pos.y = data->player_y * 50;
		while (pos.x >= 0 && pos.x < end.x && pos.y > 0 && pos.y < 400)
		{
			pixel_put(data, pos.x, pos.y, 0xFF0000);
			vec_add(&pos, dir);
		}
	}
	else
	{
		end = get_dist_negative(data, dir);
		dir.x = cos(data->player_angle);
		dir.y = sin(data->player_angle);
		pos.x = data->player_x * 50;
		pos.y = data->player_y * 50;
		while (pos.x > end.x && pos.x < 400 && pos.y > 0 && pos.y < 400)
		{
			pixel_put(data, pos.x, pos.y, 0xFF0000);
			vec_add(&pos, dir);
		}
	}
	return (0);
}

// ----- SPLIT ---------------------------

int	ft_count_words(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

int	ft_str_len(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] == c)
		i++;
	while (s[i + j] && s[i + j] != c)
		j++;
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		size;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	size = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		tab[i] = malloc(ft_str_len(s + j, c) + 1);
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
			tab[i][k++] = s[j++];
		tab[i][k] = '\0';
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

// ----- CODE ---------------------------

int	loop(t_data *data)
{
	print_map(data);
	print_player(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 400, 400, "cub3d");
	data->img = mlx_new_image(data->mlx, 400, 400);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = ft_split("11111111n10100001n10100001n10100001n10000001n10000101n10000001n11111111n", 'n');
	data->player_x = 6.5;
	data->player_y = 5.5;
	data->player_angle = 3.65f;
}

int	ft_close(t_data *data)
{
	(void)data;
	exit(0);
}

int	key_hook(int keycode, t_data *data)
{
	double	speed;
	double	rotation_speed;
	double	dx;
	double	dy;

	speed = 0.08;
	rotation_speed = 2;
	dx = cos(data->player_angle);
	dy = sin(data->player_angle);

	if (keycode == KEY_W)
	{
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (keycode == KEY_S)
	{
		data->player_x -= dx * speed;
		data->player_y -= dy * speed;
	}
	if (keycode == KEY_A)
	{
		dx = cos(data->player_angle - M_PI_2 );
		dy = sin(data->player_angle - M_PI_2 );
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (keycode == KEY_D)
	{
		dx = cos(data->player_angle + M_PI_2 );
		dy = sin(data->player_angle + M_PI_2 );
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (keycode == KEY_Q)
		data->player_angle -= rotation_speed / 180.f * M_PI;
	else if (keycode == KEY_E)
		data->player_angle += rotation_speed / 180.f * M_PI;
	if (keycode == 65307)
		ft_close(data);
	return (0);
}

int	main(void)
{
	t_data	data;

	data_init(&data);
	mlx_hook(data.win, KeyPress, KeyPressMask, key_hook, &data);
	mlx_hook(data.win, 17, 0, ft_close, &data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
}