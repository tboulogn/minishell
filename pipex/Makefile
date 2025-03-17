# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryada <ryada@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 12:12:41 by ryada             #+#    #+#              #
#    Updated: 2025/03/15 11:42:33 by ryada            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
NAME = pipex

# Compiler and Flags
CC = gcc
CFLAGS = -Werror -Wall -Wextra

# Remove Command
RM = rm -rf

# Directories
SRC_DIR = srcs
LIBFT_DIR = libft
INCLUDES = -Iincludes
BONUS_DIR = srcs_bonus
GNL_DIR = gnl

# Source Files (Mandatory)
SRCS =  $(SRC_DIR)/getenv.c \
		$(SRC_DIR)/pipex.c \
		$(SRC_DIR)/utils.c

# Source Files (Bonus)
SRCS_BONUS = $(BONUS_DIR)/child_bonus.c \
				$(BONUS_DIR)/edata_bonus.c \
				$(BONUS_DIR)/error_bonus.c \
				$(BONUS_DIR)/exec_bonus.c \
				$(BONUS_DIR)/getenv_bonus.c \
				$(BONUS_DIR)/heredoc_bonus.c \
				$(BONUS_DIR)/pipex_bonus.c \
				$(BONUS_DIR)/process_bonus.c \
				$(BONUS_DIR)/utils_bonus.c \
				$(GNL_DIR)/get_next_line.c \
				$(GNL_DIR)/get_next_line_utils.c

# Object Files (Mandatory)
OBJS = $(SRCS:.c=.o)

# Object Files (Bonus)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default Rule - Compile Pipex (Mandatory)
all: $(LIBFT) $(NAME)

# Compile Pipex (Mandatory)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "✅ Pipex (Mandatory) compiled successfully!"

# Compile Pipex (Bonus) - Overrides the Mandatory Version
bonus: $(LIBFT) $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "🚀 Pipex (Bonus) compiled successfully!"

# Compile Object Files (Mandatory)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Object Files (Bonus)
$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Libft
$(LIBFT):
	@make -C $(LIBFT_DIR) --silent

# Clean Object Files
clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C $(LIBFT_DIR) --silent
	@echo "🧹 Cleaned object files!"

# Full Clean (Remove Everything)
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) --silent
	@echo "🗑️  Removed all compiled files!"

# Recompile Everything
re: fclean all

# Phony Rules
.PHONY: all clean fclean re bonus
