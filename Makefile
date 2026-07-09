# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almighty <almighty@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/01 21:00:05 by almighty          #+#    #+#              #
#    Updated: 2026/07/09 01:54:06 by almighty         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = cc
CCFLAGS = -Wall -Wextra -g -O3 -Wno-incompatible-pointer-types
MLX = libmlx.a
MLX_DIR = mlx_linux


DIR_SRCS		:= regular/srcs
DIR_OBJS		:= regular/objs
DIR_SRCS_BON	:= bonus/srcs
DIR_OBJS_BON	:= bonus/objs

SRCS	:=	$(DIR_SRCS)/main.c\
			$(DIR_SRCS)/others/colors.c\
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
			$(DIR_SRCS)/rt_math/ray_trace.c\
			$(DIR_SRCS)/rt_math/render_image.c\
			$(DIR_SRCS)/rt_math/utils.c\
			$(DIR_SRCS)/rt_math/vector.c\
			$(DIR_SRCS)/rt_math/vector2.c\
			$(DIR_SRCS)/err_handling/env_err.c\
			$(DIR_SRCS)/err_handling/parsing_err.c\
			$(DIR_SRCS)/err_handling/parsing_err2.c\
			$(DIR_SRCS)/err_handling/parsing_hints.c\
			$(DIR_SRCS)/.debug.c

SRCS_BON	:=	$(DIR_SRCS_BON)/main.c\
				$(DIR_SRCS_BON)/others/colors.c\
				$(DIR_SRCS_BON)/others/init_env.c\
				$(DIR_SRCS_BON)/others/mlx_funcs.c\
				$(DIR_SRCS_BON)/others/memory.c\
				$(DIR_SRCS_BON)/others/extend_len.c\
				$(DIR_SRCS_BON)/parsing/go_to_next_line.c\
				$(DIR_SRCS_BON)/parsing/parse_file.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils.c\
				$(DIR_SRCS_BON)/parsing/init_shape_vals.c\
				$(DIR_SRCS_BON)/parsing/shape_parsing.c\
				$(DIR_SRCS_BON)/parsing/singleton_parsing.c\
				$(DIR_SRCS_BON)/parsing/get_num.c\
				$(DIR_SRCS_BON)/parsing/get_composite.c\
				$(DIR_SRCS_BON)/rt_math/get_intersection.c\
				$(DIR_SRCS_BON)/rt_math/get_top_intersection.c\
				$(DIR_SRCS_BON)/rt_math/is_in_shadow.c\
				$(DIR_SRCS_BON)/rt_math/ray_trace.c\
				$(DIR_SRCS_BON)/rt_math/render_image.c\
				$(DIR_SRCS_BON)/rt_math/set_shape_inter_vals.c\
				$(DIR_SRCS_BON)/rt_math/shape_surf_n.c\
				$(DIR_SRCS_BON)/rt_math/shape_surf_n2.c\
				$(DIR_SRCS_BON)/rt_math/shape_color.c\
				$(DIR_SRCS_BON)/rt_math/utils.c\
				$(DIR_SRCS_BON)/rt_math/textures.c\
				$(DIR_SRCS_BON)/rt_math/vector.c\
				$(DIR_SRCS_BON)/rt_math/vector2.c\
				$(DIR_SRCS_BON)/err_handling/env_err.c\
				$(DIR_SRCS_BON)/err_handling/parsing_err.c\
				$(DIR_SRCS_BON)/err_handling/parsing_err2.c\
				$(DIR_SRCS_BON)/err_handling/parsing_hints.c\
				$(DIR_SRCS_BON)/.debug.c

OBJS		:=	$(patsubst %.c, $(DIR_OBJS)/%.o, $(subst $(DIR_SRCS)/,,$(SRCS)))
OBJS_BON	:=	$(patsubst %.c, $(DIR_OBJS_BON)/%.o, $(subst $(DIR_SRCS_BON)/,,$(SRCS_BON)))

all: $(NAME)

$(DIR_OBJS)/%.o: $(DIR_SRCS)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
	@curr=$$(find $(DIR_OBJS) -iname "*.o" | wc -l); \
	total=$$(find $(DIR_SRCS) -iname "*.c" | wc -l); \
	printf "\r\e[?25lCompiling : \e[1m⟬\e[107m%*s\e[0m%*s\e[1m⟭\e[0m %d/%d" \
		$$curr "" $$(($$total - $$curr)) "" $$curr $$total

$(DIR_OBJS_BON)/%.o: $(DIR_SRCS_BON)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
	@curr=$$(find $(DIR_OBJS_BON) -iname "*.o" | wc -l); \
	total=$$(find $(DIR_SRCS_BON) -iname "*.c" | wc -l); \
	printf "\r\e[?25lCompiling : \e[1m⟬\e[107m%*s\e[0m%*s\e[1m⟭\e[0m %d/%d" \
		$$curr "" $$(($$total - $$curr)) "" $$curr $$total

$(NAME): $(OBJS)
	@printf "\n\nCompiling MiniLibX:\n"
	@$(MAKE) -C $(MLX_DIR) all
	@$(CC) $(CCFLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(MLX_DIR)/$(MLX)
	@printf "\n✅ Compilation completed: $(NAME)\e[?25h\n"

bonus : $(OBJS_BON)
	@printf "\n\nCompiling MiniLibX:\n"
	@$(MAKE) -C $(MLX_DIR) all
	@$(CC) $(CCFLAGS) $(OBJS_BON) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(MLX_DIR)/$(MLX)
	@printf "\n✅ Bonus compilation completed: $(NAME)\e[?25h\n"

clean :
	@rm -rf $(DIR_OBJS)
	@rm -rf $(DIR_OBJS_BON)
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "✅ clean done."

fclean : clean
	@rm -f $(NAME)
	@echo "✅ fclean done."

re: fclean all

.PHONY: all bonus clean fclean re
