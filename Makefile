# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikarjala <ikarjala@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/05 16:57:32 by ikarjala          #+#    #+#              #
#    Updated: 2022/04/07 17:40:19 by ikarjala         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fillit
BIN		= $(ROOT)$(NAME)

CFUNC	= \
main

ROOT		= ./
SRC_DIR		= $(ROOT)src/
OBJ_DIR		= $(ROOT)
SRC			= $(addprefix $(SRC_DIR),$(addsuffix .c,$(CFUNC)))
OBJ			= $(addprefix $(OBJ_DIR),$(addsuffix .o,$(CFUNC)))
INC_DIR		= $(SRC_DIR) $(LIB_DIR)/
LIB_DIR		= $(ROOT)libft
LIB			= ft
LIBS		= $(addprefix lib,$(addsuffix .a,$(LIB)))

CFLAGS		= -Wall -Wextra -Werror
DEBUG_FLAGS	= -Wimplicit -Wconversion -g -fsanitize=address
CC			= clang

##	BUILD ====
all: $(NAME)
$(NAME): lib
	@echo	$(BMSG_BIN)
	$(CC) -c $(CFLAGS) $(SRC) -I $(INC_DIR)
	$(CC) -o $(BIN) $(OBJ) -L$(LIB_DIR) -l $(LIB)
	@echo	$(BMSG_FIN)
lib:
ifeq (,$(wildcard $(addprefix $(LIB_DIR),$(LIB))))
	@echo '\_,-->' $(BMSG_LIB)
	make -C $(LIB_DIR)	re
endif
install: re clean

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(BIN) $(LIB)
	rm -f libft.so
lclean: clean
	make -C $(LIB_DIR)	fclean
re: fclean all

.PHONY: lib clean lclean fclean re install
BMSG_BIN	= '$(COL_HL)' '$(NAME) :: Starting build...' '$(COL_NUL)'
BMSG_LIB	= '$(COL_HL)' '$(LIBS) :: Compiling libraries...' '$(COL_NUL)'
BMSG_FIN	= '$(COL_CS)' '$(NAME) :: Build success!' '$(COL_NUL)'

COL_HL		= \e[0;33m
COL_CS		= \e[0;32m
COL_NUL		= \e[0;0m

##	UTILS ====
CMD_NORME	= norminette -R CheckForbiddenSourceHeader
norme:
	$(CMD_NORME) $(SRC_DIR)*.c $(LIB_DIR)/*.c $(addsuffix *.h,$(INC_DIR))
