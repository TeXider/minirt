# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almighty <almighty@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/01 21:00:05 by almighty          #+#    #+#              #
#    Updated: 2026/06/30 14:06:25 by almighty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = cc
CCFLAGS = -Wall -Wextra -Wno-incompatible-pointer-types -g -O3
MLX = libmlx.a
MLX_DIR = mlx_linux


DIR_SRCS	:= regular/srcs
DIR_OBJS	:= regular/objs

SRCS	:=	$(DIR_SRCS)/main.c\
			$(DIR_SRCS)/others/colors.c\
			$(DIR_SRCS)/others/error_handling.c\
			$(DIR_SRCS)/others/init_env.c\
			$(DIR_SRCS)/others/mlx_funcs.c\
			$(DIR_SRCS)/others/memory.c\
			$(DIR_SRCS)/others/extend_len.c\
			$(DIR_SRCS)/parsing/go_to_next_line.c\
			$(DIR_SRCS)/parsing/parse_file.c\
			$(DIR_SRCS)/parsing/parsing_utils.c\
			$(DIR_SRCS)/parsing/shape_parsing.c\
			$(DIR_SRCS)/parsing/singleton_parsing.c\
			$(DIR_SRCS)/parsing/get_num.c\
			$(DIR_SRCS)/parsing/get_composite.c\
			$(DIR_SRCS)/rt_math/get_intersection.c\
			$(DIR_SRCS)/rt_math/ray.c\
			$(DIR_SRCS)/rt_math/render_image.c\
			$(DIR_SRCS)/rt_math/utils.c\
			$(DIR_SRCS)/rt_math/vector.c\
			$(DIR_SRCS)/rt_math/vector2.c\
			$(DIR_SRCS)/.debug.c

OBJS	:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(MLX_DIR) all
	$(CC) $(CCFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(MLX_DIR)/$(MLX)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -rf $(DIR_OBJS)
	@$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	#@$(MAKE) -C $(MLX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
