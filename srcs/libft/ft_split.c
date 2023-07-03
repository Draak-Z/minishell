/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:13 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:17:33 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	ft_wdlen(const char *str, char c)
{
	int	size;

	size = 0;
	while (str[size] && str[size] != c)
		size++;
	return (size + 1);
}

static void	ft_free(char **tab, int i)
{
	while (--i >= 0)
		free(tab[i]);
	free(tab);
}

static char	**ft_does_atfw(char **ptr, int count, const char *str, char c)
{
	int	ptr_i;
	int	inner_i;
	int	i;
	int	len;

	ptr_i = -1;
	inner_i = 0;
	while (++ptr_i < count)
	{
		i = 0;
		while (str[inner_i] == c)
			inner_i++;
		len = ft_wdlen(&str[inner_i], c);
		if (go_malloc((void *)&ptr[ptr_i], (sizeof(char) * len)))
		{
			ft_free(ptr, ptr_i);
			ft_exit_error(1, "minishell: malloc failed\n", true);
		}
		while (i < len - 1)
			ptr[ptr_i][i++] = str[inner_i++];
		ptr[ptr_i][i] = 0;
	}
	ptr[ptr_i] = NULL;
	return (ptr);
}

char	**ft_split(const char *s, char c)
{
	char	**ptr;
	int		i;
	int		count;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		if (go_malloc((void *)&ptr, (sizeof(char *))))
			ft_exit_error(1, "minishell: malloc failed\n", true);
		ptr[0] = NULL;
		return (ptr);
	}
	i = 0;
	count = 1;
	if (s[0] == c)
		count--;
	while (s[++i])
		if (s[i] != c && s[i - 1] == c)
			count++;
	if (go_malloc((void *)&ptr, (sizeof(char *) * (count + 1))))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	return (ft_does_atfw(ptr, count, s, c));
}
