/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:40:55 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 19:23:27 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ft_name(char *s)
{
	char	**tmp;
	char	*name;
	int		i;

	tmp = ft_split(s, '=');
	if (!tmp)
		return (NULL);
	name = tmp[0];
	i = 0;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
	return (name);
}

void	ft_clean_elem(t_env	**env)
{
	if (!(env))
		return ;
	if ((*env)->key)
		free((*env)->key);
	if ((*env)->value)
		free((*env)->value);
	(*env)->key = NULL;
	(*env)->value = NULL;
	free(*env);
	*env = NULL;
}

t_env	*ft_create_elem(char *data)
{
	t_env	*elem;

	if (go_malloc((void *)&elem, sizeof(t_env)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	elem->key = ft_name(data);
	if (!(elem->key) || !(ft_strchr(data, '=')))
		elem->value = NULL;
	else
		elem->value = ft_strdup(ft_strchr(data, '=') + 1);
	elem->prev = NULL;
	elem->next = NULL;
	return (elem);
}

t_env	*put_to_the_end(t_env *list, char *data)
{
	t_env	*tmp;
	t_env	*start;

	if (!(list))
	{
		list = ft_create_elem(data);
		return (list);
	}
	else
	{
		tmp = ft_create_elem(data);
		start = list;
		while (list->next)
			list = list->next;
		tmp->prev = list;
		list->next = tmp;
		return (start);
	}
}

int	load_env(t_env	*env, char **envt, int i, char *pwd)
{
	char	*str;

	g_shell->env = NULL;
	while (envt[++i])
		g_shell->env = put_to_the_end(g_shell->env, envt[i]);
	if (!g_shell->env)
	{
		pwd = getcwd(NULL, 0);
		str = ft_strjoin(ft_strdup("PWD="), pwd);
		free(pwd);
		g_shell->env = put_to_the_end(g_shell->env, str);
		free(str);
	}
	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
			break ;
		env = env->next;
	}
	if (!env)
		complete_env(env, getcwd(NULL, 0), NULL);
	else
		complete_env(env, NULL, NULL);
	return (0);
}
