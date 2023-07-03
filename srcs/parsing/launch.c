/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:40:45 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 18:57:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	create_pipe(t_lines *elem)
{
	int	fd[2];

	if (pipe(fd) < 0)
		ft_exit_error(1, "minishell: pipe failed\n", true);
	if (elem->redirs->output == 0)
		elem->redirs->output = fd[1];
	else
		close(fd[1]);
	if (elem->next->redirs->input == 0)
		elem->next->redirs->input = fd[0];
	else
		close(fd[0]);
	return (0);
}

int	launch(t_lines *lst_l, t_lines *lstl, t_redirs *red, int status)
{
	while (lst_l)
	{
		if (lst_l->next)
			if (create_pipe(lst_l) == -1)
				return (1);
		red = lst_l->redirs;
		prepare_exec(red);
		if (launch_exec(red, lst_l, 0, 0))
			break ;
		if (!lst_l->next)
			break ;
		lst_l = lst_l->next;
	}
	while (lstl)
	{
		waitpid(lstl->pid, &status, 0);
		if (WIFEXITED(status) && !lstl->next)
			if (!g_shell->hd_c && (lst_l->redirs->i
					|| (!lst_l->redirs->i && WEXITSTATUS(status))))
				g_shell->exit = WEXITSTATUS(status);
		lstl = lstl->next;
	}
	return (0);
}
