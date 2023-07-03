/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:21 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 01:15:19 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	j += (unsigned char)s1[i] - (unsigned char)s2[i];
	return (j);
}

int	ft_strcmpm(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (i < 9)
		return (0);
	i--;
	if (str[i] == 'l' && str[i - 1] == 'l' && str[i - 2] == 'e'
		&& str[i - 3] == 'h' && str[i - 4] == 's' && str[i - 5] == 'i'
		&& str[i - 6] == 'n' && str[i - 7] == 'i' && str[i - 8] == 'm')
		return (1);
	return (0);
}
