###############
## Variables ##
###############

NAME		=	minishell

VPATH		=	src src/lexer
OBJDIR		=	obj
LIBDIR		=	lib
INCLDIR		=	incld

SRC			=	main.c \
				lexer.c \
				token.c \
				exit.c \
				prompt.c
OBJ			=	$(SRC:%.c=$(OBJDIR)/%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3
INCFLAGS	=	-I./$(INCLDIR) -I./$(LIBDIR)/libft/incld
LFLAGS		=	-L./$(LIBDIR)/libft -lft
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
