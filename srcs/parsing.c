/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 12:02:32 by nbled             #+#    #+#             */
/*   Updated: 2023/07/13 15:28:19 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"


char	**read_map(int fd)
{
	char	**map;
	char	*line;
	char	*s;

	s = NULL;
	line = "";
	while (line != NULL)
	{
		line = get_next_line(fd);
		s = ft_strjoin(s, line);
		free(line);
	}
	map = ft_split(s, '\n');
	free(s);
	return (map);
}

char	*get_path(char *str)
{
	char	*dst;
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	dst = malloc(strlen(str) - i + 1);
	while (str[i] && str[i] != '\n')
		dst[y++] = str[i++];
	dst[y] = '\0';
	return (dst);
}

unsigned int	get_color(char *s, int *e)
{
	unsigned int	c;
	char			**tmp;
	int				i;

	tmp = ft_split(s, ',');
	c = 0;
	i = -1;
	while (tmp[++i]);
	if (i != 3)
		return (*e = 1, c);
	c = (atoi(tmp[0]) << 16) + (atoi(tmp[1]) << 8) + (atoi(tmp[2]) << 0);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp);
	return (c);
}

void	struct_init(t_map *data)
{
	data->textures = (t_parse_textures){ 0 };
	data->map = NULL;
	data->width = -1;
	data->height = -1;
}

int	get_size_of_map(t_map *data, char **map, int i)
{
	int	start;
	int	max_width;

	max_width = -1;
	start = i;
	while (map[i] && map[++i])
	{
		if ((ft_strlen(map[i]) == 0)
				|| (ft_strlen(map[i]) == 1 && map[i][0] == '\n'))
			return (1);
		if (ft_strlen(map[i]) > max_width)
			max_width = ft_strlen(map[i]);
	}
	data->width = max_width;
	data->height = i - start;
	if (max_width == -1)
		return (1);
	return (0);
}

int	check_validity(t_map *data)
{
	for (int y=0;y<data->height;y++)
	{
		for (int x=0;x<data->width;x++)
		{
			if (!strchr(" 01NSEW", data->map[y][x]))
				return (2);
			if (data->map[y][x] == '0')
			{
				if (y == 0 || x == 0 ||
					y == data->height - 1 || x == data->width - 1)
				{
					printf("%d %d\n", x, y);
					return (3);
				}
				if (data->map[y-1][x] == ' ')
					return (4);
				if (data->map[y+1][x] == ' ')
					return (5);
				if (data->map[y][x-1] == ' ')
					return (6);
				if (data->map[y][x+1] == ' ')
					return (7);
			}
		}
	}
	return (0);
}

void	copy_map(t_map *data, char **src, int i)
{
	int	x;
	int	y;

	y = -1;
	data->map = malloc(sizeof(char **) * (data->height + 1));
	while (++y < data->height)
	{
		data->map[y] = malloc(sizeof(char *) * (data->width + 1));
		x = -1;
		while (++x < ft_strlen(src[y + i]))
			if (src[y + i][x] != '\n')
				data->map[y][x] = src[y + i][x];
			else
				data->map[y][x] = ' ';
		while (x < data->width)
			data->map[y][x++] = ' ';
		data->map[y][x] = '\0';
	}
	data->map[y] = NULL;
}

void	finalise_tex(t_parse_textures *tex, int *e)
{
	tex->floor = get_color(tex->fstr, e);
	tex->ceil = get_color(tex->cstr, e);
}

int	get_textures(char **map, t_parse_textures *tex, int *e)
{
	int	i;
	int	c;
	int	fc;

	i = 0;
	c = 0;
	fc = 0;
	while (map[i] && c != 6 && *e == 0)
	{
		c++;
		if (!tex->nstr && (strncmp(map[i], "NO ", 3) == 0 || strncmp(map[i], "NO\t", 3) == 0))
			tex->nstr = get_path(map[i]);
		else if (!tex->sstr && (strncmp(map[i], "SO ", 3) == 0 || strncmp(map[i], "SO\t", 3) == 0))
			tex->sstr = get_path(map[i]);
		else if (!tex->wstr && (strncmp(map[i], "WE ", 3) == 0 || strncmp(map[i], "WE\t", 3) == 0))
			tex->wstr = get_path(map[i]);
		else if (!tex->estr && (strncmp(map[i], "EA ", 3) == 0 || strncmp(map[i], "EA\t", 3) == 0))
			tex->estr = get_path(map[i]);
		else if (!(fc & 1) && (strncmp(map[i], "F ", 2) == 0 || strncmp(map[i], "F\t", 2) == 0))
		{
			tex->fstr = get_path(map[i]);
			fc |= 1;
		}
		else if (!(fc & 2) && (strncmp(map[i], "C ", 2) == 0 || strncmp(map[i], "C\t", 2) == 0))
		{
			tex->cstr = get_path(map[i]);
			fc |= 2;
		}
		else
			c--;
//		else if (!map[i][0])
//			c--;
//		else
//			*e = 1;
		i++;
	}
	if (c != 6)
		*e = 1;
	return (i);
}

void	free_map(char **map)
{
	int	x;

	x = -1;
	while (map[++x])
		free(map[x]);
	free(map);
}
int	free_parse(t_map *data)
{
	free_map(data->map);
	if (data->textures.nstr)
		free(data->textures.nstr);
	if (data->textures.sstr)
		free(data->textures.sstr);
	if (data->textures.estr)
		free(data->textures.estr);
	if (data->textures.wstr)
		free(data->textures.wstr);
	if (data->textures.fstr)
		free(data->textures.fstr);
	if (data->textures.cstr)
		free(data->textures.cstr);
# pragma message "DONT FORGET HERE"
	return (1);
}

int	rotate_start(char c)
{
	if (c == 'N')
		return (-90);
	if (c == 'S')
		return (90);
	if (c == 'E')
		return (0);
	if (c == 'W')
		return (180);
	return (0);
}

int	get_startpos(t_map *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (strchr("NSEW", data->map[y][x]))
			{
				data->start_pos.x = x + .5f;
				data->start_pos.y = y + .5f;
				data->start_angle = (double)rotate_start(data->map[y][x]) / 180 * M_PI;
				return (0);
			}
		}
	}
	return (1);
}

int	parse(char **map, t_map *data)
{
	int	error;
	int	i;

	error = 0;
	i = get_textures(map, &(data->textures), &error);
	if (error)
		return (error);
	while (map[i] && map[i][0] == '\n')
		i++;
	if (get_size_of_map(data, map, i))
		return (1);
	copy_map(data, map, i);
	error = check_validity(data);
	finalise_tex(&(data->textures), &error);
	error = get_startpos(data);
	if (error)
		return (free_parse(data));
	return (error);
}

int	parsing(int fd, t_map *data)
{
	char	**map;

	map = read_map(fd);
	struct_init(data);
	if (parse(map, data) == 1)
		return (free_map(map), 1);
	free_map(map);
	return (0);
}




//int	main(int argc, char **argv)
//{
//	int		fd;
//
//	if (argc != 2)
//	{
//		printf("Error ! Invalid arguments\n");
//		return (0);
//	}
//	if (is_file_empty(argv[1]) == 0)
//		return (0);
//	fd = open(argv[1], O_RDONLY);
//	if (fd > 0)
//	{
//		if (parsing(fd))
//			printf("Parsing error\n");
//	}
//	else
//		printf("Error ! File not found\n");
//	return (0);
//}
