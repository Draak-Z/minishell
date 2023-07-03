/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:27 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:17:39 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strdup(const char *str)
{
	char	*nstr;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != 0)
		i++;
	if (go_malloc((void *)&nstr, sizeof(char) * (i + 1)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	i = -1;
	while (str[++i])
		nstr[i] = str[i];
	nstr[i] = '\0';
	return (nstr);
}
