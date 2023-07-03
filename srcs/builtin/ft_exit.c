/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:34 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 02:35:24 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	exit_error_num(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_exit_error(2, NULL, false);
}

long long	ft_atoi_exit(const char *str, int i, int *er)
{
	int			neg;
	long long	sum;

	neg = 1;
	sum = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			neg = -1;
	while (str[i] && str[i] == '0')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*er = 1;
		i++;
	}
	return (sum * neg);
}

char	*check_arg(char *arg, int i, char *s)
{
	s = ft_strtrim(arg, " ");
	if (ft_is_num(s))
	{
		free(arg);
		return (s);
	}
	else
		free(s);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	i--;
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			if (g_shell->pid)
				ft_putstr_fd("exit\n", 2);
			exit_error_num(arg);
		}
	}
	if (g_shell->pid)
		ft_putstr_fd("exit\n", 2);
	return (arg);
}

int	ft_exit(char **argv)
{
	size_t		argc;
	long long	exitcode;
	int			er;

	argc = 0;
	er = 0;
	if (!argv[1])
	{
		if (g_shell->pid)
			ft_putstr_fd("exit\n", 1);
		ft_exit_error(0, NULL, false);
	}
	while (argv[argc])
		argc++;
	argv[1] = check_arg(argv[1], 0, NULL);
	if (argc > 2)
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	else
	{
		exitcode = ft_atoi_exit(argv[1], 0, &er);
		if (er)
			exit_error_num(argv[1]);
		ft_exit_error(exitcode % 256, NULL, false);
	}
	return (1);
}
