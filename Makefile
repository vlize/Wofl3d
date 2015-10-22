#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlize <vlize@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/31 09:31:19 by vlize             #+#    #+#              #
#    Updated: 2015/03/31 09:31:20 by vlize            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = wolf3d

SRC =	wolf3d.c wolf3d_exit.c wolf3d_error.c wolf3d_data.c wolf3d_hook.c \
		wolf3d_check.c wolf3d_init.c wolf3d_load_map.c wolf3d_key_event.c \
		wolf3d_make.c wolf3d_draw.c wolf3d_collision.c wolf3d_color.c \
		wolf3d_cast.c

OBJ = $(SRC:.c=.o)

LIB =	-L ./libft/ -lft \
		-framework OpenGL -framework AppKit \
		-lmlx -lm -lpthread -D_REENTRANT

INC =	-I . -I libft/includes/ \
		-I /System/Library/Frameworks/Tk.framework/Headers/ \
		-I /usr/local/include/

CMP = gcc -Wall -Wextra -Werror

all : $(NAME)

$(NAME) :
		@ make -C libft/
		@ $(CMP) $(INC) -c $(SRC)
		@ $(CMP) -o $(NAME) $(OBJ) $(LIB)
		@ echo "\x1b[32m>make all : \tOK\x1b[0m"

clean :
		@ make -C libft/ clean
		@ rm -rf $(OBJ)
		@ echo "\x1b[32m>make clean :\tOK\x1b[0m"

fclean : clean
		@ make -s -C libft/ fclean
		@ rm -rf $(NAME)
		@ echo "\x1b[32m>make fclean :\tOK\x1b[0m"

re : fclean all
	@ echo "\x1b[32m>make re :  \tOK\x1b[0m"
