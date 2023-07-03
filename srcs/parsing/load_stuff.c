/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:40:52 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 19:23:56 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	load_user(bool tf)
{
	t_env	*env;

	env = g_shell->env;
	if (tf)
		free(g_shell->usr);
	g_shell->usr = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "USER") == 0)
		{
			g_shell->usr = ft_strdup(env->value);
			return ;
		}
		env = env->next;
	}
	g_shell->usr = ft_strdup("user");
}

void	load_cmd(t_cmd *cmd)
{
	if (go_malloc((void *)&cmd->cmd_lst, sizeof(char *) * 8))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	cmd->cmd_lst[0] = ft_strdup("exit");
	cmd->cmd_lst[1] = ft_strdup("export");
	cmd->cmd_lst[2] = ft_strdup("unset");
	cmd->cmd_lst[3] = ft_strdup("cd");
	cmd->cmd_lst[4] = ft_strdup("pwd");
	cmd->cmd_lst[5] = ft_strdup("env");
	cmd->cmd_lst[6] = ft_strdup("echo");
	cmd->cmd_lst[7] = NULL;
	cmd->ba[0] = &ft_exit;
	cmd->ba[1] = &ft_export;
	cmd->ba[2] = &unset;
	cmd->ba[3] = &cd;
	cmd->ba[4] = &pwd;
	cmd->ba[5] = &env;
	cmd->ba[6] = &echo;
	cmd->ba[7] = NULL;
	g_shell->cmd = cmd;
}

t_env	*create_shlvl(char *value)
{
	t_env	*elem;

	if (go_malloc((void *)&elem, sizeof(t_env)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	elem->key = ft_strdup("SHLVL");
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	change_shlvl(t_env	*env, int value, char *str)
{
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			value = ft_atoi(env->value);
			str = ft_itoa(value + 1);
			free(env->value);
			env->value = str;
			return ;
		}
		if (!(env->next))
		{
			env->next = create_shlvl(ft_strdup("1"));
			env = env->next;
		}
		env = env->next;
	}	
}

void	complete_env(t_env	*env, char *pwd, char *str)
{
	if (!env)
	{
		str = ft_strjoin(ft_strdup("PWD="), pwd);
		free(pwd);
		g_shell->env = put_to_the_end(g_shell->env, str);
		free(str);
	}
	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
			break ;
		env = env->next;
	}
	if (!env)
		change_old_pwd(NULL);
	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "_") == 0)
			break ;
		env = env->next;
	}
	if (!env)
		change_env_exec(ft_strdup("./minishell"));
}
