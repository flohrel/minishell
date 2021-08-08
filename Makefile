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

BUILTINS	=	assign.c \
				cd.c \
				cd_next.c \
				echo.c \
				env_utils.c \
				export.c \
				export_next.c \
				exit_b.c \
				find_builtin.c \
				ft_already.c \
				ft_endwith.c \
				ft_ischarset.c \
				ft_startwith.c \
				ft_tablen.c \
				ft_strisdigit.c \
				get_env_value.c \
				init_exp.c \
				set_env_value.c \
				optionhandle.c \
				parse_env.c \
				print_env.c \
				print_sorted_env.c \
				pwd.c \
				unset.c

EXEC		=	exec.c \
				exec_utils.c \
				redirection.c \
				add_ptrlst.c \
				find_cmd.c \
				find_cmd_next.c \
				pipes.c

INPUT		=	input.c \
				input_utils.c

LEXER		=	lexer0.c \
				lexer1.c \
				lexer_utils.c

PARSER		=	parser.c \
				parser_utils.c \
				ast_build0.c \
				ast_build1.c \
				ast_build2.c \
				wildcard.c

UTILS		=	astree.c \
				exit.c \
				init.c \
				utils.c \
				flag.c \
				shell_lvl.c

SRC			=	main.c \
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
LFLAGS		=	-L./$(LIBDIR) -lft -lreadline
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
