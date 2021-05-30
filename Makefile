###############
## Variables ##
###############

NAME		=	minishell

VPATH		=	src src/lexer src/parser src/input src/utils
OBJDIR		=	obj
LIBDIR		=	lib
INCLDIR		=	incld

SRC			=	main.c \
				lexer.c \
				lexer2.c \
				token.c \
				exit.c \
				error.c \
				memory.c \
				prompt.c \
				input.c \
				parser.c \
				parser2.c \
				parser3.c \
				parser4.c \
				parser5.c \
				astree.c \
				test.c
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
