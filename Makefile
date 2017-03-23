NAME = libftprintf.a

SRC = format.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ft_printf.h

CFLAGS = -c -Wall -Wextra -Werror

LIBMAKE = make -C libft/

LIBINC = -I libft/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	$(LIBMAKE) all
	ar rc $(NAME) $(OBJ) $(LIBOBJ)
	ranlib $(NAME)

%.o: %.c
	gcc $(INC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

liball:
	$(LIBMAKE) all

libclean:
	$(LIBMAKE) clean

libre:
	$(LIBMAKE) re 