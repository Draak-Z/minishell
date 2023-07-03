/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 23:10:10 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 14:23:18 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	add_to_end(t_lines **begin_list, t_lines *elem)
{
	t_lines	*tmp;

	if (!(*begin_list))
	{
		*begin_list = elem;
		elem->prev = NULL;
	}
	else
	{
		tmp = *begin_list;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		elem->prev = tmp;
		tmp->next = elem;
	}
}

static void	add_to_end_redir(t_redirs **begin_list, t_redirs *elem)
{
	t_redirs	*tmp;

	if (!(*begin_list))
	{
		*begin_list = elem;
		elem->prev = NULL;
	}
	else
	{
		tmp = *begin_list;
		while (tmp->next)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		elem->prev = tmp;
		tmp->next = elem;
	}
}

static t_lines	*create_elem_pipes(char *data)
{
	t_lines	*new;

	if (go_malloc((void *)&new, sizeof(t_lines)))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	new->line = ft_strdup(data);
	new->input = 0;
	new->output = 0;
	new->next = NULL;
	new->prev = NULL;
	new->redirs = NULL;
	return (new);
}

int	fill_stucture(t_lines **lstl, char *line)
{
	t_lines		*elem;
	t_redirs	*elemr;

	elem = create_elem_pipes(line);
	elemr = create_elem(line);
	if (!elemr)
	{
		free(elem->line);
		free(elem);
		return (1);
	}
	add_to_end_redir(&elem->redirs, elemr);
	add_to_end(lstl, elem);
	return (0);
}
