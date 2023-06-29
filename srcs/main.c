/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 06:59:35 by nbled             #+#    #+#             */
/*   Updated: 2023/06/29 15:39:34 by nbled            ###   ########.fr       */
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
				print_square(data, x * 10 + 1, (x + 1) * 10 - 1, y * 10 + 1, (y + 1) * 10 - 1, 0x454545);
			else
				print_square(data, x * 10 + 1, (x + 1) * 10 - 1, y * 10 + 1, (y + 1) * 10 - 1, 0x999999);
			x++;
		}
		y++;
	}
}

void	print_player(t_data *data)
{
	print_square(data,
		data->player_x * 10 - 2,
		data->player_x * 10 + 2,
		data->player_y * 10 - 2,
		data->player_y * 10 + 2, 0xFF0000);
}

// ---- RAYCASTING ------------------------

void	vec_add(t_vec *a, t_vec b)
{
	a->x += b.x;
	a->y += b.y;
}

void	calc_droite_x(t_data *data, t_vec *pos)
{
	double	m;
	double	c;

	m = sin(data->ray_angle) / cos(data->ray_angle);
	c = (data->player_y - m * data->player_x) * 50;
	pos->y = m * pos->x + c;
}

t_vec	get_dist_x(t_data *data, t_vec dir, int signe1, int signe2)
{
	t_vec	pos;

	pos.x = (double)((int)(data->player_x + 1 - signe2) * 50);
	calc_droite_x(data, &pos);
	if (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
		if (data->map[(int)(pos.y /50)][(int)(pos.x /50) - signe2] == '1')
			return (pos);
	dir.x = pos.x;
	dir.y = pos.y;
	pos.x += 50 * signe1;
	calc_droite_x(data, &pos);
	dir.x = pos.x - dir.x;
	dir.y = pos.y - dir.y;
	while (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
	{
		if (data->map[(int)(pos.y /50)][(int)(pos.x /50) - signe2] == '1')
			return (pos);
		vec_add(&pos, dir);
	}
	return (pos);
}

void calc_droite_y(t_data *data, t_vec *pos)
{
    double m;
    double c;

    m = cos(data->ray_angle) / sin(data->ray_angle);
    c = (data->player_x - m * data->player_y) * 50;
    pos->x = m * pos->y + c;
}

t_vec get_dist_y(t_data *data, t_vec dir, int signe1, int signe2)
{
	t_vec	pos;

    pos.y = (double)((int)(data->player_y + 1 - signe2) * 50);
	calc_droite_y(data, &pos);
	if (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
		if (data->map[(int)(pos.y / 50) - signe2][(int)(pos.x / 50)] == '1')
			return (pos);
    dir.x = pos.x;
    dir.y = pos.y;
    pos.y += 50 * signe1;
    calc_droite_y(data, &pos);
    dir.x = pos.x - dir.x;
    dir.y = pos.y - dir.y;
    while (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
    {
        if (data->map[(int)(pos.y / 50) - signe2][(int)(pos.x / 50)] == '1')
            return (pos);
        vec_add(&pos, dir);
    }
    return (pos);
}

t_vec is_lower_vec(t_data *data, t_vec *end_x, t_vec *end_y)
{
    double dist_x;
    double dist_y;

    dist_x = sqrt(pow(fabs(end_x->x - data->player_x * 50), 2) + pow(fabs(end_x->y - data->player_y * 50), 2));
    dist_y = sqrt(pow(fabs(end_y->x - data->player_x * 50), 2) + pow(fabs(end_y->y - data->player_y * 50), 2));
    if (dist_x < dist_y)
        return *end_x;
    return *end_y;
}

int	raycasting(t_data *data)
{
	t_vec	dir;
	//t_vec	pos;
	t_vec	end_x;
	t_vec	end_y;

	dir.x = cos(data->ray_angle);
	dir.y = sin(data->ray_angle);
	if (dir.x > 0)
		end_x = get_dist_x(data, dir, 1, 0);
	else
		end_x = get_dist_x(data, dir, -1, 1);
	if (dir.y > 0)
		end_y = get_dist_y(data, dir, 1, 0);
	else
		end_y = get_dist_y(data, dir, -1, 1);
	end_x = is_lower_vec(data, &end_x, &end_y);
	
	/*
	pos.x = data->player_x * 50;
	pos.y = data->player_y * 50;
	if (dir.x > 0)
	{
		while (pos.x >= 0 && pos.x < end_x.x && pos.y > 0 && pos.y < 400)
		{
			pixel_put(data, pos.x, pos.y, 0xFF0000);
			vec_add(&pos, dir);
		}
	}
	else
	{
		while (pos.x > end_x.x && pos.x < 400 && pos.y > 0 && pos.y < 400)
		{
			pixel_put(data, pos.x, pos.y, 0xFF0000);
			vec_add(&pos, dir);
		}
	}*/

	double	len;
	double	start;

	len = sqrt(pow(fabs(end_x.x - data->player_x * 50), 2) + pow(fabs(end_x.y - data->player_y * 50), 2));
	len *= cos(data->ray_angle - data->player_angle);
	len = (SCREEN_HEIGHT / len) * 16;
	start = (SCREEN_HEIGHT - len) / 2;
	print_square(data,
		data->num_ray,
		data->num_ray,
		0,
		start, 0x0000FF);
	if (start + len < SCREEN_HEIGHT)
	{
		if (start + len < SCREEN_HEIGHT && end_x.x == (double)((int)end_x.x))
			print_square(data, data->num_ray, data->num_ray, start, start + len, 0x44FE31);
		else
			print_square(data,data->num_ray,data->num_ray,start,start + len, 0x3EDC2E);
	}
	else
	{
		if (end_x.x == (double)((int)end_x.x))
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_LENGTH, 0x44FE31);
		else
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_LENGTH, 0x3EDC2E);
	}
	print_square(data,data->num_ray,data->num_ray,start + len,SCREEN_LENGTH, 0xDC7633);

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
	double	fov;
	double	radian;

	radian = 0.0174533;
	fov = 45 * radian;
	data->ray_angle = data->player_angle - fov;
	data->num_ray = 0;
	while (data->ray_angle <= data->player_angle + fov)
	{
		raycasting(data);
		data->ray_angle += radian / 8;
		data->num_ray ++;
	}
	print_map(data);
	print_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}//*/

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_HEIGHT, SCREEN_LENGTH, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_HEIGHT, SCREEN_LENGTH);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = ft_split("11111111n10100001n10100001n10100001n10000001n10000101n10000001n11111111n", 'n');
	//data->map = ft_split("00000000n01111110n01010010n01000010n01001010n01000010n01111110n00000000n", 'n');
	data->map = ft_split("11111111n10001001n10111011n10101011n10000001n10101111n10100001n11111111n", 'n');
	data->map = ft_split("11111111n10110001n10110111n10000111n11100001n11101101n10001101n11111111n", 'n');
	data->player_x = 5.5;
	data->player_y = 4.5;
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
	rotation_speed = 4;
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