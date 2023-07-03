/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:37:26 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/17 14:42:50 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	change_pwd(char *oldpwd, int ret)
{
	t_env	*env;
	char	*path;

	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			if (!env->value)
				free(oldpwd);
			if (!env->value)
				oldpwd = NULL;
			free(env->value);
			path = getcwd(NULL, 0);
			env->value = path;
			break ;
		}
		env = env->next;
	}
	if (!env)
		free(oldpwd);
	if (!env)
		oldpwd = NULL;
	change_old_pwd(oldpwd);
	return (ret);
}

int	too_many_lines(t_env *env, char *path)
{
	if (!ft_strcmp(path, "-"))
	{
		while (env)
		{
			if (!ft_strcmp(env->key, "OLDPWD") && env->value)
			{
				chdir(env->value);
				ft_putstr_fd(env->value, 1);
				return (ft_putstr_fd_ret("\n", 1, 0));
			}
			env = env->next;
		}
		return (ft_putstr_fd_ret("minishell: cd: « OLDPWD » not set\n", 2, 1));
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		return (ft_putstr_fd_ret(": No such file or directory\n", 2, 1));
	}
	return (0);
}

int	ch_dir(char *value)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	chdir(value);
	return (change_pwd(pwd, 0));
}

int	cd(char **argv)
{
	t_env	*env;
	int		ret;
	char	*pwd;

	if (argv && argv[1] && argv[2])
		return (ft_putstr_fd_ret("minishell: cd: too many arguments\n", 2, 1));
	env = g_shell->env;
	if (!argv[1] || !ft_strcmp(argv[1], "--"))
	{
		while (env)
		{
			if (ft_strcmp(env->key, "HOME") == 0)
				return (ch_dir(env->value));
			env = env->next;
		}
		return (ft_putstr_fd_ret("minishell: cd: « HOME » not set\n", 2, 1));
	}
	pwd = getcwd(NULL, 0);
	ret = too_many_lines(g_shell->env, argv[1]);
	if (!ret)
		return (change_pwd(pwd, ret));
	free(pwd);
	return (ret);
}
