/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:07:37 by nbled             #+#    #+#             */
/*   Updated: 2023/07/06 20:25:34 by nbled            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define KEY_ESC		65307
# define KEY_W			119
# define KEY_A			97
# define KEY_S			115
# define KEY_D			100
# define KEY_Q			113
# define KEY_E			101

# define SCREEN_HEIGHT	800
# define SCREEN_WIDTH	1000

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32;1m"
# define YELLOW  "\x1b[33;1m"
# define BLUE    "\x1b[34;1m"
# define MAGENTA "\x1b[35;1m"
# define CYAN    "\x1b[36;1m"
# define END    "\x1b[0m"

# include	"mlx.h"
# include <X11/X.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>

typedef struct s_vec {
	double	x;
	double	y;
}				t_vec;

enum e_keys
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STRAF_L,
	STRAF_R,
};

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		keys[6];
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	double	player_x;
	double	player_y;
	double	player_angle;
	t_vec	player_movement;
	double	ray_angle;
	double	num_ray;
	char	**map;
}				t_data;

void	pixel_put(t_data *data, int x, int y, int color);
int		print_square(t_data *data, int x_start, int x_end, int y_start, int y_end, int color);
void	print_map(t_data *data);
void	print_player(t_data *data);

char	**ft_split(char const *s, char c);

#endif
