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
LIBDIR		=	lib
INCLDIR		=	incld

BUILTINS	=	cd.c \
				echo.c \
				env_utils.c \
				export.c \
				find_builtin.c \
				ft_already.c \
				ft_endwith.c \
				ft_ischarset.c \
				ft_startwith.c \
				ft_tablen.c \
				get_env_value.c \
				optionhandle.c \
				parse_env.c \
				print_env.c \
				pwd.c \
				exec_cmd.c \
				unset.c

EXEC		=	

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
INCFLAGS	=	-I./$(INCLDIR) -I./$(LIBDIR)/libft/incld
LFLAGS		=	-L./$(LIBDIR)/libft -lft -lncurses
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
				make -C $(LIBDIR)/libft
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
