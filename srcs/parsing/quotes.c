/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:41:25 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 03:17:42 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*delete_quotes(char *line, char *copy, int i, char symbol)
{
	int	j;

	j = 0;
	while (line[++i])
	{	
		if ((line[i] == '\'' || line[i] == '\"') && symbol == 0
			&& is_even_quotes(line + i + 1, line[i]))
			symbol = line[i];
		else if (line[i] == symbol)
			symbol = 0;
		else
			copy[j++] = line[i];
	}
	copy[j] = '\0';
	free(line);
	return (copy);
}

char	**quotes(char **argv)
{
	int		i;
	char	*str;

	i = -1;
	while (argv[++i])
	{
		if (go_malloc((void *)&str, ft_strlen(argv[i]) + 1))
			ft_exit_error(1, "minishell: malloc failed\n", true);
		argv[i] = delete_quotes(argv[i], str, -1, 0);
	}
	return (argv);
}
