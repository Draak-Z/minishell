/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:41:07 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 14:36:47 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	find_symbol(char *line)
{
	int		i;
	char	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (flag == 0)
				flag = line[i];
			else
				flag = 0;
		}
		else if ((line[i] == '>' || line[i] == '<') && flag == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_pipe_in_quote(char *line, int j, int k, int l)
{
	int	i;

	i = -1;
	while (++i < j)
	{
		if (line[i] == '\'')
			l++;
		if (line[i] == '\"')
			k++;
	}
	if (l % 2 == 0 && k % 2 == 0)
		return (0);
	while (line[j])
	{
		if (line[i] == '\'')
			l++;
		if (line[i] == '\"')
			k++;
		j++;
	}
	if (l % 2 == 0 && k % 2 == 0)
		return (0);
	return (1);
}

char	**split_pipes(char *line, int i, int j, int k)
{
	char	**pipes;

	pipes = NULL;
	while (line[++i])
		if (line[i] == '|' && is_pipe_in_quote(line, i, 0, 0) == 0)
			j++;
	if (go_malloc((void *)&pipes, sizeof(t_lines) * (j + 1)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == '|' && is_pipe_in_quote(line, i, 0, 0) == 0)
		{
			pipes[j++] = ft_strndup(line + k, i - k);
			k = ++i;
		}
	}
	pipes[j] = ft_strndup(line + k, i);
	pipes[++j] = NULL;
	return (pipes);
}

int	parse(char *line, t_lines **lstl, int i, int k)
{
	char	**pipes;

	while (line[++i])
		if (line[i] == '|' && !is_pipe_in_quote(line, i, 0, 0))
			k = 1;
	if (!k)
	{
		if (go_malloc((void *)&pipes, sizeof(t_lines) * 2))
			ft_exit_error(1, "minishell: malloc failed\n", true);
		pipes[0] = ft_strdup(line);
		pipes[1] = NULL;
	}
	else
		pipes = split_pipes(line, -1, 0, 0);
	k = -1;
	while (pipes[++k])
	{
		if (fill_stucture(lstl, pipes[k]))
		{
			free(pipes);
			return (1);
		}
	}
	free(pipes);
	return (0);
}
