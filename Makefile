#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 18:02:49 by ciglesia          #+#    #+#              #
#    Updated: 2020/11/19 17:59:20 by ciglesia         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		=	ft_ls

#****************** INC *******************#
# General
INC			=	./include/

# Libft
SUB_MAKE	=	./libft/
INCFT		=	./libft/include/

INCLUDE		=	-I $(INCFT) -I $(INC)

INC_LIB		=	-L$(SUB_MAKE) -lft

# lsailor
BONUS_MAKE	=	./lsailor/

#***************** SRC *******************#

DIRSRC		=	./src/
DIRLOAD		=	$(DIRSRC)/loading/
DIREXE		=	$(DIRSRC)/execution/
DIRVAL		=	$(DIRSRC)/validation/

SRC			=	ft_ls.c
VALIDATION	=	usage.c valid_input.c valid_dirfile.c
EXEC		=	exec.c manipulation.c sorting.c
LOADING		=	load_options.c

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

$(NAME)	:		ftlib $(OBJS)
				@$(CC)  $(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(INC_LIB)
				@$(ECHO) '> Compiled'

clean	:
				@($(RM) $(OBJS))
				@($(RM) $(DEPS))
				@(cd $(SUB_MAKE) && $(MAKE) clean)
				@(cd $(BONUS_MAKE) && $(MAKE) clean)
				@$(ECHO) '> Directory cleaned'

all		:		$(NAME)

fclean	:		clean
				@$(RM) $(NAME)
				@(cd $(SUB_MAKE) && $(MAKE) fclean)
				@(cd $(BONUS_MAKE) && $(MAKE) fclean)
				@$(ECHO) '> Remove executable'

re		:		fclean all

ftlib	:
				@(cd $(SUB_MAKE) && $(MAKE))

bonus	:		ftlib
				@(cd $(BONUS_MAKE) && $(MAKE))

.PHONY	:		all clean re

-include $(DEPS)
