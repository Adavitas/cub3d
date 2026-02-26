# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/01 21:46:55 by zzhyrgal          #+#    #+#              #
#    Updated: 2026/02/26 21:28:49 by adavitas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./libraries/get_next_line -I./libraries/libft/src -I./minilibx-linux

# Source files
PARSE_SRC = src/parsing/parse.c \
			src/parsing/parse_color.c \
			src/parsing/parse_colors_util.c \
			src/parsing/parse_color_utils2.c \
			src/parsing/parse_map.c \
			src/parsing/parse_map_utils.c \
			src/parsing/parse_player.c \
			src/parsing/parse_texture.c \
			src/parsing/parse_texture_utils.c \
			src/parsing/parse_utils.c \
			src/parsing/post_validation.c \
			src/parsing/post_validation_utils.c

GNL_SRC = libraries/get_next_line/get_next_line.c \
		  libraries/get_next_line/get_next_line_utils.c

UTILS_SRC = src/utils/utils.c \
			src/utils/init.c

PLAYER_SRC = src/player_movement/collision.c \
			 src/player_movement/move.c \
			 src/player_movement/player_rotate.c \
			 src/player_movement/update_player.c

GRAPHICS_SRC = src/graphics/init_mlx.c \
			 src/graphics/close_game.c

CLEAN_SRC = src/clean_up/free_game.c

MAIN_SRC = src/main.c

# Object files
PARSE_OBJ = $(PARSE_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)
UTILS_OBJ = $(UTILS_SRC:.c=.o)
PLAYER_OBJ = $(PLAYER_SRC:.c=.o)
GRAPHICS_OBJ = $(GRAPHICS_SRC:.c=.o)
CLEAN_OBJ = $(CLEAN_SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)

OBJ = $(PARSE_OBJ) $(GNL_OBJ) $(UTILS_OBJ) $(PLAYER_OBJ) $(GRAPHICS_OBJ) $(CLEAN_OBJ) $(MAIN_OBJ)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): libft mlx $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -Llibraries/libft -lft -Lminilibx-linux -lmlx -lX11 -lXext -lm -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

libft:
	@$(MAKE) -C libraries/libft

mlx:
	@$(MAKE) -C minilibx-linux

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo "$(GREEN)✓ Object files cleaned$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C libraries/libft fclean
	@$(MAKE) -C minilibx-linux clean
	@echo "$(GREEN)✓ $(NAME) removed$(RESET)"

re: fclean all

# Test with different .cub files
test: $(NAME)
	@echo "$(YELLOW)Testing parser with valid file...$(RESET)"
	./$(NAME) test_files/file.cub

test_all: $(NAME)
	@echo "$(YELLOW)Testing all .cub files...$(RESET)"
	@for file in test_files/*.cub; do \
		echo "\n$(YELLOW)Testing $$file$(RESET)"; \
		./$(NAME) $$file; \
		echo ""; \
	done

# Norminette check
norm:
	@echo "$(YELLOW)Running norminette...$(RESET)"
	@norminette parsing/ includes/ utils/ clean_up/ get_in_line/ main_testing.c || true

.PHONY: all clean fclean re test test_all norm libft mlx