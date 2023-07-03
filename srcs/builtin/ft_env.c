/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:38:29 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 19:19:39 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**copy_env(t_env *src, char *str)
{
	t_env	*old;
	char	**new;
	char	*value;
	int		i;

	i = 0;
	old = src;
	while (old && ++i)
		old = old->next;
	if (go_malloc((void *)&new, sizeof(char *) * (i + 1)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	old = src;
	i = 0;
	while (old)
	{
		str = ft_strjoin(ft_strdup(old->key), "=");
		value = ft_strdup(old->value);
		str = ft_strjoin(str, value);
		free(value);
		new[i++] = str;
		old = old->next;
	}
	new[i] = NULL;
	return (new);
}

void	display_var(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, 1);
			ft_putchar_fd('=', 1);
			ft_putstr_fd(env->value, 1);
			ft_putchar_fd('\n', 1);
		}
		env = env->next;
	}
}

int	env(char **argv)
{
	if (argv[1])
	{
		ft_putstr_fd("env: «", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("»: Aucun fichier ou dossier de ce type\n", 2);
		return (127);
	}
	display_var(g_shell->env);
	return (0);
}
