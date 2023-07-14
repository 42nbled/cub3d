/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbled <nbled@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 07:07:37 by nbled             #+#    #+#             */
/*   Updated: 2023/07/14 18:50:16 by nbled            ###   ########.fr       */
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
# define KEY_M			109
# define KEY_LEFT		65361
# define KEY_RIGHT		65363

# define SCREEN_HEIGHT	600
# define SCREEN_WIDTH	1000

# define BUFFER_SIZE 32

# define PLAYER_SPEED 0.02f
# define ROT_SPEED 0.4f

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

typedef struct s_texture {
	void	*texture;
	int		x;
	int		y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_parse_textures
{
	char			*nstr;
	char			*sstr;
	char			*estr;
	char			*wstr;
	char			*fstr;
	char			*cstr;

	unsigned int	floor;
	unsigned int	ceil;
}	t_parse_textures;

typedef struct s_map
{
	int					width;
	int					height;
	t_vec				start_pos;
	double				start_angle;
	char				**map;
	t_parse_textures	textures;
}	t_map;

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
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	double		player_x;
	double		player_y;
	double		player_angle;
	double		ray_angle;
	double		num_ray;
	char		**map;
	int			map_height;
	int			map_widht;
	int			keys[6];
	int			minimap;

	int			floor;
	int			ceil;
	t_texture	north_texture;
	t_texture	south_texture;
	t_texture	est_texture;
	t_texture	west_texture;
}				t_data;

int		handle_press(int keycode, t_data *data);
int		handle_release(int keycode, t_data *data);

int		ft_close(t_data *data);
void	clear_mlx(t_data *data, t_map *map_data);
void	free_tex_str(t_map *map_data);

int		data_init(t_data *data, t_map *map_data, char *path);

void	get_angle(t_data *data);
void	player_movement(t_data *data);
int		loop(t_data *data);

int		print_screen(t_data *data, t_vec *ray);

t_vec	raycasting(t_data *data);

void	vec_add(t_vec *a, t_vec b);
t_vec	get_dist_x(t_data *data, t_vec dir, int signe1, int signe2);
t_vec	get_dist_y(t_data *data, t_vec dir, int signe1, int signe2);

void	pixel_put(t_data *data, int x, int y, int color);
int		print_line(t_data *data, int y_start, int y_end, int color);
void	print_map(t_data *data);
void	print_player(t_data *data);

int		ft_count_words(const char *s, char c);
int		ft_str_len(char const *s, char c);
char	**ft_split(char const *s, char c);

char	*get_next_line(int fd);
char	*i_want_to_break_free(char *str1, char *str2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
int		is_number(char *str);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		parsing(int fd, t_map *data);
int		free_parse(t_map *data);
void	free_map(char **map);

char	**read_map(int fd);
void	struct_init(t_map *data);
int		parse(char **map, t_map *data);
int		condition_get_all(t_parse_textures *tex, char *s, int *fc);
int		get_textures(char **map, t_parse_textures *tex, int *e);
int		get_size_of_map(t_map *data, char **map, int i);
int		copy_map(t_map *data, char **src, int i);
int		check_validity(t_map *data);
int		get_color(char *s, int *e);
int		get_startpos(t_map *data);
char	*get_path(char *str, int *e);

void	norm_vec(t_vec *v);

void	print_texture_north(t_data *data, t_vec *ray, double len, double start);
void	print_texture_south(t_data *data, t_vec *ray, double len, double start);
void	print_texture_west(t_data *data, t_vec *ray, double len, double start);
void	print_texture_est(t_data *data, t_vec *ray, double len, double start);

#endif
