# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adavitas <adavitas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/01 21:46:55 by zzhyrgal          #+#    #+#              #
#    Updated: 2026/02/25 18:09:02 by adavitas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := game
CC := cc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -I./includes
LIBFT := ./libft
LIBFT_A := $(LIBFT)/libft.a

SRCS := src/main_testing.c \
		src/parsing/parse.c \
		src/parsing/parse_color.c \
		src/parsing/parse_colors_util.c \
		src/parsing/parse_map.c \
		src/parsing/parse_texture.c \
		src/parsing/parse_texture_utils.c \
		src/parsing/post_validation.c \
		src/parsing/flood_fill.c \
		src/parsing/ext_validate.c \
		src/utils/init.c \
		src/utils/utils.c \
		src/utils/error.c \
		src/clean_up/free_game.c \
		src/clean_up/helper.c \
		get_in_line/get_next_line.c \
		get_in_line/get_next_line_utils.c

OBJS := $(SRCS:.c=.o)
DEPS := $(SRCS:.c=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

