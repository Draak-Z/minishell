/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:39:09 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 20:36:11 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL || fd < 0)
		return ;
	while (s[i])
		write(fd, &s[i++], 1);
}

int	ft_putstr_fd_ret(char *s, int fd, int ret)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
	return (ret);
}
