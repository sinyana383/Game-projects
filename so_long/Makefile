NAME = so_long
HEADER = so_long.h
HEADER_GNL = get_next_line/get_next_line.h
HEADER_PRINT = ft_printf/ft_printf.h
SRC = so_long \
	  ft_printf/ft_printf ft_printf/ft_printf_utils ft_printf/libft_functions\
	  mlx_init/check_and_get_size mlx_init/init\
	  frame_fun/new_frame \
	  hook_fun/key hook_fun/exit \
	  get_next_line/get_next_line get_next_line/get_next_line_utils get_next_line/get_lines get_next_line/get_lines_utils
OBJ = $(addsuffix .o, $(SRC))
FLAGS = -Werror -Wextra -Wall
GCC = cc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(GCC) $(FLAGS) $(OBJ) -L. -lmlx -framework OpenGL -framework AppKit -o $(NAME)

mlx_init/%.o : mlx_init/%.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

frame_fun/%.o : frame_fun/%.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

hook_fun/%.o : hook_fun/%.c $(HEADER)
	$(GCC) $(FLAGS) -c $< -o $@

get_next_line/%.o : get_next_line/%.c $(HEADER_GNL)
	$(GCC) $(FLAGS) -c $< -o $@

ft_printf/%.o : ft_printf/%.c $(HEADER_PRINT)
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
	