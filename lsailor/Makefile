#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 18:02:49 by ciglesia          #+#    #+#              #
#    Updated: 2020/11/19 13:05:53 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	../lsail

#****************** INC *******************#
# General
INC			=	./include/

# Libft
LIB			=	../libft/
INCFT		=	../libft/include/

INCLUDE		=	-I $(INCFT) -I $(INC)

INC_LIB		=	-L$(LIB) -lft


#***************** SRC *******************#

DIRSRC		=	./src/
DIRLOAD		=	$(DIRSRC)/loading/
DIREXE		=	$(DIRSRC)/execution/
DIRVAL		=	$(DIRSRC)/validation/

SRC			=	lsail.c
VALIDATION	=
EXEC		=
LOADING		=

SRCS		=	$(SRC) $(VALIDATION) $(EXEC) $(LOADING)

#***************** DEPS ******************#

DIROBJ		=	./depo/

OAUX		=	$(SRCS:%=$(DIROBJ)%)
DEPS		=	$(OAUX:.c=.d)
OBJS		=	$(OAUX:.c=.o)

ifdef FLAGS
	ifeq ($(FLAGS), no)
CFLAGS		=
	endif
	ifeq ($(FLAGS), debug)
CFLAGS		=	-Wall -Wextra -Werror -ansi -pedantic -g
	endif
else
CFLAGS		=	-Wall -Wextra -Werror
endif

CC			=	/usr/bin/gcc
RM			=	/bin/rm -f
ECHO		=	/bin/echo -e

#************************ DEPS COMPILATION *************************

%.o		:		../$(DIRSRC)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIREXE)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRVAL)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

%.o		:		../$(DIRLOAD)/%.c
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -o $@ -c $<

#************************ MAIN COMPILATION *************************

$(NAME)	:		$(OBJS)
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) '> Compiled'

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@$(ECHO) '> Directory cleaned'

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@$(ECHO) '> Remove executable'

re		:		fclean all

.PHONY	:		all clean re

-include $(DEPS)
