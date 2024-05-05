# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
CYAN = \033[1;36m
MAGENTA = \033[0;35m
ORANGE = \033[38;5;216m
NC = \033[0m

# Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I/usr/include -I./minilibx-linux -O3
LDFLAGS = -L./minilibx-linux -L/usr/lib
LDLIBS = -lmlx_Linux -lXext -lX11 -lm -lz

# Project
NAME = cub3d
HEADER_DIR = ./includes/
OBJ_DIR = objects/
SRC_DIR = functions/
EXIT_DIR = functions/exit/
INIT_DIR = functions/init/
TOOL_DIR = functions/tools/
SRC = 	$(SRC_DIR)main.c \
		$(INIT_DIR)check_arg.c \
		$(INIT_DIR)init.c \
		$(EXIT_DIR)exit.c \
		$(TOOL_DIR)free_tab.c \
		$(TOOL_DIR)test.c \

OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC))

#Libft
LIBFT_A = ./libft/libft.a

all: $(NAME)

$(LIBFT_A):
	@make -s -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@
	@echo "$(CYAN)Compiled $<$(NC)"

$(NAME): $(OBJS) $(LIBFT_A)
	@cd minilibx-linux && $(MAKE)
	@$(CC) $(CFLAGS) $(LDFLAGS) -I $(HEADER_DIR) $(OBJS) $(LIBFT_A) $(LDLIBS) -o $@ && \
		echo "${MAGENTA}$@ ${GREEN}Compiled successfully${NC}" || \
		echo "${RED}Failed to compile ${CYAN}$@${NC}"

run : ${NAME}
	@./${NAME} map.cub

valgrind : ${NAME}
	@ valgrind --leak-check=full --show-leak-kinds=all ./${NAME} map.cub

runv : ${NAME}
	@ valgrind --leak-check=full --trace-children=yes --track-fds=yes ./${NAME} map.cub

env : ${NAME}
	@env -i ./${NAME}

envv : ${NAME}
	@env -i valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./${NAME}

clean:
	@rm -rf $(OBJ_DIR)
	@make -s clean -C ./libft
	@echo "${YELLOW}Finished cleaning${NC}"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT_A)
	@echo "${YELLOW}Complete cleaning completed${NC}"

re: fclean all

.PHONY: all clean fclean re
