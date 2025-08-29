# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msabr <msabr@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 00:33:01 by msabr             #+#    #+#              #
#    Updated: 2025/03/18 02:07:31 by msabr            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

#mandatory
NAME_CLIENT = client
NAME_SERVER = server

SRCS_CLIENT = mandatory/client.c mandatory/minilib.c
SRCS_SERVER = mandatory/server.c mandatory/minilib.c
			
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

HEADER = mandatory/ft_minitalk.h

#bonus
NAME_CLIENT_BONUS = client_bonus
NAME_SERVER_BONUS = server_bonus

SRCS_CLIENT_BONUS = bonus/client_bonus.c bonus/minilib_bonus.c
SRCS_SERVER_BONUS = bonus/server_bonus.c bonus/minilib_bonus.c
			
OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

HEADER_BONUS = bonus/ft_minitalk_bonus.h

#rules
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(NAME_SERVER)

bonus: $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

$(NAME_CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(NAME_SERVER_BONUS)

%bonus.o:%bonus.c $(HEADER_BONUS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)
	$(RM) $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean: clean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)
	$(RM) $(NAME_CLIENT_BONUS) $(NAME_SERVER_BONUS)

re: fclean all

.PHONY: clean