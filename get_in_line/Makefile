# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zzhyrgal <zzhyrgal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 12:39:30 by zzhyrgal          #+#    #+#              #
#    Updated: 2025/08/16 12:24:44 by zzhyrgal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -DBUFFER_SIZE=1000000000

NAME    = get_next_line.a
SRCS    = get_next_line.c get_next_line_utils.c
OBJS    = $(SRCS:.c=.o)

TEST    = test_gnl
TESTSRC = main.c
TESTOBJ = $(TESTSRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME) $(TESTOBJ)
	$(CC) $(CFLAGS) $(TESTOBJ) $(NAME) -o $(TEST)

clean:
	rm -f $(OBJS) $(TESTOBJ)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re test
