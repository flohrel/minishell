###############
## Variables ##
###############

NAME		=	minishell

VPATH		=	src
OBJDIR		=	obj
LIBDIR		=	lib
INCLDIR		=	incld

SRC			=	cd.c pwd.c echo.c export.c unset.c \
				parse_env.c get_env_value.c print_env.c env_utils.c

OBJ			=	$(SRC:%.c=$(OBJDIR)/%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3
INCFLAGS	=	-I./$(INCLDIR) -I./$(LIBDIR)/libft/incld -I./include
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
