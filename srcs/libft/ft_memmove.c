/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:02 by bmaudet           #+#    #+#             */
/*   Updated: 2021/10/08 19:39:03 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	unsigned char	*psrc;
	size_t			i;
	unsigned char	*pdest;

	i = 0;
	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	if ((!dest && !src) || !size)
		return (dest);
	if (psrc < pdest)
		while (++i <= size)
			pdest[size - i] = psrc[size - i];
	else
		while (size-- > 0)
			*(pdest++) = *(psrc++);
	return (dest);
}
