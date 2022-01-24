
NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror


# **************************************************************************** #
# source code

MAIN = main.c

#CFILES_ALICE = 

#CFILES_ANDI =

HEADERS = cub3d.h

# **************************************************************************** #
# loctaions

BUILD_DIR ?= ./builds
SOURCE_DIR ?= ./sources
INCL_DIR ?= ./header
LIBFT_PATH = libft

# **************************************************************************** #
# internal vars

CFILES := $(CFILES_ALICE) $(CFILES_ANDI) $(MAIN)
SOURCES := $(addprefix $(SOURCE_DIR)/,$(CFILES))
OFILES := $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(CFILES)))
INCLUDES := $(addprefix $(INCL_DIR)/,$(HEADERS))
LFT_LINKING = -L $(LIBFT_PATH) -lft -I $(LIBFT_PATH)/libft.h

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

# **************************************************************************** #
# compile

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OFILES) $(INCLUDES)
	@ $(MAKE) -C $(LIBFT_PATH)
	@ $(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LFT_LINKING)
	@ echo "$(GREEN)Built executable '$(NAME)'$(NC)"

$(BUILD_DIR):
	@ mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@ $(CC) $(CFLAGS) $^ -c -o $@
	@ echo "$(GREEN)Built object files$(NC)"

.PHONY: clean

clean:
	@ make clean -C $(LIBFT_PATH)
	@ echo "Cleaning libft"
	@ echo "$(RED)Removing created object files$(NC)"
	@ rm -rf $(OFILES)

fclean: clean
	@ make fclean -C $(LIBFT_PATH)
	@ echo "$(RED)Removing executable\nForce-removing directory 'builds'$(NC)"
	@ rm -rf $(BUILD_DIR) *~ $(NAME)

re: fclean
	@ make

