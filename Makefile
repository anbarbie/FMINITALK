# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: antbarbi <antbarbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/17 02:43:38 by antbarbi          #+#    #+#              #
#    Updated: 2021/08/17 02:43:38 by antbarbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS += -Iinclude -Wall -Werror -Wextra

NAME_SERVER = server
NAME_CLIENT = client

SRC_COMMON = src/libft

SRCS_SERVER:= $(shell find $(SRC_COMMON) src/server -name "*.c")
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

SRCS_CLIENT:= $(shell find $(SRC_COMMON) src/client -name "*.c")
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT)

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C bonus clean
	find . -name "*.o" -delete -print

fclean: clean
	$(MAKE) -C bonus fclean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

bonus:
	$(MAKE) -C bonus
	cp bonus/$(NAME_SERVER) .
	cp bonus/$(NAME_CLIENT) .

debug: CFLAGS += -g
debug: fclean bonus

.PHONY: all clean fclean re bonus debug
