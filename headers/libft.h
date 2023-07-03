/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmaudet <bmaudet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 21:56:32 by bmaudet           #+#    #+#             */
/*   Updated: 2021/11/19 02:24:41 by bmaudet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	*ft_memmove(void *dest, const void *src, size_t size);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_putstr_fd_ret(char *s, int fd, int ret);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strcmpm(char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
int		ft_strncmp(char *str1, char *str2, size_t n);
char	*ft_strndup(char *str, int n);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strtrim(char *s1, char *set);
int		is_alpha(char c);
int		is_num(char c);
int		ft_is_alpha(char *s);
int		ft_is_num(char *s);

#endif
