NAME = cub3D

CC = clang

CFLAGS = -g -Wall -Wextra -Werror

MACOS_MLX = mlxopengl

MACOS_FLAGS = -lmlx -framework OpenGL -framework AppKit

LINUX_MLX = minilibx-linux

LINUX_FLAGS = -lmlx -lm -lX11 -lXext -lbsd

SRC = cub3d \
	draw2d \
	map \
	get_next_line \
	get_next_line_utils \
	raycast \
	raycast_helper \
	draw3d \
	move \
	parse \
	elements \
	tools \
	more_tools \
	sprites \
	bitmap

FIL = $(addsuffix .c, $(addprefix files/, $(SRC)))

OBJ = $(FIL:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\n\033[0;33mCompiling..."
#	sudo apt-get install gcc make xorg libxext-dev libbsd-dev
#	$(CC) $(CFLAGS) $(FIL) -L $(LINUX_MLX) $(LINUX_FLAGS) -o $(NAME)
	$(CC) $(CFLAGS) $(FIL) -L $(MACOS_MLX) $(MACOS_FLAGS) -o $(NAME)
	@echo "\033[0m"

clean:
	@echo "\033[0;31mCleaning..."
	rm -rf $(OBJ)
	rm -f bitmap.bmp
	@echo "\033[0m"

fclean: clean
	@echo "\033[0;31mRemoving executable..."
	rm -f $(NAME)
	@echo "\033[0m"

re: fclean all