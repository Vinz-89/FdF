NAME = fdf

CC = cc

CFLAGS = -Wall -Wextra -Werror -lm -O3
LFLAGS = -lmlx -lXext -lX11 -lm

RM = rm -rf

SRCS = main.c parsing.c draw.c color.c
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

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBDIR) fclean

re: fclean all