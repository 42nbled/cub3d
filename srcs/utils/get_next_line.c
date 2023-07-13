/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 02:15:02 by nbled             #+#    #+#             */
/*   Updated: 2023/07/13 13:54:05 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	got_newline(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

static void	get_rest(char *full_str, char *rest)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (full_str[i] == '\n')
		i++;
	if (!rest)
		return ;
	while (full_str[i] && full_str[i] != '\0')
		rest[j++] = full_str[i++];
	if (full_str[i] == '\0')
		rest[j] = '\0';
}

static char	*get_line(char *full_str)
{
	char	*return_str;
	int		i;

	i = 0;
	while (full_str[i] && full_str[i] != '\n')
		i++;
	if (full_str[i] == '\n')
		i++;
	return_str = (char *)malloc(i + 1);
	if (!return_str)
		return (NULL);
	i = -1;
	while (full_str[++i] && full_str[i] != '\n')
		return_str[i] = full_str[i];
	if (full_str[i] == '\n')
		return_str[i++] = '\n';
	return_str[i] = '\0';
	return (return_str);
}

static char	*get_until_newline(int fd, char *rest)
{
	char	*str;
	char	*tmp;
	int		read_result;

	read_result = BUFFER_SIZE;
	str = ft_strdup(rest);
	tmp = (char *)malloc(BUFFER_SIZE + 1);
	if (!str || !tmp)
		return (i_want_to_break_free(str, tmp));
	while (read_result == BUFFER_SIZE && !got_newline(str))
	{
		read_result = read(fd, tmp, BUFFER_SIZE);
		if (read_result == -1)
			return (i_want_to_break_free(str, tmp));
		tmp[read_result] = '\0';
		str = ft_strjoin(str, tmp);
		if (!str)
			return (i_want_to_break_free(str, tmp));
	}
	free(tmp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*str;
	char		*full_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (NULL);
	full_str = get_until_newline(fd, rest);
	if (!full_str || full_str[0] == '\0')
	{
		free(full_str);
		return (NULL);
	}
	str = get_line(full_str);
	if (!str)
		return (i_want_to_break_free(str, full_str));
	get_rest(full_str, rest);
	free(full_str);
	if (str[0] == '\0')
	{
		free(str);
		return (NULL);
	}
	return (str);
}
