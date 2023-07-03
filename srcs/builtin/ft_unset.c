/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:38 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:56:46 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*search_for_var(char *data, t_env *env)
{
	t_env	*tmp;
	t_env	*next;
	t_env	*prev;

	prev = NULL;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(data, tmp->key) == 0)
		{
			next = tmp->next;
			ft_clean_elem(&tmp);
			if (!(prev))
				env = next;
			else
				prev->next = next;
			return (env);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (env);
}

int	error_msg_unset(char *data)
{
	ft_putstr_fd("minishell:  unset: « ", 2);
	ft_putstr_fd(data, 2);
	ft_putstr_fd(" » not a valid identifier\n", 2);
	return (1);
}

int	check_var(char *str, char *data)
{
	int	i;

	i = 0;
	if (!(str))
		return (0);
	if (!is_alpha(str[i]) && str[i] != '_')
		return (error_msg_unset(data));
	while (str[++i] != '\0')
	{
		if (!is_alpha(str[i]) && !is_num(str[i]) && str[i] != '_')
		{
			if (str[i + 1] == '\0' && str[i] == '+')
				return (2);
			return (error_msg_unset(data));
		}
	}
	return (0);
}

int	unset(char **argv)
{
	int	i;

	i = 1;
	if (!(argv[1]))
		return (0);
	while (argv[i])
	{
		if (check_var(argv[i], argv[i]) == -1)
			return (-1);
		g_shell->env = search_for_var(argv[i], g_shell->env);
		i++;
	}
	return (0);
}
