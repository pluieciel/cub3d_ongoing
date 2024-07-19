NAME = cub3D

SOURCES_DIR = srcs
HEADERS_DIR = includes
OBJECTS_DIR = objs

SOURCES = animation_utils.c image.c door.c draw_utils.c hook_key.c init.c minimap.c player.c raycast2d.c render.c utils.c \
check_map.c color.c draw2.c handgun_animation.c init_hud.c parse_elements.c player_move.c raycast3d2.c rotation.c \
collision.c crowbar_animation.c draw.c hook.c init_animation.c main.c parse_map.c parse_map2.c player_rotate.c raycast3d.c time.c hud.c

OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -I$(HEADERS_DIR) -g
LDFLAGS = -L./libft_gc -L./minilibx -lft_gc -lmlx_Linux -lXext -lX11 -lm -lpthread -Ofast
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
