/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sede <clement.desede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:11:34 by cde-sede          #+#    #+#             */
/*   Updated: 2023/07/14 18:02:22 by cde-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_str_len(char const *s, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	*fill_tab(char *tab, char const *s, char c, int *k)
{
	int	j;

	j = 0;
	while (s[(*k)] && s[(*k)] == c)
		(*k)++;
	while (s[(*k)] && s[(*k)] != c)
		tab[j++] = s[(*k)++];
	tab[j] = '\0';
	return (tab);
}

static char	**str_del(char **tab, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(tab[j]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	k = 0;
	while (i < ft_count_words(s, c))
	{
		tab[i] = malloc(ft_str_len(s + k, c) + 1);
		if (!tab[i])
			return (str_del(tab, i));
		tab[i] = fill_tab(tab[i], s, c, &k);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
