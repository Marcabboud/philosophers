NAME	= philo

SRC_DIR	= src
INC_DIR	= include
OBJ_DIR	= obj

SRC		= $(wildcard $(SRC_DIR)/*.c) main.c
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I $(INC_DIR) -pthread

GREEN	= \033[0;32m
BLUE	= \033[0;34m
YELLOW	= \033[0;33m
WHITE_BOLD	= \033[1;37m
NC		= \033[0m

all: $(NAME)
	@echo "$(WHITE_BOLD)[OK] Compilation philo done$(NC)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR)

$(NAME): $(OBJ) | $(OBJ_DIR)
	@echo "\n$(GREEN)[OK] Creating executable $(NAME)$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "\r\033[K$(BLUE)Compiling $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Removing object files$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(YELLOW)Removing executable $(NAME)$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re