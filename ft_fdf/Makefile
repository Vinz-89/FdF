# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmeessen <vmeessen@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 16:59:04 by vmeessen          #+#    #+#              #
#    Updated: 2025/04/15 16:59:04 by vmeessen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -O3
LFLAGS = -lmlx -lXext -lX11 -lm

RM = rm -rf

SRCS = main.c hud.c hud_util.c parsing/parsing.c parsing/parsing_exit.c parsing/parsing_setup.c parsing/utils.c draw/draw.c draw/draw_basic.c draw/color.c draw/color2.c draw/views.c
SRCS_ = $(addprefix srcs/, $(SRCS))

LIBDIR = Lib
LIB = lib.a

MINILIBXDIR = minilibx-linux

OBJ = $(SRCS_:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBDIR)/$(LIB) minilibx
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBDIR)/$(LIB) -L$(MINILIBXDIR) $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBDIR)/$(LIB):
	$(MAKE) -C $(LIBDIR)

minilibx:
	$(MAKE) -C minilibx-linux

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBDIR) clean
	$(MAKE) -C $(MINILIBXDIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean
	$(MAKE) -C $(MINILIBXDIR) clean

re: fclean all
