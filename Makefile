# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/07/24 14:45:12 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -L$(LIBDIR)/ -L$(LIBDIR)/libft/ft_printf -lft -lftprintf -lm

UNAME_S := $(shell uname -s)

ifeq	($(UNAME_S),Darwin)
	SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
	SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
	SDL2_ttf = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
	LDFLAGS += -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
	CFLAGS += -F ./frameworks
endif

SRC=$(SRCDIR)/main.c\
	$(SRCDIR)/input/input.c\
	$(SRCDIR)/input/input2.c\
	$(SRCDIR)/input/mouse_event.c\
	$(SRCDIR)/utils/error.c\
	$(SRCDIR)/utils/utils.c\
	$(SRCDIR)/utils/tools.c\
	$(SRCDIR)/utils/print.c\
	$(SRCDIR)/utils/verbose.c\
	$(SRCDIR)/utils/color.c\
	$(SRCDIR)/env/init.c\
	$(SRCDIR)/env/env.c\
	$(SRCDIR)/env/event.c\
	$(SRCDIR)/env/env_texture.c\
	$(SRCDIR)/env/draw.c\
	$(SRCDIR)/gui/button.c\
	$(SRCDIR)/loader/map_parse.c\
	$(SRCDIR)/loader/textures.c\
	$(SRCDIR)/loader/load_game.c\
	$(SRCDIR)/linked/linked_list.c\
	$(SRCDIR)/linked/button_list.c\
	$(SRCDIR)/constructor/constructor.c\
	$(SRCDIR)/geometry/vector.c\
	$(SRCDIR)/graphics/graphics.c\
	$(SRCDIR)/graphics/drawing.c\
	$(SRCDIR)/graphics/intersections.c\
	$(SRCDIR)/graphics/object_intersections.c\
	$(SRCDIR)/graphics/raycast.c\
	$(SRCDIR)/graphics/textures.c\
	$(SRCDIR)/player_behave/keyboard_handling.c\
	$(SRCDIR)/player_behave/player_behaviour.c\
	$(SRCDIR)/interface/interface.c\
	$(SRCDIR)/sdl/bresenham.c\
	$(SRCDIR)/sdl/sdl.c

OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/input2.o\
	$(LIBDIR)/mouse_event.o\
	$(LIBDIR)/error.o\
	$(LIBDIR)/bresenham.o\
	$(LIBDIR)/map_parse.o\
	$(LIBDIR)/textures.o\
	$(LIBDIR)/load_game.o\
	$(LIBDIR)/linked_list.o\
	$(LIBDIR)/button_list.o\
	$(LIBDIR)/button.o\
	$(LIBDIR)/constructor.o\
	$(LIBDIR)/print.o\
	$(LIBDIR)/env.o\
	$(LIBDIR)/event.o\
	$(LIBDIR)/env_texture.o\
	$(LIBDIR)/draw.o\
	$(LIBDIR)/graphics.o\
	$(LIBDIR)/textures.o\
	$(LIBDIR)/raycast.o\
	$(LIBDIR)/drawing.o\
	$(LIBDIR)/intersections.o\
	$(LIBDIR)/object_intersections.o\
	$(LIBDIR)/interface.o\
	$(LIBDIR)/tools.o\
	$(LIBDIR)/vec2.o\
	$(LIBDIR)/utils.o\
	$(LIBDIR)/verbose.o\
	$(LIBDIR)/color.o\
	$(LIBDIR)/init.o\
	$(LIBDIR)/keyboard_handling.o\
	$(LIBDIR)/player_behaviour.o\
	$(LIBDIR)/sdl.o

NAME=editor

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)/libft/ fclean && make -C $(LIBDIR)/libft
	@cp $(LIBDIR)/libft/libft.a $(LIBDIR)/
	$(CC) $(LDFLAGS) -o $@ $^
ifeq ($(UNAME_S),Darwin)
		@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
		@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)
		@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
endif

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/*/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o
	rm -rf $(LIBDIR)/libft.a
	make -C $(LIBDIR)/libft clean

fclean:clean
	rm -rf $(NAME)
	make -C $(LIBDIR)/libft fclean

re : fclean all
