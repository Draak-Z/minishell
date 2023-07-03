/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:41:37 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 18:29:46 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h" 

void	catch_quit(int signal)
{
	(void)signal;
	if (!g_shell->ms)
	{
		if (g_shell->pid == 0 && !g_shell->hd)
		{
			ft_putstr_fd("Quit (core dumped)\n", 1);
			g_shell->exit = 131;
		}
		else if (g_shell->pid == 0 && g_shell->hd)
		{
			ft_putstr_fd("\b\b  ", 2);
			return ;
		}
		else
			ft_putstr_fd("\b\b  \b\b", 2);
	}
}

void	catch_int(int signal)
{
	(void)signal;
	if (!g_shell->ms)
	{
		if (g_shell->pid == 0 && g_shell->hd)
			exit(130);
		else
		{
			ft_putstr_fd("\n", 2);
			rl_replace_line("", 0);
			if (g_shell->pid == -1)
				rl_on_new_line();
			rl_redisplay();
			g_shell->exit = 130;
		}
	}
}

void	signal_handling(void)
{
	if (signal(SIGINT, &catch_int) == SIG_ERR)
		exit(0);
	if (signal(SIGQUIT, &catch_quit) == SIG_ERR)
		exit(0);
}
