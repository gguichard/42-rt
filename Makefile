# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/04/30 02:38:34 by roduquen         ###   ########.fr        #
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

CC			=	gcc -O2
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS		=	-Llibft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs)
LDLIBS		=	-lft

SRC_DIR		=	src
SRC 		=					\
draw.c							\
lib.c							\
main.c							\
effects/bump_mapping.c			\
effects/cartoon_filter.c		\
effects/checkerboard.c			\
effects/effects.c				\
effects/gray_filter.c			\
effects/perlin_noise.c			\
effects/perlin_noise_filter.c	\
effects/perlin_permut_tab.c		\
effects/perturbations.c			\
effects/sin_perturbation.c		\
effects/wood_filter.c			\
maths/maths_utils.c				\
maths/quaternion.c				\
maths/quaternion_2.c			\
maths/solver.c					\
maths/vec3d.c					\
maths/vec3d_2.c					\
misc/camera.c					\
misc/error.c					\
parser/parser.c					\
parser/parser_objects.c			\
parser/parser_objects_utils.c	\
parser/parser_types.c			\
parser/parser_utils.c			\
parser/wf_obj_parser.c			\
raytracing/light_rays.c			\
raytracing/ray_utils.c			\
raytracing/raytracer.c			\
raytracing/trace_rays.c			\
shapes/cone.c					\
shapes/cylinder.c				\
shapes/ellipsoid.c				\
shapes/holed_cube.c				\
shapes/hyperboloid.c			\
shapes/plane.c					\
shapes/sphere.c					\
shapes/torus.c					\
shapes/triangle.c				\
ui/convert_to_ppm.c				\
ui/key_camera_events.c			\
ui/key_filter_events.c			\
ui/lib_hooks.c					\
ui/shape_keys.c					\
ui/shape_transforms.c

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
	@/bin/mkdir $@/effects 2> /dev/null || true
	@/bin/mkdir $@/events 2> /dev/null || true
	@/bin/mkdir $@/maths 2> /dev/null || true
	@/bin/mkdir $@/misc 2> /dev/null || true
	@/bin/mkdir $@/parser 2> /dev/null || true
	@/bin/mkdir $@/raytracing 2> /dev/null || true
	@/bin/mkdir $@/shapes 2> /dev/null || true
	@/bin/mkdir $@/ui 2> /dev/null || true

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
