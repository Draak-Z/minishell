/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:41 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 17:56:16 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	pwd(char **argv)
{
	char	*pwd;

	(void)argv;
	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}
