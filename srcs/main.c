/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 06:59:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/06 20:11:39 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
	t_vec	tmp;

    pos.y = (double)((int)(data->player_y + 1 - signe2) * 50);
	calc_droite_y(data, &pos);
	if (pos.x >= 0 && pos.x < 400 && pos.y > 0 && pos.y < 400)
		if (data->map[(int)(pos.y / 50) - signe2][(int)(pos.x / 50)] == '1')
			return (pos);
    tmp.x = pos.x;
    tmp.y = pos.y;
    pos.y += 50 * signe1;
    calc_droite_y(data, &pos);
    dir.x = pos.x - tmp.x;
    dir.y = pos.y - tmp.y;
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

t_vec	raycasting(t_data *data)
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
	return (is_lower_vec(data, &end_x, &end_y));
	
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
}

int	print_screen(t_data *data, t_vec *ray)
{
	double	len;
	double	start;

	len = sqrt(pow(fabs(ray->x - data->player_x * 50), 2) + pow(fabs(ray->y - data->player_y * 50), 2));
	len *= cos(data->ray_angle - data->player_angle);
	len = (SCREEN_HEIGHT / len) * 16;
	start = (SCREEN_HEIGHT - len) / 2;
	if (len <= SCREEN_HEIGHT)
	{
		print_square(data, data->num_ray, data->num_ray, 0, start, 0x17202A);
		if (0x17202A + len < 1515766)
		{
			print_square(data, data->num_ray, data->num_ray, start, start + len, 0x17202A + len);
		}
		else
		{
			print_square(data, data->num_ray, data->num_ray, start, start + len, 1515766);
		}
		print_square(data,data->num_ray,data->num_ray,start + len,SCREEN_HEIGHT, 0x17202A);
	}
	else
	{
		
		if (ray->x == (double)((int)ray->x))
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 1515766 );
		else
			print_square(data,data->num_ray,data->num_ray,0,SCREEN_HEIGHT, 1515766);
	}
	return (0);
}

// ----- CODE ---------------------------

void	get_angle(t_data *data)
{
	t_vec	focal;
	t_vec	range;

	focal.x = cos(data->player_angle) + data->player_x;
	focal.y = sin(data->player_angle) + data->player_y;
	focal.x += cos(data->player_angle - M_PI_2);
	focal.y += sin(data->player_angle - M_PI_2);
	range.x = cos(data->player_angle - M_PI_2) / (SCREEN_WIDTH / 2);
	range.y = sin(data->player_angle - M_PI_2) / (SCREEN_WIDTH / 2);
	focal.x -= range.x * data->num_ray;
	focal.y -= range.y * data->num_ray;
	data->ray_angle = atan2(focal.y - data->player_y, focal.x - data->player_x);
}

void	player_movement(t_data *data)
{
	double	speed;
	double	rotation_speed;
	double	dx;
	double	dy;

	speed = 0.02;
	rotation_speed = 1;
	dx = cos(data->player_angle);
	dy = sin(data->player_angle);

	if (data->keys[UP])
	{
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (data->keys[DOWN])
	{
		data->player_x -= dx * speed;
		data->player_y -= dy * speed;
	}
	if (data->keys[STRAF_L])
	{
		dx = cos(data->player_angle - M_PI_2 );
		dy = sin(data->player_angle - M_PI_2 );
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (data->keys[STRAF_R])
	{
		dx = cos(data->player_angle + M_PI_2 );
		dy = sin(data->player_angle + M_PI_2 );
		data->player_x += dx * speed;
		data->player_y += dy * speed;
	}
	if (data->keys[LEFT])
		data->player_angle -= rotation_speed / 180.f * M_PI;
	else if (data->keys[RIGHT])
		data->player_angle += rotation_speed / 180.f * M_PI;
}

int	loop(t_data *data)
{
	t_vec	ray;
	
	player_movement(data);
	data->num_ray = 0;
	while (data->num_ray < SCREEN_WIDTH)
	{
		get_angle(data);
		ray = raycasting(data);
		print_screen(data, &ray);
		data->num_ray ++;
	}
	//print_map(data);
	//print_player(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void	data_init(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->map = ft_split("11111111n10100001n10100001n10100001n10000001n10000101n10000001n11111111n", 'n');
	//data->map = ft_split("00000000n01111110n01010010n01000010n01001010n01000010n01111110n00000000n", 'n');
	//data->map = ft_split("11111111n10001001n10111011n10101011n10000001n10101111n10100001n11111111n", 'n');
	//data->map = ft_split("11111111n10110001n10110111n10000111n11100001n11101101n10001101n11111111n", 'n');
	for (int i = 0; i < 6; i++)
		data->keys[i] = 0;
	data->player_x = 5.5;
	data->player_y = 4.5;
	data->player_angle = 0.0f;
}

int	ft_close(t_data *data)
{
	(void)data;
	exit(0);
}

int handle_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[UP] = 1;
	if (keycode == KEY_S)
		data->keys[DOWN] = 1;
	if (keycode == KEY_A)
		data->keys[STRAF_L] = 1;
	if (keycode == KEY_D)
		data->keys[STRAF_R] = 1;
	if (keycode == KEY_Q)
		data->keys[LEFT] = 1;
	else if (keycode == KEY_E)
		data->keys[RIGHT] = 1;
	if (keycode == 65307)
		ft_close(data);
	return (0);
}
int handle_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys[UP] = 0;
	if (keycode == KEY_S)
		data->keys[DOWN] = 0;
	if (keycode == KEY_A)
		data->keys[STRAF_L] = 0;
	if (keycode == KEY_D)
		data->keys[STRAF_R] = 0;
	if (keycode == KEY_Q)
		data->keys[LEFT] = 0;
	else if (keycode == KEY_E)
		data->keys[RIGHT] = 0;
	return (0);
}
int	main(void)
{
	t_data	data;

	data_init(&data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_release, &data);
	mlx_hook(data.win, KeyPress, KeyPressMask, handle_press, &data);
	mlx_hook(data.win, 17, 0, ft_close, &data);
	mlx_loop_hook(data.mlx, loop, &data);
	mlx_loop(data.mlx);
}