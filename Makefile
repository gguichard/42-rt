# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/05/08 13:30:22 by gguichar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rt

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
init_objects.c					\
lib.c							\
main.c							\
effects/bump_mapping.c			\
effects/cartoon_filter.c		\
effects/checkerboard.c			\
effects/effects.c				\
effects/fog.c					\
effects/gray_filter.c			\
effects/perlin_noise.c			\
effects/perlin_noise_filter.c	\
effects/perlin_permut_tab.c		\
effects/perturbations.c			\
effects/wavy_effect.c			\
effects/wood_filter.c			\
maths/bbox.c					\
maths/kd_tree.c					\
maths/limited_objects.c			\
maths/math_utils.c				\
maths/mesh_tree.c				\
maths/quaternion.c				\
maths/quaternion_2.c			\
maths/solver.c					\
maths/vec3d.c					\
maths/vec3d_2.c					\
misc/camera.c					\
misc/error.c					\
parser/parse_checker.c			\
parser/parse_color.c			\
parser/parse_limits.c			\
parser/parse_misc.c				\
parser/parse_objects.c			\
parser/parse_objects_utils.c	\
parser/parse_properties.c		\
parser/parse_rotation.c			\
parser/parse_vec3d.c			\
parser/parse_vertices.c			\
parser/scene_parser.c			\
parser/setup_camera.c			\
parser/wf_obj_parser.c			\
parser/wf_obj_parser_helper.c	\
raytracing/light_rays.c			\
raytracing/ray_utils.c			\
raytracing/raytracer.c			\
raytracing/trace_rays.c			\
shapes/bbox.c					\
shapes/cone.c					\
shapes/cylinder.c				\
shapes/ellipsoid.c				\
shapes/hyperboloid.c			\
shapes/plane.c					\
shapes/sphere.c					\
shapes/tanglecube.c				\
shapes/torus.c					\
shapes/triangle.c				\
shapes/trianglemesh.c			\
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
