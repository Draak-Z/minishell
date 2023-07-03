/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:04:10 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 14:37:02 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	clear_lst_redirs(t_redirs **lst)
{
	t_redirs	*list;
	t_redirs	*tmp;

	list = *lst;
	while (list)
	{
		tmp = list;
		if (list->line)
			free(list->line);
		if (list->symbol)
			free(list->symbol);
		if (list->executable)
			free(list->executable);
		if (list->word)
			free(list->word);
		if (list->argv)
			free_array(list->argv, -1);
		list = list->next;
		free(tmp);
	}
	lst = NULL;
}

void	clear_lst_lines(t_lines **lst)
{
	t_lines	*list;
	t_lines	*tmp;

	list = *lst;
	while (list)
	{
		tmp = list;
		free(list->line);
		clear_lst_redirs(&list->redirs);
		list = list->next;
		free(tmp);
	}
	lst = NULL;
}

void	env_clear(t_env *env)
{
	t_env	*list;
	t_env	*next;

	list = env;
	while (list)
	{
		next = list->next;
		ft_clean_elem(&list);
		list = next;
	}
	env = NULL;
}

void	clear_cmd_lst(void)
{
	int	i;

	i = -1;
	while (++i < 8)
		free(g_shell->cmd->cmd_lst[i]);
	free(g_shell->cmd->cmd_lst);
}

void	ft_exit_error(int er, char *msg, bool tf)
{
	clear_lst_lines(&g_shell->lst);
	env_clear(g_shell->env);
	clear_cmd_lst();
	free(g_shell->usr);
	free(g_shell);
	rl_clear_history();
	if (tf)
		ft_putstr_fd(msg, 2);
	exit(er);
}
