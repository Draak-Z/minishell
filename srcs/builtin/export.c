/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:13 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 02:02:29 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	error_msg_export(char *data)
{
	ft_putstr_fd("minishell:  export: « ", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd(" » not a valid identifier\n", 2);
	return (1);
}

int	check_variable(char *str, char *data)
{
	int	i;

	i = 0;
	if (!(str))
		return (0);
	if ((!is_alpha(str[i]) && str[i] != '_') || data[0] == '=')
		return (error_msg_export(data));
	while (str[++i] != '\0')
	{
		if (!is_alpha(str[i]) && !is_num(str[i]) && str[i] != '_')
		{
			if (str[i + 1] == '\0' && str[i] == '+')
				return (2);
			return (error_msg_export(data));
		}
	}
	return (0);
}

int	find_variable_and_replace(t_env *tmp, t_env *new, int type, char *str)
{
	if (type == 2)
	{
		str = new->key;
		new->key = ft_strndup(str, ft_strlen(str) - 1);
		free(str);
	}
	while (tmp)
	{
		if (ft_strcmp(tmp->key, new->key) == 0)
		{
			if (type == 2)
				tmp->value = ft_strjoin(tmp->value, new->value);
			if (type == 2)
				free(new->value);
			if (type == 0)
				free(tmp->value);
			if (type == 0)
				tmp->value = new->value;
			free(new->key);
			free(new);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_variable(char *data)
{
	t_env	*new;
	t_env	*env;
	int		type;

	new = ft_create_elem(data);
	type = check_variable(new->key, data);
	if (type == 1)
	{
		ft_clean_elem(&new);
		return (1);
	}
	env = g_shell->env;
	if (find_variable_and_replace(env, new, type, NULL) == 1)
		return (0);
	while (env->next)
		env = env->next;
	env->next = new;
	return (0);
}

int	ft_export(char **argv)
{
	t_env	*env;
	int		i;

	i = 0;
	env = g_shell->env;
	while (env && ++i)
		env = env->next;
	if (!(argv[1]))
		return (sort_env(-1, 0, copy_env_exp(g_shell->env, NULL, i), NULL));
	i = 0;
	while (argv[++i])
		if (add_variable(argv[i]) == 1)
			return (1);
	return (0);
}
