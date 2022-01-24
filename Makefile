
NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror


# **************************************************************************** #
# source code

MAIN = main.c

CFILES_ALICE =

CFILES_ANDI =

HEADERS = cub3d.h

LIBRARIES_TO_COMPILE = libft


# **************************************************************************** #
# loctaions

BUILD_DIR ?= ./builds
SOURCE_DIR ?= ./sources
INCL_DIR ?= ./header

CFILES := $(CFILES_ALICE) $(CFILES_ANDI) $(MAIN)
SOURCES := $(addprefix $(SOURCE_DIR)/,$(CFILES))
OFILES := $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(CFILES)))
INCLUDES := $(addprefix $(INCL_DIR)/,$(HEADERS))


# **************************************************************************** #
# compile

GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m

all: $(NAME)

$(NAME): $(BUILD_DIR) $(OFILES) $(INCLUDES)
	@ echo "$(GREEN)Creating executable '$(NAME)'$(NC)"
	@ $(CC) $(CFLAGS) -o $(NAME) $(OFILES)

$(BUILD_DIR):
	@ mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SOURCE_DIR)/%.c
	@ echo "$(GREEN)Building object files$(NC)"
	@ $(CC) $(CFLAGS) $^ -c -o $@

.PHONY: clean

clean:
	@ echo "$(RED)Removing created object files$(NC)"
	@ rm -rf $(OFILES)

fclean: clean
	@ echo "$(RED)Removing executable\nForce-removing directory 'builds'$(NC)"
	@ rm -rf $(BUILD_DIR) *~ $(NAME)

re: fclean
	@ make

