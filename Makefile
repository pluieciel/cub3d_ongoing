NAME = $(MANDATORY_DIR)/cub3D
BONUS_NAME = $(BONUS_DIR)/cub3D

MANDATORY_DIR = mandatory
BONUS_DIR = bonus

SOURCES_DIR = srcs
HEADERS_DIR = includes
OBJECTS_DIR = objs

MANDATORY_SOURCES = check_map.c \
					color.c \
					draw.c \
					draw_utils.c \
					hook.c \
					hook_key.c \
					image.c \
					init.c \
					main.c \
					parse_elements.c \
					parse_map2.c \
					parse_map.c \
					player.c \
					player_move.c \
					player_rotate.c \
					raycast_3d_h.c \
					raycast_3d_v.c \
					raycast.c \
					render.c \
					rotation.c \
					time.c \
					utils.c

BONUS_SOURCES = animation_utils.c \
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

MANDATORY_OBJECTS = $(addprefix $(MANDATORY_DIR)/$(OBJECTS_DIR)/, $(MANDATORY_SOURCES:.c=.o))
BONUS_OBJECTS = $(addprefix $(BONUS_DIR)/(OBJECTS_DIR)/, $(BONUS_SOURCES:.c=.o))

CFLAGS = -Wall -Wextra -Werror -g -Ofast -lpthread
LDFLAGS = -L./libft_gc -L./minilibx -lft_gc -lmlx_Linux -lXext -lX11 -lm

$(MANDATORY_DIR)/$(OBJECTS_DIR)/%.o: $(MANDATORY_DIR)/$(SOURCES_DIR)/%.c
	@mkdir -p $(MANDATORY_DIR)/$(OBJECTS_DIR)
	$(CC) $(CFLAGS) -I$(MANDATORY_DIR)/$(HEADERS_DIR) -c $< -o $@

$(BONUS_DIR)/$(OBJECTS_DIR)/%.o: $(BONUS_DIR)/$(SOURCES_DIR)/%.c
	@mkdir -p $(BONUS_DIR)/$(OBJECTS_DIR)
	$(CC) $(CFLAGS) -I$(BONUS_DIR)/$(HEADERS_DIR) -c $< -o $@

$(NAME): $(MANDATORY_OBJECTS)
	make bonus -C ./libft_gc
	make -C ./minilibx
	$(CC) $(CFLAGS) -I$(MANDATORY_DIR)/$(HEADERS_DIR) $(MANDATORY_OBJECTS) -o $@ $(LDFLAGS)

$(BONUS_NAME): $(BONUS_OBJECTS)
	make bonus -C ./libft_gc
	make -C ./minilibx
	$(CC) $(CFLAGS) -I$(BONUS_DIR)/$(HEADERS_DIR) $(BONUS_OBJECTS) -o $@ $(LDFLAGS)

bonus: $(BONUS_NAME)

all: $(NAME) bonus

clean:
	@make clean -C ./libft_gc
	${RM} -rf $(MANDATORY_DIR)/$(OBJECTS_DIR) $(BONUS_DIR)/$(OBJECTS_DIR)

fclean: clean
	@make fclean -C ./libft_gc
	${RM} -r $(NAME) $(BONUS_NAME)

re: fclean all

mlx:
	@mkdir -p minilibx
	@wget -O minilibx/minilibx-linux.tgz https://cdn.intra.42.fr/document/document/25926/minilibx-linux.tgz
	@tar -xzvf minilibx/minilibx-linux.tgz -C minilibx/ --strip-components=1
	${RM} -rf minilibx/minilibx-linux.tgz

.PHONY: all bonus clean fclean re mlx
