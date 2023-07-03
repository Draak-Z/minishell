/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:01:30 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/16 20:00:18 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	**copy_env_exp(t_env *old, char *str, int i)
{
	char	**new;
	char	*value;

	if (go_malloc((void *)&new, sizeof(char *) * (i + 1)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	i = 0;
	while (old)
	{
		if (old->value)
		{
			str = ft_strjoin(ft_strdup(old->key), "=\"");
			value = ft_strdup(old->value);
			str = ft_strjoin(str, value);
			free(value);
			str = ft_strjoin(str, "\"\n");
			new[i++] = str;
		}
		else
			new[i++] = ft_strjoin(ft_strdup(old->key), "\n");
		old = old->next;
	}
	new[i] = NULL;
	return (new);
}

int	sort_env(int i, int j, char **new, char *tmp)
{
	while (new[++i])
	{
		j = i;
		while (new[++j])
		{
			if (ft_strcmp(new[i], new[j]) > 0)
			{
				tmp = new[i];
				new[i] = new[j];
				new[j] = tmp;
			}
		}
	}
	i = -1;
	while (new[++i])
	{
		if (new[i][0] != '_')
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(new[i], 1);
		}
	}
	free_array(new, -1);
	return (0);
}
