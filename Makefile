# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almighty <almighty@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/01 21:00:05 by almighty          #+#    #+#              #
#    Updated: 2026/06/02 00:07:23 by almighty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = cc
CCFLAGS = -Wall -Wextra -Werror
MLX = libmlx.a
MLX_DIR = mlx_linux


DIR_SRCS	:= regular/srcs
DIR_OBJS	:= regular/objs

SRCS	:=	$(DIR_SRCS)/main.c\
			$(DIR_SRCS)/get_intersection.c\
			$(DIR_SRCS)/ray.c\
			$(DIR_SRCS)/vector.c\
			$(DIR_SRCS)/vector2.c\

OBJS	:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(MLX_DIR) all
	$(CC) $(CCFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(MLX_DIR)/$(MLX)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	$(CC) $(CCFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	#@$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re