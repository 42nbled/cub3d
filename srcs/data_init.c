/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:57:35 by nbled             #+#    #+#             */
/*   Updated: 2023/07/13 15:23:33 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_textures(t_data *data, t_map *map_data)
{
	data->north_texture = malloc(sizeof(t_texture));
	data->north_texture->texture = mlx_xpm_file_to_image(data->mlx, map_data->textures.nstr, &data->north_texture->x, &data->north_texture->y);
	data->south_texture = malloc(sizeof(t_texture));
	data->south_texture->texture = mlx_xpm_file_to_image(data->mlx, map_data->textures.sstr, &data->south_texture->x, &data->south_texture->y);
	data->est_texture = malloc(sizeof(t_texture));
	data->est_texture->texture = mlx_xpm_file_to_image(data->mlx, map_data->textures.estr, &data->est_texture->x, &data->est_texture->y);
	data->west_texture = malloc(sizeof(t_texture));
	data->west_texture->texture = mlx_xpm_file_to_image(data->mlx, map_data->textures.wstr, &data->west_texture->x, &data->west_texture->y);
}

int	data_init(t_data *data, t_map *map_data, char *path)
{
	int	fd;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	for (int i = 0; i < 6; i++)
		data->keys[i] = 0;
	data->mouse = 0;
	data->minimap = 0;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
		return (1);
	if (parsing(fd, map_data))
		return (close(fd), 1);
	close(fd);
	data->map_widht = map_data->width;
	data->map_height = map_data->height;
	data->map = (char **)map_data->map;
	init_textures(data, map_data);
	data->player_x = map_data->start_pos.x;
	data->player_y = map_data->start_pos.y;
	data->player_angle = map_data->start_angle;
	data->player_angle += 0.01f;
	return (0);
}
//			//data->map = ft_split("11111111n10100001n10100001n10100001n10000001n10000101n10000001n11111111n", 'n');
//			//data->map = ft_split("11111111n11000001n10000111n10001101n10001001n10000101n10000001n11111111n", 'n');
//			//data->map = ft_split("00000000n01111110n01010010n01000010n01001010n01000010n01111110n00000000n", 'n');
//			//data->map = ft_split("11111111n10001001n10111011n10101011n10000001n10101111n10100001n11111111n", 'n');
//			//data->map = ft_split("11111111n10110001n10110111n10000111n11100001n11101101n10001101n11111111n", 'n');
//		
//			data->map = ft_split("11111111111111111111111111n10001111111111111111111101n10101000000000000000000101n10001000000000000000000101n11101000000000000000000101n10000011111111111111101101n11101111111011111111100001n10000000000000000000000001n11111111111111111111111111n", 'n');
//			data->map_height = ft_count_words("11111111111111111111111111n10001111111111111111111101n10101000000000000000000101n10001000000000000000000101n11101000000000000000000101n10000011111111111111101101n11101111111011111111100001n10000000000000000000000001n11111111111111111111111111n", 'n');
//			data->map_widht = ft_str_len("11111111111111111111111111n10001111111111111111111101n10101000000000000000000101n10001000000000000000000101n11101000000000000000000101n10000011111111111111101101n11101111111011111111100001n10000000000000000000000001n11111111111111111111111111n", 'n');
//			for (int i = 0; i < 6; i++)
//				data->keys[i] = 0;
//			data->mouse = 0;
//			data->minimap = 0;
//			data->player_x = 5.5;
//			data->player_y = 3.5;
//			data->player_angle = 0.01f;
//			data->north_texture = malloc(sizeof(t_texture));
//			data->north_texture->texture = mlx_xpm_file_to_image(data->mlx, "textures/cracked_smouth_stone.xpm", &data->north_texture->x, &data->north_texture->y);
//			data->south_texture = malloc(sizeof(t_texture));
//			data->south_texture->texture = mlx_xpm_file_to_image(data->mlx, "textures/smouth_stone.xpm", &data->south_texture->x, &data->south_texture->y);
//			data->est_texture = malloc(sizeof(t_texture));
//			data->est_texture->texture = mlx_xpm_file_to_image(data->mlx, "textures/moussi_smouth_stone.xpm", &data->est_texture->x, &data->est_texture->y);
//			data->west_texture = malloc(sizeof(t_texture));
//			data->west_texture->texture = mlx_xpm_file_to_image(data->mlx, "textures/ground_player_facing_down.xpm", &data->west_texture->x, &data->west_texture->y);
//		
//		}
