NAME	=	minishell

HEADERS	=	headers

SRCS	=	srcs/builtin/cd.c srcs/builtin/export_display.c srcs/builtin/export.c srcs/builtin/ft_echo.c srcs/builtin/ft_env.c srcs/builtin/ft_exit.c srcs/builtin/ft_unset.c srcs/builtin/oldpwd.c srcs/builtin/pwd.c \
			srcs/libft/ft_atoi.c srcs/libft/ft_is_alphanum.c srcs/libft/ft_itoa.c srcs/libft/ft_memmove.c srcs/libft/ft_putchar_fd.c srcs/libft/ft_putstr_fd.c srcs/libft/ft_split.c srcs/libft/ft_strchr.c srcs/libft/ft_strcmp.c srcs/libft/ft_strdup.c srcs/libft/ft_strjoin.c srcs/libft/ft_strlen.c srcs/libft/ft_strncmp.c srcs/libft/ft_strndup.c srcs/libft/ft_strstr.c srcs/libft/ft_strtrim.c \
			srcs/parsing/dollar.c srcs/parsing/execute.c srcs/parsing/fill_structure.c srcs/parsing/heredoc.c srcs/parsing/launch.c srcs/parsing/load_env.c srcs/parsing/load_stuff.c srcs/parsing/minishell.c srcs/parsing/nes.c srcs/parsing/parse.c srcs/parsing/preparation.c srcs/parsing/quotes.c srcs/parsing/redirections.c srcs/parsing/signal.c \
			srcs/utils/free.c srcs/utils/ft_split_argv.c srcs/utils/utils.c

OBJS	=	${SRCS:.c=.o}

CC		=	gcc

FLAGS	=	-Wall -Werror -Wextra -g3 -fsanitize=address

RM		=	rm -f

.c.o:
			${CC} ${FLAGS} -I$(HEADERS) -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CC} $(FLAGS) -o ${NAME} ${OBJS} -lreadline

clean: 
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
