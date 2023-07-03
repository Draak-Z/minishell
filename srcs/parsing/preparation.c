/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:41:16 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:32:35 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	check_commande(t_cmd *cmd, char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (-3);
	while (cmd->cmd_lst[i] != NULL)
	{
		if (ft_strcmp(cmd->cmd_lst[i], line) == 0)
			return (i);
		i++;
	}
	return (-2);
}

char	*add_path(char *cmd, char **paths, char *line)
{
	int	i;

	i = -1;
	while (paths[++i] != NULL)
	{
		line = ft_strjoin(paths[i], "/");
		line = ft_strjoin(line, cmd);
		if (open(line, O_RDONLY) != -1)
		{
			free_array(paths, i);
			return (line);
		}
		free(line);
	}
	free(paths);
	return (ft_strdup(cmd));
}

char	*find_path(char *cmd)
{
	t_env	*env;
	char	*str;
	char	**paths;

	env = g_shell->env;
	str = NULL;
	if (cmd == NULL)
		return (0);
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
			str = env->value;
		env = env->next;
	}
	if (str)
		paths = ft_split(str, ':');
	else
	{
		g_shell->path = 1;
		return (ft_strdup(cmd));
	}
	return (add_path(cmd, paths, NULL));
}

void	prepare_exec(t_redirs *lstl)
{
	g_shell->path = 0;
	lstl->line = dollar(lstl->line, g_shell->env, 0, 0);
	lstl->argv = ft_split_argv(lstl->line);
	lstl->argv = quotes(lstl->argv);
	lstl->cmd = lstl->argv[0];
	lstl->i = check_commande(g_shell->cmd, lstl->cmd);
	if (lstl->i >= 0)
		lstl->executable = ft_strdup(lstl->cmd);
	else if (access(lstl->argv[0], X_OK) == -1)
		lstl->executable = find_path(lstl->cmd);
	else
		lstl->executable = ft_strdup(lstl->argv[0]);
}
