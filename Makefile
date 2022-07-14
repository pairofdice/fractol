# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 15:46:07 by jsaarine          #+#    #+#              #
#    Updated: 2022/07/14 14:39:24 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
S = src/
SRC = 	$Smain.c \
		$Sinit.c \
		$Sfractals.c \
		$Spixel_put_color.c \
		$Scomplex.c \
		$Smultithread.c \
		$Shandle_keys.c \
		$Szoom.c \
		$Sutils.c \
		$Sscreenloop.c \
		$Smouse_events.c

HDR = fractol.h
OBJ = $(SRC:%.c=%.o)

FRAMEWORKS = -framework OpenGL -framework AppKit

CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(SRC) $(OBJ)
	$(CC) -o $@ -I /usr/local/include $(SRC) -L /usr/local/lib/ -lmlx \
		$(FRAMEWORKS) -flto -O3 $(CFLAGS)

mb: $(SRC) $(OBJ) $(LIBA)
	$(CC) -o $@ -I minilibx/ $(SRC) $(LIBA) -L minilibx/ \
	-lmlx -L /usr/X11/lib -l X11 -l Xext $(FRAMEWORKS) -flto -O3

%.o: %.c $(HDR)
	CC $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
