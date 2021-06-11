# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flohrel <flohrel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/16 16:04:42 by flohrel           #+#    #+#              #
#    Updated: 2021/06/10 16:49:29 by flohrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###############
## Variables ##
###############

NAME		=	libft.a

VPATH		=	src/conv \
				src/ctype \
				src/dlist \
				src/io \
				src/list \
				src/memory \
				src/string \
				src/io/gnl
INCLDIR		=	incld
OBJDIR		=	obj

CONV		=	ft_atoi.c \
				ft_itoa.c \
				ft_ltoa.c \
				ft_lltoa.c \
				ft_ltoa_base.c \
				ft_lltoa_base.c \
				ft_ultoa_base.c \
				ft_uint_to_utf8.c

CTYPE		=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isupper.c \
				ft_islower.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_tolower.c \
				ft_toupper.c \
				is_charset.c

DLIST		=	ft_dlstadd_back.c \
				ft_dlstadd_front.c \
				ft_dlstclear.c \
				ft_dlstdelone.c \
				ft_dlstiter.c \
				ft_dlstlast.c \
				ft_dlstmap.c \
				ft_dlstnew.c \
				ft_dlstsize.c

IO			=	ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c

LIST		=	ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_lstsort.c

MEM			=	ft_calloc.c \
				garb_coll.c \
				free.c

STR			=	ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_bzero.c

GNL			=	get_next_line.c \
				gnl_utils.c

SRC			=	$(CONV) \
				$(CTYPE) \
				$(DLIST) \
				$(IO) \
				$(LIST) \
				$(MEM) \
				$(STR) \
				$(GNL)
OBJ			=	$(SRC:%.c=$(OBJDIR)/%.o)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
INCFLAGS	=	-I./$(INCLDIR)
RM			=	/bin/rm -rf
AR			=	ar
ARFLAGS		=	rcs


###########
## Rules ##
###########

.PHONY:			all clean debug fclean re

all:			$(NAME)

$(OBJDIR)/%.o:	%.c | $(OBJDIR)
				$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME):		$(OBJ)
				$(AR) $(ARFLAGS) $@ $^

$(OBJDIR):
				mkdir $(OBJDIR)

debug:			CFLAGS += -fsanitize=address -g3
debug:			re

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME) $(OBJDIR)

re:				fclean all
