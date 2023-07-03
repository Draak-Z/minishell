/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:35:03 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:26:10 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	redirections(t_redirs *lst_lines, char *s, int input, int output)
{
	if (lst_lines->target[0] == '\0')
		return (ft_putstr_fd_ret("minishell: syntax error\n", 2, 1));
	if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0)
		output = open_file(s, lst_lines->target);
	if (ft_strchr(s, '<'))
		input = open_file(s, lst_lines->target);
	if (input < 0 || output < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst_lines->target, 2);
		if (input == -1 || output == -1)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (input == -2 || output == -2)
			ft_putstr_fd(": No file or directory of this type\n", 2);
		return (1);
	}
	if (lst_lines->input != 0 && output == 0)
		close(lst_lines->input);
	if (input != 0 && output == 0)
		lst_lines->input = input;
	if (output != 0 && input == 0)
		lst_lines->output = output;
	free(lst_lines->target);
	return (0);
}

static char	*get_name(char *line, int i, t_redirs *elem)
{
	char	*name;
	char	*tmp;
	int		z;
	int		y;

	z = i;
	y = i;
	while (line[y] && (line[y] == '>' || line[y] == '<' || line[y] == ' '))
		y++;
	i = y;
	while (line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<')
		i++;
	tmp = ft_strndup(line + y, (i - y));
	name = ft_strtrim(tmp, " ");
	elem->target = dollar(ft_strdup(name), g_shell->env, 0, 0);
	free(name);
	free(tmp);
	tmp = ft_strdup(line + i);
	name = ft_strjoin(ft_strndup(line, z), tmp);
	free(line);
	free(tmp);
	return (name);
}

char	*dup_symbol(char *line, int i)
{
	char	*symbol;

	symbol = NULL;
	if (line[i] == '>' && line[i + 1] == '>')
		symbol = ft_strdup(">>");
	else if (line[i] == '<' && line[i + 1] == '<')
		symbol = ft_strdup("<<");
	else if (line[i] == '<')
		symbol = ft_strdup("<");
	else if (line[i] == '>')
		symbol = ft_strdup(">");
	return (symbol);
}

int	parse_redirections(char *line, t_redirs *elem, int i)
{
	while (i != -1)
	{
		free(elem->symbol);
		elem->symbol = dup_symbol(line, i);
		if (ft_strcmp(elem->symbol, "<<") == 0)
		{
			line = heredoc_case(elem, line, i);
			free(elem->line);
			elem->line = line;
		}
		if (ft_strcmp(elem->symbol, ">") == 0
			|| ft_strcmp(elem->symbol, ">>") == 0
			|| (ft_strcmp(elem->symbol, "<") == 0))
		{
			line = get_name(line, i, elem);
			elem->line = line;
			if (redirections(elem, elem->symbol, 0, 0))
			{
				free(line);
				return (1);
			}
		}
		i = find_symbol(line);
	}
	return (0);
}

t_redirs	*create_elem(char *data)
{
	t_redirs	*new;

	if (go_malloc((void *)&new, sizeof(t_redirs)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	new->line = data;
	new->word = NULL;
	new->symbol = NULL;
	new->target = NULL;
	new->input = 0;
	new->output = 0;
	new->i = -1;
	new->argv = NULL;
	new->executable = NULL;
	new->next = NULL;
	if (parse_redirections(new->line, new, find_symbol(new->line)))
	{
		free(new->target);
		free(new->symbol);
		free(new);
		return (NULL);
	}
	return (new);
}
