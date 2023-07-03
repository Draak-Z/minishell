/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:41:03 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:16:05 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_add_history(char *line)
{
	if (line && *line && !empty_line(line))
		add_history(line);
}

int	parse_functions(char *line, int ret)
{
	g_shell->lst = NULL;
	ret = too_many_pipes(line, -1, 1, 0);
	if (ret == 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token « | »\n", 2);
		g_shell->exit = ret;
		return (2);
	}
	ret = parse(line, &g_shell->lst, -1, 0);
	if (!ret && launch(g_shell->lst, g_shell->lst, NULL, 0))
		return (1);
	clear_lst_lines(&g_shell->lst);
	if (ret)
		return (2);
	return (0);
}

void	control_d(int er)
{
	env_clear(g_shell->env);
	clear_cmd_lst();
	free(g_shell->usr);
	free(g_shell);
	rl_clear_history();
	ft_putstr_fd("exit\n", 1);
	exit(er);
}

int	lsh_loop(char *line, char *prompt)
{
	while (true)
	{
		load_user(1);
		g_shell->ms = 0;
		g_shell->pid = -1;
		g_shell->hd = 0;
		g_shell->hd_c = 0;
		g_shell->hd_q = 0;
		prompt = make_prompt(g_shell->usr);
		line = readline(prompt);
		free(prompt);
		if (line)
		{
			if (!empty(line))
				if (parse_functions(line, 0) == 1)
					return (1);
			ft_add_history(line);
			free(line);
			continue ;
		}
		free(line);
		control_d(g_shell->exit);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd	cmd;

	(void)argv;
	if (go_malloc((void *)&g_shell, sizeof(t_shell)))
	{
		ft_putstr_fd("minishell: malloc failed\n", 2);
		return (1);
	}
	if (argc == 1)
	{
		signal_handling();
		load_env(NULL, env, -1, NULL);
		load_user(0);
		load_cmd(&cmd);
		g_shell->exit = 0;
		change_shlvl(g_shell->env, 0, NULL);
		if (lsh_loop(NULL, NULL))
			return (1);
	}
	else
		return (ft_putstr_fd_ret("Error : Too many arguments\n", 2, 1));
	return (0);
}
