# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/05/02 23:15:33 by ymekraou         ###   ########.fr        #
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

TTF_DIR		= 	SDL2_TTF
TTF_BUILD	=	./SDL_text/ttf_build/lib/
INC_TTF     =   SDL_text/ttf_build/include/SDL2/SDL_ttf.h

CC			=	gcc -O2
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR)
CFLAGS 		=	-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS		=	-lft -Llibft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs) -lSDL2_ttf 

SRC_DIR		=	src
SRC 		=					\
draw.c							\
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
parser/parse_checker.c			\
parser/parse_objects.c			\
parser/parse_objects_utils.c	\
parser/parse_properties.c		\
parser/parse_rotation.c			\
parser/parse_vertices.c			\
parser/parser_utils.c			\
parser/scene_parser.c			\
parser/setup_camera.c			\
raytracing/light_rays.c			\
raytracing/ray_utils.c			\
raytracing/raytracer.c			\
raytracing/trace_rays.c			\
shapes/cone.c					\
shapes/cylinder.c				\
shapes/ellipsoid.c				\
shapes/hyperboloid.c			\
shapes/plane.c					\
shapes/sphere.c					\
shapes/tanglecube.c				\
shapes/torus.c					\
shapes/triangle.c				\
ui/convert_to_ppm.c				\
ui/key_camera_events.c			\
ui/key_filter_events.c			\
ui/lib_hooks.c					\
ui/shape_keys.c					\
ui/shape_transforms.c			\
panel/draw_panel.c				\

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) $(LDFLAGS)  -L$(TTF_BUILD) -o $@ $^  -I ./$(INC_TTF)
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SDL_BUILD) $(OBJ_DIR) $(TTF_BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $< -I ./$(INC_TTF) 

$(SDL_BUILD): | $(SDL_DIR)
	curl https://www.libsdl.org/release/$(SDL_TAR) --output $(SDL_TAR)
	tar -xf $(SDL_TAR)
	cd $(SDL_LIB) && ./configure --prefix=$(shell pwd)/$(SDL_DIR)
	$(MAKE) -C $(SDL_LIB)
	$(MAKE) -C $(SDL_LIB) install

##$(TTF_BUILD):
##	cd $(TTF_DIR)
##	tar -xvzf freetype-2.8.tar.gz
##	mkdir freetype_build
##	cd freetype-2.8 && ./configure --prefix=$(shell pwd)/../freetype_build
##	make
##	make install
##	cd ..
##	export FT2_CONFIG="$(shell pwd)/freetype_build/bin/freetype_config"
##	export SDL2_CONFIG="$(shell pwd)/../SDL2/bin/sdl2_config"
##	unzip SDL2_ttf-2.0.15.zip
##	mkdir ttf_build
##	cd SDL2_ttf-2.0.15
##	./configure --prefix="$(shell pwd)/../ttf_build"
##	make
##	make install



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
	@/bin/mkdir $@/panel 2> /dev/null || true

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
