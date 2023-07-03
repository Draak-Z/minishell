/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:40:28 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/18 14:37:55 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_key(char *line)
{
	char	*str;
	int		i;

	i = 0;
	if (line[i] == '?')
		i++;
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\''
		&& line[i] != '\"' && line[i] != '$' && (is_alpha(line[i])
			|| is_num(line[i]) || line[i] == '_'))
		i++;
	if (i == 0 && (line[i] != '\'' || line[i] != '\"'))
		return (ft_strdup(&line[i]));
	if (i == 0)
		return (NULL);
	str = ft_strndup(line, i);
	return (str);
}

char	*get_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

char	*left_part(char *line, int i, t_env *env, char *key)
{
	char	*str1;
	char	*str2;
	char	*var;

	if (!key)
		return (ft_strndup(line, i + 1));
	if (key[0] == '?')
		var = ft_itoa(g_shell->exit);
	else
		var = get_value(env, key);
	if (!var && !ft_strcmp(key, "_"))
		var = ft_strdup("_");
	free(key);
	if (!var)
		return (ft_strndup(line, i));
	str1 = ft_strndup(line, i);
	str2 = ft_strdup(var);
	str1 = ft_strjoin(str1, str2);
	free(str2);
	free(var);
	return (str1);
}

char	*right_part(char *line)
{
	int		i;

	i = 0;
	if (line[i] == '?')
	{
		i++;
		return (ft_strdup(line + i));
	}
	while (line[i] != '\0' && line[i] != ' ' && line[i] != '\''
		&& line[i] != '\"' && line[i] != '$' && (is_alpha(line[i])
			|| is_num(line[i]) || line[i] == '_'))
		i++;
	return (ft_strdup(line + i));
}

char	*dollar(char *line, t_env *env, int i, char symbol)
{
	char	*str1;
	char	*str2;

	while (line[i] != '\0')
	{	
		if (line[i] == '$' && symbol != '\'')
		{
			str1 = left_part(line, i, env, get_key(line + i + 1));
			str2 = right_part(line + i + 1);
			i = ft_strlen(str1);
			free(line);
			line = ft_strjoin(str1, str2);
			free(str2);
			continue ;
		}
		if ((line[i] == '\'' || line[i] == '\"') && symbol == 0
			&& is_even_quotes(line + i + 1, line[i]))
			symbol = line[i];
		else if (line[i] == symbol)
			symbol = 0;
		i++;
	}
	return (line);
}
