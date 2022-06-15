# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsaarine <jsaarine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 15:46:07 by jsaarine          #+#    #+#              #
#    Updated: 2022/06/14 17:07:15 by jsaarine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
S = src/
SRC = 	$Smain.c \
		$Sinit.c \
		$Sline.c \
		$Sutils.c \
		$Sfractals.c \
		$Sbounds_checks.c \
		$Spixel_put_color.c \
		$Scomplex.c \
		$Smultithread.c \
		$Shandle_it.c \
		$Shandle_keys.c \
		$Szoom.c

#H = includes/
HDR = fractol.h

OBJ = $(SRC:%.c=%.o)

LIBFT = libft/
LIBA = libft/libft.a

FRAMEWORKS = -framework OpenGL -framework AppKit

CC = clang
CFLAGS = #-Wall -Wextra -Werror
RM = /bin/rm -f

all: $(NAME)

$(NAME): $(SRC) $(OBJ) $(LIBA)
	$(CC) -o $@ -I /usr/local/include $(SRC) $(LIBA) -L /usr/local/lib/ -lmlx \
		$(FRAMEWORKS) -flto -O3

mb: $(SRC) $(OBJ) $(LIBA)
	$(CC) -o $@ -I minilibx/ $(SRC) $(LIBA) -L minilibx/ -lmlx -L /usr/X11/lib \
		-l X11 -l Xext $(FRAMEWORKS) -flto -O3

$(LIBA):
	make -C $(LIBFT)

%.o: %.c $(LIBA) $(HDR)
	CC $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all
