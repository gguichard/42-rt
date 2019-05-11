# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gguichar <gguichar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/16 22:54:05 by gguichar          #+#    #+#              #
#    Updated: 2019/05/11 12:52:42 by roduquen         ###   ########.fr        #
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

TTF_DIR		=	SDL_text
TTF_BUILD	=	SDL_text/ttf_build/lib
INC_TTF     =   SDL_text/ttf_build/include/SDL2

CC			=	gcc -O2
CPPFLAGS	=	-Ilibft/includes -I$(INC_DIR) -I$(INC_TTF)
CFLAGS 		=	-Wall -Werror -Wextra $(shell ./SDL2/bin/sdl2-config --cflags)
LDFLAGS		=	-Llibft -L$(TTF_BUILD) -lft $(shell ./$(SDL_DIR)/bin/sdl2-config --libs) -lSDL2_ttf

SRC_DIR		=	src
SRC 		=					\
draw.c							\
lib.c							\
main.c							\
objects.c						\
csg/const_solid_geo.c			\
csg/csg_inter.c					\
csg/csg_sub.c					\
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
parser/parse_objects_type.c		\
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
ui/shape_transforms.c			\
panel/init_panel.c				\
panel/quit_panel.c				\
panel/panel_utils.c				\
panel/draw_panel.c				\
panel/panel_camera_value.c		\
panel/draw_object_bg.c			\
panel/object_spatial_value.c	\
panel/object_light_value.c		\
panel/object_effect_value.c		\
panel/draw_object_name.c		\
panel/draw_object_color.c

OBJ_DIR		=	.obj
OBJ			=	$(SRC:.c=.o)
DEP			=	$(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR)/,$(OBJ))
	$(MAKE) -C libft
	$(CC) $(LDFLAGS) -o $@ $^
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

-include $(addprefix $(OBJ_DIR)/,$(DEP))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(TTF_BUILD)
	$(CC) $(CFLAGS) $(CPPFLAGS) -MMD -o $@ -c $<

$(SDL_BUILD): | $(SDL_DIR)
	curl https://www.libsdl.org/release/$(SDL_TAR) --output $(SDL_TAR)
	tar -xf $(SDL_TAR)
	cd $(SDL_LIB) && ./configure --prefix=$(shell pwd)/$(SDL_DIR)
	$(MAKE) -C $(SDL_LIB)
	$(MAKE) -C $(SDL_LIB) install

$(TTF_BUILD): | $(SDL_BUILD)
	cd $(TTF_DIR) && tar -xf freetype-2.8.tar.gz
	cd $(TTF_DIR) && mkdir freetype_build
	cd $(TTF_DIR)/freetype-2.8 && ./configure --prefix=$(shell pwd)/SDL_text/freetype_build
	$(MAKE) -C $(TTF_DIR)/freetype-2.8
	$(MAKE) -C $(TTF_DIR)/freetype-2.8 install
	cd $(TTF_DIR) && unzip SDL2_ttf-2.0.15.zip
	mkdir $(TTF_DIR)/ttf_build
	cd $(TTF_DIR)/SDL2_ttf-2.0.15 && FT2_CONFIG="$(shell pwd)/SDL_text/freetype_build/bin/freetype-config" SDL2_CONFIG="$(shell pwd)/SDL2/bin/sdl2-config" ./configure --prefix="$(shell pwd)/SDL_text/ttf_build"
	$(MAKE) -C $(TTF_DIR)/SDL2_ttf-2.0.15
	$(MAKE) -C $(TTF_DIR)/SDL2_ttf-2.0.15 install

$(SDL_DIR):
	@mkdir $@ 2> /dev/null || true

$(OBJ_DIR):
	@mkdir $@ 2> /dev/null || true
	@mkdir $@/csg 2> /dev/null || true
	@mkdir $@/effects 2> /dev/null || true
	@mkdir $@/events 2> /dev/null || true
	@mkdir $@/maths 2> /dev/null || true
	@mkdir $@/misc 2> /dev/null || true
	@mkdir $@/parser 2> /dev/null || true
	@mkdir $@/raytracing 2> /dev/null || true
	@mkdir $@/shapes 2> /dev/null || true
	@mkdir $@/ui 2> /dev/null || true
	@mkdir $@/panel 2> /dev/null || true

clean:
	$(MAKE) -C libft clean
	$(RM) $(SDL_TAR)
	$(RM) -r $(SDL_LIB)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(TTF_DIR)/freetype-2.8
	$(RM) -r $(TTF_DIR)/SDL2_ttf-2.0.15

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)
	$(RM) -r $(SDL_DIR)
	$(RM) -r $(TTF_DIR)/freetype_build
	$(RM) -r $(TTF_DIR)/ttf_build
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean
