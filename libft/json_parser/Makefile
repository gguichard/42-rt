# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/15 15:22:16 by gguichar          #+#    #+#              #
#    Updated: 2019/04/17 14:38:16 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	json_parser.a

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

CC			=	gcc
CFLAGS 		=	-Wall -Werror -Wextra
CPPFLAGS	=	-MMD -I../includes -I$(INC_DIR)

SRC_DIR		=	src
SRC 		=		\
json_lexer.c		\
json_lexer_types.c	\
json_parser.c		\
json_parser_utils.c	\
json_parser_types.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	ar rcs $@ $^

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(OBJ_DIR):
	@/bin/mkdir $(OBJ_DIR) 2> /dev/null || true

clean:
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	/bin/rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
