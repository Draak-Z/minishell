/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:38 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/08 19:39:39 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strncmp(char *str1, char *str2, size_t n)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	while (i < n)
	{
		if (str1[i] == str2[i] && (str1[i] != '\0' || str2[i] != '\0'))
			i++;
		else
		{
			j += (unsigned char)str1[i] - (unsigned char)str2[i];
			if (j > 0)
				return (1);
			else if (j < 0)
				return (-1);
			else
				return (0);
		}
	}
	return (j);
}
