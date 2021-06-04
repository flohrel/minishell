###############
## Variables ##
###############

NAME		=	minishell

VPATH		=	src \
				src/builtins \
				src/exec \
				src/input \
				src/lexer \
				src/parser \
				src/utils
OBJDIR		=	obj
LIBDIR		=	libft
INCLDIR		=	incld

BUILTINS	=	cd.c \
				echo.c \
				env_utils.c \
				export.c \
				exit_b.c \
				find_builtin.c \
				ft_already.c \
				ft_endwith.c \
				ft_ischarset.c \
				ft_startwith.c \
				ft_tablen.c \
				ft_strisdigit.c \
				get_env_value.c \
				set_env_value.c \
				optionhandle.c \
				parse_env.c \
				print_env.c \
				pwd.c \
				unset.c

EXEC		=	exec.c \
			exec_utils.c \
			add_ptrlst.c \
			find_cmd.c

INPUT		=	input.c \
				prompt.c

LEXER		=	lexer.c \
				lexer2.c

PARSER		=	parser.c \
				parser2.c \
				parser3.c \
				parser4.c \
				parser5.c \

UTILS		=	astree.c \
				error.c \
				exit.c \
				list_to_tab.c \
				memory.c \
				print_tab.c \
				token.c

SRC			=	main.c \
				test.c \
				$(BUILTINS) \
				$(EXEC) \
				$(INPUT) \
				$(LEXER) \
				$(PARSER) \
				$(UTILS)

OBJ			=	$(SRC:%.c=$(OBJDIR)/%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3
INCFLAGS	=	-I./$(INCLDIR) -I./$(LIBDIR)/incld
LFLAGS		=	-L./$(LIBDIR) -lft -lncurses
RM			=	/bin/rm -rf
UNAME		:=	$(shell uname -s)


###########
## Rules ##
###########

.PHONY:			all bonus clean fclean re

all:			$(NAME)

$(OBJDIR)/%.o:	%.c | $(OBJDIR)
				$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				make -C $(LIBDIR)
				$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR):
				mkdir $(OBJDIR)

bonus:
				@make all

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME) $(OBJDIR)

re:				fclean all
