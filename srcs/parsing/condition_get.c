/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:17:12 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 17:46:19 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	condition_get_ns(t_parse_textures *tex, char *s)
{
	int	e;

	e = 0;
	if (strncmp(s, "NO ", 3) == 0 || strncmp(s, "NO\t", 3) == 0)
	{
		if (tex->nstr)
			return (1);
		tex->nstr = get_path(s, &e);
		return (e);
	}
	if (strncmp(s, "SO ", 3) == 0 || strncmp(s, "SO\t", 3) == 0)
	{
		if (tex->sstr)
			return (1);
		tex->sstr = get_path(s, &e);
		return (e);
	}
	return (2);
}

int	condition_get_ew(t_parse_textures *tex, char *s)
{
	int	e;

	e = 0;
	if (strncmp(s, "EA ", 3) == 0 || strncmp(s, "EA\t", 3) == 0)
	{
		if (tex->estr)
			return (1);
		tex->estr = get_path(s, &e);
		return (e);
	}
	if (strncmp(s, "WE ", 3) == 0 || strncmp(s, "WE\t", 3) == 0)
	{
		if (tex->wstr)
			return (1);
		tex->wstr = get_path(s, &e);
		return (e);
	}
	return (2);
}

int	condition_get_fc(t_parse_textures *tex, char *s, int *fc)
{
	int	e;

	e = 0;
	if (strncmp(s, "F ", 2) == 0 || strncmp(s, "F\t", 2) == 0)
	{
		if (*fc & 1)
			return (1);
		tex->fstr = get_path(s, &e);
		*fc |= 1;
		return (e);
	}
	if (strncmp(s, "C ", 2) == 0 || strncmp(s, "C\t", 2) == 0)
	{
		if (*fc & 2)
			return (1);
		tex->cstr = get_path(s, &e);
		*fc |= 2;
		return (e);
	}
	return (2);
}

int	condition_get_all(t_parse_textures *tex, char *s, int *fc)
{
	int	n;

	n = condition_get_ns(tex, s);
	if (n == 1)
		return (1);
	n = condition_get_ew(tex, s);
	if (n == 1)
		return (1);
	n = condition_get_fc(tex, s, fc);
	if (n == 1)
		return (1);
	return (0);
}
