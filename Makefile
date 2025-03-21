# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryada <ryada@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 14:30:07 by tboulogn          #+#    #+#              #
#    Updated: 2025/03/21 17:09:10 by ryada            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft_master/
INCLUDE_DIR = includes/

# SRC_FILES = 
# SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
SRC = $(SRC_DIR)main.c\
	$(SRC_DIR)free.c\
	$(SRC_DIR)tokenization.c\
	$(SRC_DIR)utils.c  \
	$(SRC_DIR)exec.c  \
	$(SRC_DIR)env_tab.c \
	$(SRC_DIR)checker.c \
	$(SRC_DIR)builtin/ft_cd.c \
	$(SRC_DIR)builtin/ft_echo.c \
	$(SRC_DIR)builtin/ft_env.c \
	$(SRC_DIR)builtin/ft_pwd.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I$(INCLUDE_DIR) -g
INCLUDES = -I/usr/include -Imlx

LIBFT = $(LIBFT_DIR)/libft_master.a

GREEN = \033[32m
RESET = \033[0m

BANNER = "$(GREEN)\n\
===================================================================\n\
███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n\
████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n\
██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n\
██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n\
██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n\
===================================================================\n\
-------------------MINISHELL BY RYADA & TBOULOGN-------------------\n\
===================================================================\n\$(RESET)"\

all: banner $(LIBFT) $(NAME)

banner :
	@echo $(BANNER)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -lhistory
	@echo "$(GREEN)✅ Compilation terminée !$(RESET)"

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

