CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = libftsprintf.a
SRCDIR = ./srcs/
INCLDIR = ./includes/
SRCS = $(SRCDIR)ft_sprintf.c \
	   $(SRCDIR)calcul.c \
	   $(SRCDIR)parser.c \
	   $(SRCDIR)add_cs_to_buffer.c \
	   $(SRCDIR)add_d_to_buffer.c \
	   $(SRCDIR)add_f_to_buffer.c \
	   $(SRCDIR)add_o_to_buffer.c \
	   $(SRCDIR)add_p_to_buffer.c \
	   $(SRCDIR)add_u_to_buffer.c \
	   $(SRCDIR)add_x_to_buffer.c \
	   $(SRCDIR)add_xmaj_to_buffer.c \
	   $(SRCDIR)add_percent_to_buff.c \
	   $(SRCDIR)adjust_str.c \
	   $(SRCDIR)ft_affichage.c \
	   $(SRCDIR)infinity.c \
	   $(SRCDIR)infinity_add.c \
	   $(SRCDIR)send_to_buffer.c \
	   $(SRCDIR)ultimate_double_calculator.c \
	   $(SRCDIR)utilitys.c \
	   $(SRCDIR)utilitys2.c
OBJS_ = $(SRCS:.c=.o)
OBJS = $(notdir $(OBJS_))

all : $(NAME)

$(NAME) : $(SRCS)
	@make objects
	@ar rc $(NAME) $(OBJS)
	@echo "\n\033[36mCreation :\033[0m \033[35;4m$(NAME)\033[0m\n"
	@ranlib $(NAME)
	@echo "\033[36mIndexation :\033[0m \033[35;4m$(NAME)\033[0m\n"

objects : $(OBJS)

%.o : $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c -I $(INCLDIR) $^
	@echo "\033[36mCompilation :\033[0m \033[32m$*\033[0m"

clean :
	@rm -rf $(OBJS)
	@echo "\n\033[36mDeletion :\033[0m \033[32mObjects\033[0m\n"

fclean : clean
	@rm -rf $(NAME)
	@echo "\033[36mDeletion :\033[0m \033[35;4m$(NAME)\033[0m\n"

re : fclean all

.PHONY : all objects clean fclean re
