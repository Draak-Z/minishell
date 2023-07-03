/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:57 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:04:43 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_itoa(int n)
{
	char	buff[12];
	int		i;
	int		sign;
	int		tmp;

	buff[11] = 0;
	i = 10;
	sign = 0;
	if (n < 0)
		sign = 1;
	if (!n)
		buff[i--] = '0';
	while (n)
	{
		tmp = n % 10;
		if (tmp < 0)
			tmp = -tmp;
		buff[i--] = tmp + '0';
		n /= 10;
	}
	if (sign)
		buff[i--] = '-';
	return (ft_strdup(buff + i + 1));
}
