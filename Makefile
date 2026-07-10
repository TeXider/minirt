# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpanou-d <tpanou-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/01 21:00:05 by almighty          #+#    #+#              #
#    Updated: 2026/07/10 08:35:20 by tpanou-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt
CC = cc
CCFLAGS = -Wall -Wextra -Werror -g -O3
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
			$(DIR_SRCS)/rt_math/get_top_intersection.c\
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

SRCS_BON	:=	$(DIR_SRCS_BON)/main_bonus.c\
				$(DIR_SRCS_BON)/others/colors_bonus.c\
				$(DIR_SRCS_BON)/others/init_env_bonus.c\
				$(DIR_SRCS_BON)/others/mlx_funcs_bonus.c\
				$(DIR_SRCS_BON)/others/memory_bonus.c\
				$(DIR_SRCS_BON)/others/extend_len_bonus.c\
				$(DIR_SRCS_BON)/parsing/go_to_next_line_bonus.c\
				$(DIR_SRCS_BON)/parsing/parse_file_bonus.c\
				$(DIR_SRCS_BON)/parsing/parsing_utils_bonus.c\
				$(DIR_SRCS_BON)/parsing/init_shape_vals_bonus.c\
				$(DIR_SRCS_BON)/parsing/check_options_bonus.c\
				$(DIR_SRCS_BON)/parsing/option_utils_bonus.c\
				$(DIR_SRCS_BON)/parsing/shape_parsing_bonus.c\
				$(DIR_SRCS_BON)/parsing/singleton_parsing_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_num_bonus.c\
				$(DIR_SRCS_BON)/parsing/get_composite_bonus.c\
				$(DIR_SRCS_BON)/rt_math/get_intersection_bonus.c\
				$(DIR_SRCS_BON)/rt_math/get_top_intersection_bonus.c\
				$(DIR_SRCS_BON)/rt_math/is_in_shadow_bonus.c\
				$(DIR_SRCS_BON)/rt_math/ray_trace_aa_bonus.c\
				$(DIR_SRCS_BON)/rt_math/ray_trace_bonus.c\
				$(DIR_SRCS_BON)/rt_math/render_image_bonus.c\
				$(DIR_SRCS_BON)/rt_math/set_shape_inter_vals_bonus.c\
				$(DIR_SRCS_BON)/rt_math/shape_surf_n_bonus.c\
				$(DIR_SRCS_BON)/rt_math/shape_surf_n2_bonus.c\
				$(DIR_SRCS_BON)/rt_math/shape_color_bonus.c\
				$(DIR_SRCS_BON)/rt_math/utils_bonus.c\
				$(DIR_SRCS_BON)/rt_math/textures_bonus.c\
				$(DIR_SRCS_BON)/rt_math/vector_bonus.c\
				$(DIR_SRCS_BON)/rt_math/vector2_bonus.c\
				$(DIR_SRCS_BON)/err_handling/opt_hint_msgs_bonus.c\
				$(DIR_SRCS_BON)/err_handling/env_err_bonus.c\
				$(DIR_SRCS_BON)/err_handling/parsing_err_bonus.c\
				$(DIR_SRCS_BON)/err_handling/parsing_err2_bonus.c\
				$(DIR_SRCS_BON)/err_handling/parsing_hints_bonus.c\

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
