/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:49 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 18:49:54 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	clear_mlx(t_data *data, t_map *map_data)
{
	if (data->north_texture.texture)
		mlx_destroy_image(data->mlx, data->north_texture.texture);
	if (data->south_texture.texture)
		mlx_destroy_image(data->mlx, data->south_texture.texture);
	if (data->est_texture.texture)
		mlx_destroy_image(data->mlx, data->est_texture.texture);
	if (data->west_texture.texture)
		mlx_destroy_image(data->mlx, data->west_texture.texture);
	free_tex_str(map_data);
	mlx_destroy_image(data->mlx, data->img);
	free_map(data->map);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

void	free_tex_str(t_map *map_data)
{
	if (map_data->textures.nstr)
		free(map_data->textures.nstr);
	if (map_data->textures.sstr)
		free(map_data->textures.sstr);
	if (map_data->textures.estr)
		free(map_data->textures.estr);
	if (map_data->textures.wstr)
		free(map_data->textures.wstr);
	if (map_data->textures.fstr)
		free(map_data->textures.fstr);
	if (map_data->textures.cstr)
		free(map_data->textures.cstr);
}

int	ft_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->north_texture.texture);
	mlx_destroy_image(data->mlx, data->south_texture.texture);
	mlx_destroy_image(data->mlx, data->est_texture.texture);
	mlx_destroy_image(data->mlx, data->west_texture.texture);
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free_map(data->map);
	free(data->mlx);
	exit(0);
}
