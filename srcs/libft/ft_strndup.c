/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:42 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:48:29 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*str_new;
	int		i;

	i = ft_strlen(str);
	if (i > n)
		i = n;
	if (go_malloc((void *)&str_new, ((sizeof(char) * (i + 1)))))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	i = 0;
	while (str[i] && i < n)
	{
		str_new[i] = str[i];
		i++;
	}
	str_new[i] = '\0';
	return (str_new);
}
