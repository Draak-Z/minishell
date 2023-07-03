/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alphanum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 17:25:16 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 02:24:58 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_num(char c)
{
	if (c > '9' || c < '0')
		return (0);
	else
		return (1);
}

int	is_alpha(char c)
{
	if (c < 'A' || c > 'z' || (c > 'Z' && c < 'a'))
		return (0);
	else
		return (1);
}

int	ft_is_num(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!is_num(s[i]))
			return (0);
	return (1);
}

int	ft_is_alpha(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!is_alpha(s[i]))
			return (0);
	return (1);
}
