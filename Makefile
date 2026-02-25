# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/01 21:46:55 by zzhyrgal          #+#    #+#              #
#    Updated: 2026/02/22 21:33:17 by zzhyrgal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -cc
INCLUDES = -I./includes -I./get_in_line -I./libft

# Source files
PARSE_SRC = parsing/parse.c \
			parsing/parse_color.c \
			parsing/parse_colors_util.c \
			parsing/parse_color_utils2.c \
			parsing/parse_map.c \
			parsing/parse_map_utils.c \
			parsing/parse_player.c \
			parsing/parse_texture.c \
			parsing/parse_texture_utils.c \
			parsing/parse_utils.c \
			parsing/post_validation.c \
			parsing/post_validation_utils.c

GNL_SRC = get_in_line/get_next_line.c \
		  get_in_line/get_next_line_utils.c

UTILS_SRC = utils/utils.c \
			utils/init.c

CLEAN_SRC = clean_up/free_game.c

MAIN_SRC = parsing/main_testing.c

# Object files
PARSE_OBJ = $(PARSE_SRC:.c=.o)
GNL_OBJ = $(GNL_SRC:.c=.o)
UTILS_OBJ = $(UTILS_SRC:.c=.o)
CLEAN_OBJ = $(CLEAN_SRC:.c=.o)
MAIN_OBJ = $(MAIN_SRC:.c=.o)

OBJ = $(PARSE_OBJ) $(GNL_OBJ) $(UTILS_OBJ) $(CLEAN_OBJ) $(MAIN_OBJ)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -lm -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

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

.PHONY: all clean fclean re test test_all norm