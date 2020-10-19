/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbroccol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 00:00:46 by gbroccol          #+#    #+#             */
/*   Updated: 2020/05/20 12:23:16 by anastasiya       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_words_count(char const *s, char c)
{
	int res;

	res = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == '\0')
			return (res);
		while (*s != c && *s != '\0')
			s++;
		res++;
	}
	return (res);
}

static int		ft_letters_count(char const *s, char c, int j)
{
	int res;

	res = 0;
	while (s[j] != c && s[j] != '\0')
	{
		res++;
		j++;
	}
	return (res);
}

static void		*free_mem(char **result, int string)
{
	while (string >= 0)
	{
		free(result[string]);
		string--;
	}
	free(result);
	return (NULL);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		words_count;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	words_count = ft_words_count(s, c);
	if ((result = (char **)malloc((words_count + 1) * sizeof(char *))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (s[j] == c && s[j] != '\0')
			j++;
		if ((result[i] = ft_substr(s, j, ft_letters_count(s, c, j))) == NULL)
			return (free_mem(result, (i - 1)));
		while (s[j] != c && s[j] != '\0')
			j++;
		i++;
	}
	result[i] = NULL;
	return (result);
}
