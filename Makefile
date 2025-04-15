# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboulogn <tboulogn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/17 14:30:07 by tboulogn          #+#    #+#              #
#    Updated: 2025/04/14 13:48:21 by tboulogn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

NAME = minishell

SRC_DIR = src/
OBJ_DIR = obj/
LIBFT_DIR = libft_master/
INCLUDE_DIR = includes/

SRC = $(SRC_DIR)builtin/ft_cd.c \
	$(SRC_DIR)builtin/ft_echo.c \
	$(SRC_DIR)builtin/ft_env.c \
	$(SRC_DIR)builtin/ft_exit.c \
	$(SRC_DIR)builtin/ft_pwd.c \
	$(SRC_DIR)builtin/ft_export.c \
	$(SRC_DIR)builtin/ft_unset.c \
	$(SRC_DIR)env/env_list.c \
	$(SRC_DIR)execution/exec_error.c \
	$(SRC_DIR)execution/exec_helper.c \
	$(SRC_DIR)execution/exec_path.c \
	$(SRC_DIR)execution/exec.c \
	$(SRC_DIR)free/free.c \
	$(SRC_DIR)parsing/parsing_checker.c \
	$(SRC_DIR)parsing/parsing_helper_1.c \
	$(SRC_DIR)parsing/parsing_helper_2.c \
	$(SRC_DIR)parsing/parsing_quotes_1.c \
	$(SRC_DIR)parsing/parsing_quotes_2.c \
	$(SRC_DIR)parsing/parsing_redir_pipe.c \
	$(SRC_DIR)parsing/parsing1.c \
	$(SRC_DIR)parsing/parsing2.c \
	$(SRC_DIR)pipe/pipe_helper_1.c \
	$(SRC_DIR)pipe/pipe_helper_2.c \
	$(SRC_DIR)pipe/pipe_here_doc.c \
	$(SRC_DIR)pipe/pipe_process.c \
	$(SRC_DIR)pipe/pipe.c \
	$(SRC_DIR)signals/signals.c \
	$(SRC_DIR)utils/utils.c \
	$(SRC_DIR)utils/utils_2.c \
	$(SRC_DIR)utils/utils_3.c \
	$(SRC_DIR)main.c \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
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
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline -lhistory
	@echo "$(GREEN)✅ Compilation terminée !$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

