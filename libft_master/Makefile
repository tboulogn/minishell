# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryada <ryada@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/05 16:38:57 by tboulogn          #+#    #+#              #
#    Updated: 2025/03/22 16:55:26 by ryada            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_master.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
OBJ_DIR = obj/

RESET 	= \033[0m
VERT 	= \033[1;32m

SRC	=	$(SRC_DIR)/ft_strlen.c $(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_strlcat.c $(SRC_DIR)/ft_strchr.c $(SRC_DIR)/ft_strrchr.c $(SRC_DIR)/ft_strnstr.c $(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_atoi.c $(SRC_DIR)/ft_isalpha.c $(SRC_DIR)/ft_isdigit.c $(SRC_DIR)/ft_isalnum.c $(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isprint.c $(SRC_DIR)/ft_toupper.c $(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_memset.c $(SRC_DIR)/ft_bzero.c $(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c $(SRC_DIR)/ft_memchr.c $(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strlcpy.c $(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_substr.c $(SRC_DIR)/ft_strjoin.c $(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c $(SRC_DIR)/ft_itoa.c $(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c $(SRC_DIR)/ft_putchar_fd.c $(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_lstadd_back_bonus.c $(SRC_DIR)/ft_lstadd_front_bonus.c \
		$(SRC_DIR)/ft_lstclear_bonus.c $(SRC_DIR)/ft_lstdelone_bonus.c \
		$(SRC_DIR)/ft_lstiter_bonus.c $(SRC_DIR)/ft_lstlast_bonus.c $(SRC_DIR)/ft_lstmap_bonus.c \
		$(SRC_DIR)/ft_lstnew_bonus.c $(SRC_DIR)/ft_lstnew_bonus.c $(SRC_DIR)/ft_lstsize_bonus.c \
		$(SRC_DIR)/ft_putendl_fd.c $(SRC_DIR)/ft_putnbr_fd.c $(SRC_DIR)/get_next_line.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:$(SRC_DIR)/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(VERT)LIBFT_MASTER created.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/ft_printf
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -f $(NAME)
		@echo "$(VERT)All files cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re