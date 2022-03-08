
NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address


# **************************************************************************** #
# source code

MAIN = main.c

CFILES_ALICE = \
	parse.c \
	parse_map_chars.c \
	parse_identifiers.c \
	draw.c \
	drawing_utils.c \
	player.c \
	minimap.c \
	raycast.c \
	fullmap.c \
	sidebar.c

CFILES_ANDI = \
	parse_map.c \
	parse_map_check_map.c \
	parse_map_check_borders.c \
	mlx.c \
	movement.c \
	init_structs.c \
	system_utils.c \
	texture_map.c \
	utils.c

HEADERS = cub3D.h

# **************************************************************************** #
# loctaions

BUILD_DIR ?= ./builds
SOURCE_DIR ?= ./sources
INCL_DIR ?= ./header
LIBFT_PATH = ./libft
MLX_PATH = ./minilibx_macos

# **************************************************************************** #
# internal setups

CFILES := $(CFILES_ALICE) $(CFILES_ANDI) $(MAIN)
SOURCES := $(addprefix $(SOURCE_DIR)/,$(CFILES))
OFILES := $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(CFILES)))
INCLUDES := $(addprefix $(INCL_DIR)/,$(HEADERS))
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

compile_libft:
	@ make -C $(LIBFT_PATH)

$(BUILD_DIR):
	@ mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@ $(CC) $(CFLAGS) $^ -c -o $@

compile_mlx:
	@ make -C $(MLX_PATH)

.PHONY: clean

clean:
#@ make clean -C $(LIBFT_PATH)
#@ make clean -C $(MLX_PATH)
	@ echo "$(RED)Removing object files$(NC)"
	@ rm -rf $(OFILES)

fclean: clean
#@ make fclean -C $(LIBFT_PATH)
	@ echo "$(RED)Removing '$(NAME)'\nForce-removing object directory$(NC)"
	@ rm -rf $(BUILD_DIR) *~ $(NAME)

re: fclean
	@ make
