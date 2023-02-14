NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror -I inc -g

ifeq ($(USER), lsabik)
	LDFLAGS="-L/Users/lsabik/.brew/opt/readline/lib"
	CPPFLAGS="-I/Users/lsabik/.brew/opt/readline/include"
else
	LDFLAGS="-L/usr/lib"
    CPPFLAGS="-I/usr/include"
endif
INCLUDESS        =  ${CPPFLAGS}
LIBRARIESS        = ${LDFLAGS} -lreadline

SRCS        :=      minishell.c \
                          src/libft/ft_atoi.c \
                          src/libft/ft_bzero.c \
                          src/libft/ft_calloc.c \
                          src/libft/ft_isalnum.c \
                          src/libft/ft_isalpha.c \
                          src/libft/ft_isascii.c \
                          src/libft/ft_isdigit.c \
                          src/libft/ft_isprint.c \
                          src/libft/ft_itoa.c \
                          src/libft/ft_lstadd_back.c \
                          src/libft/ft_lstadd_front.c \
                          src/libft/ft_lstclear.c \
                          src/libft/ft_lstdelone.c \
                          src/libft/ft_lstiter.c \
                          src/libft/ft_lstlast.c \
                          src/libft/ft_lstmap.c \
                          src/libft/ft_lstnew.c \
                          src/libft/ft_lstsize.c \
						              src/libft/ft_strcmp.c \
                          src/libft/ft_memchr.c \
                          src/libft/ft_memcmp.c \
                          src/libft/ft_memcpy.c \
                          src/libft/ft_memmove.c \
						              src/libft/ft_strndup.c \
                          src/libft/ft_memset.c \
                          src/libft/ft_putchar_fd.c \
                          src/libft/ft_putendl_fd.c \
                          src/libft/ft_putnbr_fd.c \
                          src/libft/ft_putstr_fd.c \
                          src/libft/ft_split.c \
                          src/libft/ft_strchr.c \
                          src/libft/ft_strdup.c \
                          src/libft/ft_striteri.c \
                          src/libft/ft_strjoin.c \
                          src/libft/ft_strlcat.c \
                          src/libft/ft_strlcpy.c \
                          src/libft/ft_strlen.c \
                          src/libft/ft_strmapi.c \
                          src/libft/ft_strncmp.c \
                          src/libft/ft_strnstr.c \
                          src/libft/ft_strrchr.c \
                          src/libft/ft_strtrim.c \
                          src/libft/ft_substr.c \
                          src/libft/ft_tolower.c \
                          src/libft/ft_toupper.c \
						              src/parsing/init.c \
						              src/builtin/cd.c \
                          src/builtin/echo.c \
						              src/utils/get_env.c \
                          src/utils/set_env.c \
                          src/builtin/export.c \
                          src/utils/is_option.c \
                          src/utils/add_env.c \
                          src/parsing/lexer.c \
                          src/utils/ft_token_add_back.c \
                          src/parsing/signals.c \
                          
OBJS        := $(SRCS:.c=.o)

.c.o:
	${CC} ${FLAGS} ${INCLUDESS} -c $< -o ${<:.c=.o}


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f

${NAME}:	${OBJS} inc/minishell.h
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			${CC} ${FLAGS} ${LIBRARIESS} -o ${NAME} ${OBJS} -lreadline
			@echo "$(GREEN)$(NAME) created[0m ✔️"

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:		clean
			@ ${RM} ${NAME}
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re
