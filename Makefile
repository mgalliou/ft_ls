# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/28 13:13:07 by mgalliou          #+#    #+#              #
#    Updated: 2017/07/27 16:44:40 by mgalliou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include includes/gmsl

NAME		=	ft_ls
RM			= 	rm -rf
CC			=	gcc
FLAGS		=	-c -Wall -Wextra -Werror
CPPFLAGS	=	$(foreach dir, $(INC_DIR), -I$(dir))
RM			= 	rm -rf
LDFLAGS		=	-L$(LIB_DIR)
LDLIBS		=	-lft
LIB_DIR		= 	./$(LIB_NAME)
SRC_DIR		=	./srcs
OBJ_DIR		=	./objs
INC_DIR		=	\
				./includes \
				./$(LIB_NAME)/includes
LIB_NAME	=	libft
SRC_NAME	=	\
				main.c \
				get_options.c \
				get_files.c \
				get_timestring.c \
				get_timecmpf.c \
				get_cmpf.c \
				extract_files.c \
				create_path.c \
				filenew.c \
				filedel.c \
				print_files.c \
				print_filename.c \
				get_paddings.c \
				print_long_format.c \
				print_incolumn.c \
				print_xattr.c \
				print_acl.c \
				print_mode.c \
				isrelative.c
OBJ_NAME	=	$(SRC_NAME:.c=.o)
SRC			=	$(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ			=	$(addprefix $(OBJ_DIR)/,$(OBJ_NAME))
CBLUE		=	\e[1\e[38;2;0;90;160m
CRED		=	\e[1\e[38;2;160;0;90m
HEAD		=	[ $(NAME) ]
CHEAD		=	"$(CRED)$(HEAD)\e[m"
COL			=	$$(tput cols)
PAD			=	$$(($(COL) - $(call strlen,$(HEAD)) - 1))

define print_info
    @printf "\e%b %*s\n" $(CHEAD) $(PAD) $(1)
endef

all : $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_DIR)
	$(call print_info,"all object created")
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@ #-fsanitize=address
	$(call print_info,"binary created")

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CPPFLAGS) $(FLAG) -c $< -o $@
	$(call print_info,"$< created")

clean :
	@$(RM) $(OBJ_DIR)
	$(call print_info,"all object deleted")
	@make clean -C $(LIB_DIR)


fclean : clean
	@$(RM) $(NAME)
	$(call print_info,"binary deleted")
	@make fclean -C $(LIB_DIR)

re : fclean all

norminette :
	$@ $(SRC_DIR) $(INC_DIR)
	make $@ -C $(LIB_DIR)

.PHONY: all clean fclean re
