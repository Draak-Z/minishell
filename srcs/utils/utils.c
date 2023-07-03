/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:42:50 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/12 18:56:46 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	empty_line(char *str)
{
	int	i;

	i = -1;
	if (!(str))
		return (1);
	while (str[++i] != '\0')
		if (str[i] != ' ')
			return (0);
	return (1);
}

int	empty(char *str)
{
	int	i;

	i = -1;
	if (!(*str))
		return (1);
	while (str[++i] != '\0')
		if (str[i] != ' ')
			return (0);
	g_shell->exit = 0;
	return (1);
}

void	free_array(char **tab, int i)
{
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*make_prompt(char *str)
{
	char	*ret;
	char	*cwd;

	ret = NULL;
	ret = ft_strdup("\033[1;36m");
	ret = ft_strjoin(ret, str);
	ret = ft_strjoin(ret, "@minishell\033[0m:\x1b[31m");
	cwd = getcwd(NULL, 0);
	ret = ft_strjoin(ret, cwd);
	free(cwd);
	ret = ft_strjoin(ret, "\x1b[0m$ ");
	return (ret);
}

int	go_malloc(void **str, int taille)
{
	(*str) = malloc(taille);
	if (str)
		return (0);
	return (1);
}
