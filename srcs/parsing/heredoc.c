/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:24:37 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 19:26:30 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*delete_quotes_hd(char *line, char *copy, int i, char symbol)
{
	int	j;

	j = 0;
	if (go_malloc((void *)&copy, ft_strlen(line) + 1))
		ft_exit_error(1, "minishell: malloc failed\n", true);
	while (line[++i])
	{	
		if (line[i] == '\'' || line[i] == '\"')
			g_shell->hd_q = 1;
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

char	*heredoc_case(t_redirs *elem, char *line, int i)
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
	while ((line[i] && line[i] != ' ' && line[i] != '>' && line[i] != '<'))
		i++;
	tmp = ft_strndup(line + y, (i - y));
	name = ft_strtrim(tmp, " ");
	elem->word = ft_strdup(name);
	elem->word = delete_quotes_hd(elem->word, NULL, -1, 0);
	free(tmp);
	free(name);
	tmp = ft_strdup(line + i);
	name = ft_strjoin(ft_strndup(line, z), tmp);
	free(tmp);
	return (name);
}

int	end_heredoc(int pid, t_redirs *list, int *heredoc_pipe)
{
	int	ret;

	g_shell->hd = false;
	waitpid(pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	list->input = heredoc_pipe[0];
	close(heredoc_pipe[1]);
	if (ret == 130)
		return (130);
	return (0);
}

void	loop_heredoc(char *line, t_redirs *list, int *heredoc_pipe)
{
	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: warning: « here-document »", 2);
			ft_putstr_fd(" ended by end of file (instead of « ", 2);
			ft_putstr_fd(list->word, 2);
			ft_putstr_fd(" »)\n", 2);
			break ;
		}
		if (!ft_strcmp(line, list->word))
		{
			free(line);
			break ;
		}
		if (!g_shell->hd_q)
			line = dollar(line, g_shell->env, 0, 0);
		ft_putstr_fd(line, heredoc_pipe[1]);
		ft_putstr_fd("\n", heredoc_pipe[1]);
		free(line);
	}
}

int	heredoc(t_redirs *list)
{
	int		pid;
	int		heredoc_pipe[2];

	if (pipe(heredoc_pipe) < 0)
		ft_exit_error(1, "minishell: pipe failed\n", true);
	g_shell->hd = true;
	pid = fork();
	if (pid < 0)
		ft_exit_error(1, "minishell: fork failed\n", true);
	g_shell->pid = pid;
	if (pid == 0)
	{
		close(heredoc_pipe[0]);
		loop_heredoc(NULL, list, heredoc_pipe);
		close(heredoc_pipe[1]);
		exit(0);
	}
	return (end_heredoc(pid, list, heredoc_pipe));
}
