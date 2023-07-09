/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:55:50 by nbled             #+#    #+#             */
/*   Updated: 2023/07/06 22:00:40 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
