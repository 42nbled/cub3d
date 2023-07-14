NAME = cub3d

SRC_DIR = srcs
OBJ_DIR = objs

SRCS = $(addprefix $(SRC_DIR)/, main.c \
		print.c \
		get_dist.c \
		raycasting.c \
		print_screen.c \
		print_screen_ns.c \
		print_screen_ew.c \
		loop.c \
		loop_2.c \
		data_init.c \
		ft_close.c \
		hook.c \
		parsing/parsing.c \
		parsing/parsing_1.c \
		parsing/parsing_2.c \
		parsing/parsing_3.c \
		parsing/condition_get.c \
		utils/ft_atoi.c \
		utils/ft_is_number.c \
		utils/ft_strchr.c \
		utils/ft_strncmp.c \
		utils/ft_split.c \
		utils/get_next_line_utils.c \
		utils/get_next_line.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Including MinilibX
MLX_DIR = minilibx-linux
MLX_MAKE = Makefile
MLX_PATH = $(MLX_DIR)/libmlx.a

# Compiling options
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -I $(MLX_DIR) -I include -MMD -MP
MFLAGS = -L $(MLX_DIR) -lmlx -lm -lX11 -lXext -lpthread

$(NAME): $(OBJS) $(MLX_PATH)
	@echo "\033[0;34mCompiling $(NAME)...\033[0m"
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(MFLAGS)
	@echo "\033[0;32mCompilation done.\033[0m"

$(MLX_PATH):
	@echo "\033[0;34mCompiling MinilibX...\033[0m"
	make -C $(MLX_DIR)
	@echo "\033[0;32mCompilation done.\033[0m"

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;34mCleaning objects...\033[0m"
	make clean -C $(MLX_DIR)
	rm -rf $(OBJ_DIR)
	@echo "\033[0;32mCleaning done.\033[0m"

fclean: clean
	@echo "\033[0;34mCleaning executable...\033[0m"
	rm -f $(NAME)
	@echo "\033[0;32mCleaning done.\033[0m"

re: fclean all

-include $(OBJS:.o=.d)
.PHONY: all clean fclean re
