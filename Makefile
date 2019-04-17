# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/04/17 16:27:19 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rtv1

END			=	\x1b[0m
GREEN		=	\x1b[32m

INC_DIR		=	includes

SDL_LIB		=	SDL2-2.0.9
SDL_DIR		=	SDL2
SDL_TAR		=	$(SDL_LIB).tar.gz
SDL_BUILD	=	$(SDL_DIR)/lib/libSDL2.a

CC			=	gcc
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS		=	-Llibft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs)
LDLIBS		=	-lft

SRC_DIR		=	src
SRC 		=	\
main.c			\
lib.c			\
parser.c		\
parser_types.c	\
parser_utils.c	\
draw_view.c		\
error.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) $(LDFLAGS) $(LDLIBS) -o $@ $^
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SDL_BUILD) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS)  -MMD -o $@ -c $<

$(SDL_BUILD): | $(SDL_DIR)
	curl https://www.libsdl.org/release/$(SDL_TAR) --output $(SDL_TAR)
	tar -xf $(SDL_TAR)
	cd $(SDL_LIB) && ./configure --prefix=$(shell pwd)/$(SDL_DIR)
	$(MAKE) -C $(SDL_LIB)
	$(MAKE) -C $(SDL_LIB) install

$(SDL_DIR) $(OBJ_DIR):
	@/bin/mkdir $@ 2> /dev/null || true

clean:
	$(MAKE) -C libft clean
	/bin/rm -f $(SDL_TAR)
	/bin/rm -rf $(SDL_LIB)
	/bin/rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	/bin/rm -f $(NAME)
	/bin/rm -rf $(SDL_DIR)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
