# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssoeno <ssoeno@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/23 19:04:11 by ssoeno            #+#    #+#              #
#    Updated: 2024/06/09 17:47:34 by ssoeno           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fract-ol

CC = gcc
CFLAGS = -Wall -Werror -Wextra

# PRINTF = ft_printf/libftprintf.a
PRINTF = ft_printf
LIBFT = $(PRINTF)/libft
MLX = minilibx/libmlx.a

SRCS = main.c events.c init.c render.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PRINTF)/libftprintf.a $(MLX)
	# $(CC) $(OBJS)  -Lft_printf/libft -lft -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	$(CC) $(OBJS)  -L$(PRINTF) -lftprintf -Lminilibx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(PRINTF)/libftprintf.a:
	make -C $(PRINTF)

%.o: %.c
	$(CC) $(CFLAGS) -I$(PRINTF) -Imlx -c $< -o $@

clean:
	make -C $(PRINTF) clean
	${RM} ${OBJS}

fclean: clean
	make -C $(PRINTF) fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re