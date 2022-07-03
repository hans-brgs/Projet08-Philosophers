# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hbourgeo <hbourgeo@student.19.be>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/15 07:55:41 by hbourgeo          #+#    #+#              #
#    Updated: 2022/07/03 20:35:59 by hbourgeo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
OS = $(shell uname)

# Get DIR
INC_DIR =	includes/
SRC_DIR = srcs/
OBJ_DIR = obj_$(basename $(NAME))/

# MLX mac OS / LINUX
ifeq ($(OS), Linux)

else

endif

# Edit FLAGS
CC = gcc 
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -I$(INC_DIR)
CFLAGS += -pthread
DEPS = $(shell find $(INC_DIR) -type f -name "*.h")

SRCS = $(notdir $(shell find $(SRC_DIR) -type f -name "*.c"))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# Add search path
VPATH = $(INC_DIR) $(OBJ_DIR) $(LIBFT) $(shell find $(SRC_DIR) -type d)

all: $(NAME)

$(OBJ_DIR)%.o : %.c $(DEPS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) :
	@mkdir -p $(OBJ_DIR)

$(NAME) : $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
	@rm -rf $(OBJS)
	@rm -rf $(OBJ_DIR)
	@rm	-rf *.txt

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : clean fclean all re

# Print variable content
print-%: ; @echo $* = $($*)

# VALGRIND
ARG1 = 4
ARG2 = 800
ARG3 = 100
ARG4 = 100
ARG5 = 2
leak:
	@valgrind	--leak-check=full			\
				--show-leak-kinds=all		\
    			--track-origins=yes			\
    			--verbose					\
    			--trace-children=yes		\
    			--log-file=valgrind-out.txt \
    			./$(NAME) $(ARG1) $(ARG2) $(ARG3) $(ARG4) $(ARG5)\

# GIT
MSG = ""
git: fclean
	@git add .
	@git commit -am "`date +'%m-%d-%Y %H:%M:%S'` | $(MSG)"
	@git push
	