/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 18:49:50 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	malloc_textures(t_data *data)
{
	data->north_texture = (t_texture){0};
	data->south_texture = (t_texture){0};
	data->est_texture = (t_texture){0};
	data->west_texture = (t_texture){0};
}

int	init_textures(t_data *data, t_map *map_data)
{
	data->north_texture.texture = mlx_xpm_file_to_image(data->mlx,
			map_data->textures.nstr, &data->north_texture.x,
			&data->north_texture.y);
	if (!data->north_texture.texture)
		return (1);
	data->south_texture.texture = mlx_xpm_file_to_image(data->mlx,
			map_data->textures.sstr, &data->south_texture.x,
			&data->south_texture.y);
	if (!data->south_texture.texture)
		return (1);
	data->est_texture.texture = mlx_xpm_file_to_image(data->mlx,
			map_data->textures.estr, &data->est_texture.x,
			&data->est_texture.y);
	if (!data->est_texture.texture)
		return (1);
	data->west_texture.texture = mlx_xpm_file_to_image(data->mlx,
			map_data->textures.wstr, &data->west_texture.x,
			&data->west_texture.y);
	if (!data->west_texture.texture)
		return (1);
	free_tex_str(map_data);
	return (0);
}

int	set_var(t_data *data, t_map *map_data)
{
	data->minimap = 0;
	data->map_widht = map_data->width;
	data->map_height = map_data->height;
	data->map = map_data->map;
	if (init_textures(data, map_data))
		return (1);
	data->player_x = map_data->start_pos.x;
	data->player_y = map_data->start_pos.y;
	data->player_angle = map_data->start_angle;
	data->player_angle += 0.01f;
	data->floor = map_data->textures.floor;
	data->ceil = map_data->textures.ceil;
	return (0);
}

int	check_extension(char *s)
{
	int	i;

	i = ft_strlen(s);
	if (i < 4)
		return (1);
	if (s[i - 4] != '.'
		|| s[i - 3] != 'c'
		|| s[i - 2] != 'u'
		|| s[i - 1] != 'b')
		return (1);
	return (0);
}

int	data_init(t_data *data, t_map *map_data, char *path)
{
	int	fd;
	int	i;

	if (check_extension(path))
		return (1);
	i = 0;
	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (1);
	if (parsing(fd, map_data))
		return (close(fd), 1);
	close(fd);
	malloc_textures(data);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_map(map_data->map), free_tex_str(map_data), 1);
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	while (i < 6)
		data->keys[i++] = 0;
	if (set_var(data, map_data))
		return (clear_mlx(data, map_data), 1);
	return (0);
}
