/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:40:32 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:17:24 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	close_used_fd(t_redirs *lst_lines, int ret)
{
	if (lst_lines->input != 0)
	{
		close(lst_lines->input);
		lst_lines->input = 0;
	}
	if (lst_lines->output != 0)
	{
		close(lst_lines->output);
		lst_lines->output = 0;
	}
	return (ret);
}

void	exec_fail_msg(char *str, char *msg)
{
	g_shell->exit = 127;
	if (!ft_strcmp(msg, ": is a directory"))
		g_shell->exit = 126;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

void	execute(t_redirs *lst, char **env, int a)
{
	g_shell->ms = 0;
	if (lst->input != 0)
		dup2(lst->input, 0);
	if (lst->output != 0)
		dup2(lst->output, 1);
	if (lst->i >= 0 && lst->i <= 6)
		g_shell->exit = g_shell->cmd->ba[lst->i](lst->argv);
	else
	{
		if (lst->executable[0] == 47 || g_shell->path)
			a = access(lst->executable, R_OK);
		g_shell->exit = execve(lst->executable, lst->argv, env);
		if (a == -2 && g_shell->exit == -1)
			exec_fail_msg(lst->argv[0], ": command not found");
		else if (a == -1 && g_shell->exit == -1)
			exec_fail_msg(lst->argv[0], ": No file or directory of this type");
		else if (a > -1 && g_shell->exit == -1)
			exec_fail_msg(lst->argv[0], ": is a directory");
		free_array(lst->argv, -1);
	}
	exit(g_shell->exit);
}

int	pipe_functions(t_redirs *lst, t_lines *lstl, char **env)
{
	pid_t	pid;

	if (lst->executable)
	{
		pid = fork();
		if (pid < 0)
			ft_exit_error(1, "minishell: fork failed\n", true);
		g_shell->pid = pid;
		if (pid && ft_strcmpm(lst->executable))
			g_shell->ms = 1;
		if (pid == 0)
			execute(lst, env, -2);
		else
			lstl->pid = pid;
		g_shell->pid = 0;
	}
	free_array(env, -1);
	return (close_used_fd(lst, 0));
}

int	launch_exec(t_redirs *lines, t_lines *lstl, int i, int ret)
{
	while (lines->argv[i])
		i++;
	if (i == 0)
		i++;
	change_env_exec(ft_strdup(lines->argv[--i]));
	if (lines->word != NULL)
	{
		ret = heredoc(lines);
		g_shell->exit = ret;
	}
	if (ret == 130)
	{
		g_shell->hd_c = 1;
		return (1);
	}
	if (lines->i >= 0 && lines->i <= 3 && !g_shell->lst->next)
	{
		ret = g_shell->cmd->ba[lines->i](lines->argv);
		if (!lstl->next)
			g_shell->exit = ret;
		return (close_used_fd(lines, 0));
	}
	return (pipe_functions(lines, lstl, copy_env(g_shell->env, NULL)));
}
