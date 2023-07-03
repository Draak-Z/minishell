/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:31 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 19:05:38 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	int		lens1;
	int		lens2;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	lens1 = ft_strlen((char *)s1);
	lens2 = ft_strlen((char *)s2);
	if (go_malloc((void *)&newstr, sizeof(char) * (lens1 + lens2 + 1)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	while (++i < lens1)
		newstr[i] = s1[i];
	while (i < lens1 + lens2)
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}
