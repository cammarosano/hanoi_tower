SRC = src/hanoi_tower.c src/utils.c
OBJ = $(SRC:.c=.o)

NAME = hanoi_tower
LIBFT = libft/libft.a
LIB = libft/
INCLUDES = includes/

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJ)
		gcc $(OBJ) $(LIBFT) -o $@

$(LIBFT):
		make bonus clean -C libft

%.o:	%.c
		gcc -c $< -I $(INCLUDES) -o $@

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME) $(LIBFT)

re:		fclean all
