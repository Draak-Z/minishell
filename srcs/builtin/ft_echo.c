/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:19 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 03:28:47 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	option(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) >= 2)
	{
		if (str[0] == '-' && str[1] == 'n')
		{
			while (str[++i])
				if (str[i] != 'n')
					return (0);
			return (1);
		}
	}
	return (0);
}

int	echo(char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (argv[i] && option(argv[i]))
	{
		flag = 1;
		i++;
	}
	if (!(argv[i]) && flag == 0)
		ft_putchar_fd('\n', 1);
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar_fd(' ', 1);
		else if (!(argv[i + 1]) && flag == 0)
			ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
