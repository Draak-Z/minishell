/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oldpwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 00:34:55 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:56:46 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*create_old_pwd(char *value)
{
	t_env	*elem;

	if (go_malloc((void *)&elem, sizeof(t_env)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	elem->key = ft_strdup("OLDPWD");
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	change_old_pwd(char *oldpwd)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = oldpwd;
			return ;
		}
		if (!(env->next))
			env->next = create_old_pwd(oldpwd);
		env = env->next;
	}	
}
