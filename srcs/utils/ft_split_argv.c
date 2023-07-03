/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:42:36 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:50:08 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_even_quotes(char *line, char c)
{
	int	i;

	i = -1;
	while (line[++i])
		if (line[i] == c)
			return (1);
	return (0);
}

int	line_size(char *line)
{
	int		i;
	char	symbol;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == ' ')
			break ;
		if ((line[i] == '\"' || line[i] == '\'')
			&& is_even_quotes(line + i + 1, line[i]))
		{
			symbol = line[i];
			while (line[++i + 1] != '\0')
				if (line[i] == symbol)
					break ;
		}
	}
	return (i);
}

int	arrays_size(char *line)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			i = i + line_size(line + i);
			n++;
		}
		else
			i++;
	}
	return (n);
}

char	**split_argv(char *line, int n)
{
	int		i;
	int		size;
	char	**pointers;
	char	*data;

	pointers = NULL;
	if (go_malloc((void *)&pointers, (sizeof(char *) * (n + 1))))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	i = 0;
	n = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
		{
			size = line_size(line + i);
			data = ft_strndup(line + i, size);
			i = i + size;
			pointers[n++] = data;
		}
		else
			i++;
	}
	pointers[n] = NULL;
	return (pointers);
}

char	**ft_split_argv(char *line)
{
	char	**argv;
	int		n;

	n = arrays_size(line);
	argv = split_argv(line, n);
	return (argv);
}
