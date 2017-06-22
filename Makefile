NAME = libftprintf.a

SRC = ft_printf.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ft_printf.h

CFLAGS = -c -Wall -Wextra -Werror

LIBMAKE = make -C libft/

LIBINC = -I libft/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBMAKE) all
	@ar rc $(NAME) $(OBJ) $(LIBOBJ)
	@ranlib $(NAME)
	@echo  "\033[32mPrintf was added to libft, libftprintf.a created\033[0m"

%.o: %.c
	@gcc $(INC) $(CFLAGS) -o $@ $<

clean:
	@rm -f $(OBJ) ft_printf.h.gch printf_main.o main.o
	@echo "\033[01;31mFt_printf object files deleted\033[0m"

fclean: clean
	@rm -f $(NAME) a.out
	@echo "\033[01;31mFt_printf executable files deleted\033[0m"

re: fclean all

liball:
	@$(LIBMAKE) all

libclean:
	@$(LIBMAKE) clean

libre:
	@$(LIBMAKE) re

main: all
	@gcc -Wall -Wextra -Werror $(NAME) main.c
	@echo  "\033[32mLibrary and main.c compilation finished\033[0m"

mre: fclean main

maind: all
	@gcc -Wall -Wextra -Werror -Wno-format-invalid-specifier -Wno-format -Wno-macro-redefined -Wno-implicitly-unsigned-literal $(NAME) printf_main.c
	@echo  "\033[32mLibrary and printf_main.c compilation with additional flags finished\033[0m"

mdre: fclean maind