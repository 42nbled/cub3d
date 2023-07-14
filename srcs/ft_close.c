/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:49 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 14:01:15 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->north_texture->texture);
	mlx_destroy_image(data->mlx, data->south_texture->texture);
	mlx_destroy_image(data->mlx, data->est_texture->texture);
	mlx_destroy_image(data->mlx, data->west_texture->texture);
	mlx_destroy_image(data->mlx, data->img);
	free(data->north_texture);
	free(data->south_texture);
	free(data->est_texture);
	free(data->west_texture);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_map(data->map);
	free(data->mlx);
	exit(0);
}
