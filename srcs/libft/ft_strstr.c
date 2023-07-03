/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:46 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/08 19:39:47 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	j;

	j = 0;
	if (to_find[j] == '\0' || to_find == NULL)
		return (str);
	while (*str != '\0')
	{
		j = 0;
		while (str[j] == to_find[j])
		{
			if (to_find[j + 1] == '\0')
				return (str);
			j++;
		}
		str++;
	}
	return (0);
}
