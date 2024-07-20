NAME = cub3D

SOURCES_DIR = srcs
HEADERS_DIR = includes
OBJECTS_DIR = objs

SOURCES = animation_utils.c \
			check_map.c \
			collision.c \
			color.c \
			crowbar_animation.c \
			door.c \
			draw2.c \
			draw.c \
			draw_utils.c \
			handgun_animation.c \
			hook.c \
			hook_key.c \
			hud.c \
			image.c \
			init_animation.c \
			init.c \
			init_hud.c \
			main.c \
			minimap.c \
			parse_elements.c \
			parse_map2.c \
			parse_map.c \
			player.c \
			player_move.c \
			player_rotate.c \
			raycast_2d_h.c \
			raycast_2d_v.c \
			raycast_3d_h.c \
			raycast_3d_v.c \
			raycast.c \
			render.c \
			rotation.c \
			shotgun_animation.c \
			time.c \
			utils.c

OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I$(HEADERS_DIR) -g -Ofast  -lpthread
LDFLAGS = -L./libft_gc -L./minilibx -lft_gc -lmlx_Linux -lXext -lX11 -lm
AR = ar -rcs

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c
	@mkdir -p $(OBJECTS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	make bonus -C ./libft_gc
	make -C ./minilibx
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)

bonus: ${NAME}

all: ${NAME}

clean:
	@make clean -C ./libft_gc
	#@make clean -C ./minilibx
	${RM} -rf ${OBJECTS_DIR}

fclean: clean
	@make fclean -C ./libft_gc
	${RM} -r ${NAME}

re: fclean all

mlx:
	@mkdir -p minilibx
	@wget -O minilibx/minilibx-linux.tgz https://cdn.intra.42.fr/document/document/24023/minilibx-linux.tgz
	@tar -xzvf minilibx/minilibx-linux.tgz -C minilibx/ --strip-components=1
	${RM} -rf minilibx/minilibx-linux.tgz

.PHONY: all clean fclean re bonus mlx
