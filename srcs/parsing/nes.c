/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:34:07 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/17 20:53:09 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	open_file(char *symbol, char *file)
{
	int	fd;

	if (ft_strcmp(symbol, ">>") == 0)
		fd = open(file, O_APPEND | O_CREAT | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strcmp(symbol, ">") == 0)
		fd = open(file, O_TRUNC | O_CREAT | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
	{
		if (access(file, F_OK) == -1)
			return (-2);
		fd = open(file, O_RDONLY);
	}
	return (fd);
}

int	too_many_pipes(char *line, int i, int x, int y)
{
	while (line[++i])
		if (line[i] == '|')
			x++;
	i = -1;
	while (--x > 0)
	{
		while (line[++i] != '|')
			if (line[i] != ' ')
				y = 1;
		if (!y)
			return (2);
		y = 0;
		if (x == 1)
			while (line[++i])
				if (line[i] != ' ')
					y = 1;
		if (!y && x == 1)
			return (2);
	}
	return (0);
}

char	*trunk_line(char *line, int i, int j)
{
	char	*tmp;

	tmp = ft_strdup(line + i + j);
	free(line);
	return (tmp);
}

t_env	*create_underscore(char *value)
{
	t_env	*elem;

	if (go_malloc((void *)&elem, sizeof(t_env)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	elem->key = ft_strdup("_");
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

void	change_env_exec(char *str)
{
	t_env	*env;

	env = g_shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, "_") == 0)
		{
			free(env->value);
			env->value = str;
			return ;
		}
		if (!(env->next))
		{
			env->next = create_underscore(str);
			env = env->next;
		}
		env = env->next;
	}
}
