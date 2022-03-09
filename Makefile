
NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address


# **************************************************************************** #
# source code

CFILES = main.c \
	parse.c \
	parse_map_chars.c \
	parse_identifiers.c \
	draw.c \
	drawing_utils.c \
	player_spawn.c \
	raycaster_cast_ray.c \
	raycaster_utils.c \
	raycaster.c \
	sidebar.c \
	parse_map.c \
	parse_map_check_map.c \
	parse_map_check_borders.c \
	parse_map_checkers.c \
	mlx.c \
	movement.c \
	movement_newpos.c \
	movement_checkpos.c \
	inits.c \
	vector_utils.c \
	texture_map.c \
	parse_colors.c 

HEADERS_MANDATORY = cub3D_mandatory.h
BONUS_HEADERS = cub3D_bonus.h

BONUS_CFILES = \
	main_bonus.c \
	parse_bonus.c \
	parse_map_chars_bonus.c \
	parse_identifiers_bonus.c \
	draw_bonus.c \
	drawing_utils_bonus.c \
	player_bonus.c \
	minimap_bonus.c \
	raycast_bonus.c \
	fullmap_bonus.c \
	sidebar_bonus.c \
	parse_map_bonus.c \
	parse_map_check_map_bonus.c \
	parse_map_check_borders_bonus.c \
	parse_map_checkers_bonus.c \
	mlx_bonus.c \
	movement_bonus.c \
	init_structs_bonus.c \
	system_utils_bonus.c \
	texture_map_bonus.c \
	utils_bonus.c \
	init_anim_sprites_bonus.c \

# **************************************************************************** #
# loctaions

BUILD_DIR ?= ./builds_mandatory
SOURCE_DIR ?= ./sources_mandatory
INCL_DIR ?= ./header_mandatory

BONUS_BUILD_DIR ?= ./builds_bonus
BONUS_SOURCE_DIR ?= ./sources_bonus
BONUS_INCL_DIR ?= ./header_bonus

LIBFT_PATH = ./libft
MLX_PATH = ./minilibx_macos

# **************************************************************************** #
# internal setups

SOURCES := $(addprefix $(SOURCE_DIR)/,$(CFILES))
OFILES := $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(CFILES)))
INCLUDES := $(addprefix $(INCL_DIR)/,$(HEADERS_MANDATORY))

BONUS_SOURCES := $(addprefix $(BONUS_SOURCE_DIR)/,$(BONUS_CFILES))
BONUS_OFILES := $(addprefix $(BONUS_BUILD_DIR)/, $(patsubst %.c, %.o, $(BONUS_CFILES)))
BONUS_INCLUDES := $(addprefix $(BONUS_INCL_DIR)/,$(BONUS_HEADERS))

LFT_LINKING = -L $(LIBFT_PATH) -lft -I $(LIBFT_PATH)/libft.h
MLX_LINKING = -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

# **************************************************************************** #
# compile

all: $(NAME)

$(NAME): compile_mlx compile_libft $(BUILD_DIR) $(OFILES) $(INCLUDES)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(MLX_LINKING) -lm $(LFT_LINKING)
	@ echo "$(GREEN)Created executable '$(NAME)'$(NC)"


bonus: compile_mlx compile_libft $(BONUS_BUILD_DIR) $(BONUS_OFILES) $(BONUS_INCLUDES)
	@ $(CC) $(CFLAGS) -o $(NAME) $(BONUS_OFILES) $(MLX_LINKING) -lm $(LFT_LINKING)
	@ echo "$(GREEN)Created executable '$(NAME)' bonus version$(NC)"

compile_libft:
	@ make -C $(LIBFT_PATH)

compile_mlx:
	@ make -C $(MLX_PATH)

$(BUILD_DIR):
	@ mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@ $(CC) $(CFLAGS) $^ -c -o $@

$(BONUS_BUILD_DIR):
	@ mkdir -p $(BONUS_BUILD_DIR)

$(BONUS_BUILD_DIR)/%.o : $(BONUS_SOURCE_DIR)/%.c
	@ $(CC) $(CFLAGS) $^ -c -o $@


.PHONY: clean

clean:
#@ make clean -C $(LIBFT_PATH)
#@ make clean -C $(MLX_PATH)
	@ echo "$(RED)Removing object files$(NC)"
	@ rm -rf $(OFILES)
	@ rm -rf $(BONUS_OFILES)

fclean: clean
#@ make fclean -C $(LIBFT_PATH)
	@ echo "$(RED)Removing '$(NAME)'\nForce-removing object directory$(NC)"
	@ rm -rf $(BUILD_DIR) *~ $(NAME)
	@ rm -rf $(BONUS_BUILD_DIR) *~ $(NAME)

re: fclean
	@ make

re_bonus: fclean
	@ bonus

