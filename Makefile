# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpeck <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/06 18:25:31 by dpeck             #+#    #+#              #
#    Updated: 2019/04/13 12:29:59 by dpeck            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_PATH = src/
INC_PATH = includes/
OBJ_PATH = obj/

SRC = audio.c \
	  bullet_collision.c \
	  clean_lists.c \
	  dda.c \
	  door.c \
	  door_timer.c \
	  draw_sprites.c \
	  draw_wall_and_sky.c \
	  enemy_actions.c \
	  enemy_ai.c \
	  enemy_decisions.c \
	  enemy_textures1.c \
	  enemy_textures2.c \
	  events.c \
	  floorcast.c \
	  free_everything.c \
	  free_sdl_struct.c \
	  get_sprite_texture.c \
	  init_lookup_tables.c \
	  init_sdl.c \
	  init_sprite.c \
	  init_wolf.c \
	  main.c \
	  movement.c \
	  pickups.c \
	  qsort.c \
	  raycast.c \
	  read.c \
	  setup_game.c \
	  setup_text.c \
	  sprite_cast.c \
	  sprite_loader.c \
	  sprite_read.c \
	  texture_load.c \
	  update_frame.c \
	  update_ui.c \
	  util.c \
	  validate_map.c \
	  validate_sdl.c \
	  wall_bounds.c

HEADER = includes/wolf.h
LIBFT = includes/libft/
LIB = -L lib
SDL = -Wl -lSDL2main -lSDL2
SDLDEPEND = -lm -liconv -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal
TTF = -lbz2 -lpng16 -lz -lfreetype -lSDL2_ttf
MIXER = -logg -lvorbisfile -lvorbisenc -lvorbis -lmodplug.1 -lSDL2_mixer
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
INC_LFT = $(addprefix -I, includes/libft/)

OBJ_NAME = $(subst .c,.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	make -C includes/libft/
	gcc -Wall -Wextra -Werror -o $(NAME) $(OBJ) -L includes/libft/ -lft $(LIB) $(SDL) $(SDLDEPEND) $(TTF) $(MIXER)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	gcc -Wall -Wextra -Werror $(INC) -o $@ -c $<

test: $(OBJ)
	gcc -o $(NAME) $(OBJ) -L includes/libft/ -lft $(SDL) $(SDLDEPEND) $(TTF) $(MIXER)

clean:
	make -C includes/libft/ clean
	/bin/rm -rf $(OBJ_PATH)

fclean: clean
	make -C includes/libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
