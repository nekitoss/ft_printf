UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
	CC = gcc
endif
ifeq ($(UNAME), Linux)
	CC = c99
endif

FLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRC = ft_printf.c\
		additional_funtions.c\
		convertor_choose_and_percent.c\
		cs_whitechar.c\
		doux.c\
		flag_search.c\
		precision_and_width.c\
		processing_width_and_precision.c

OBJ = $(SRC:.c=.o)

LIBOBJ = libft/*.o

INC = -I ./

CFLAGS = -c

LIBMAKE = make -C libft/

LIBINC = -I libft/libft.h -L./libft -lft

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIBMAKE) all
	@ar rc $(NAME) $(OBJ) $(LIBOBJ)
	@ranlib $(NAME)
	@echo  "\033[32mPrintf was added to libft, libftprintf.a created\033[0m"

%.o: %.c
	@$(CC) $(INC) $(CFLAGS) $(FLAGS) -o $@ $<

clean: libclean
	@rm -f $(OBJ) ft_printf.h.gch printf_main.o main.o
	@echo "\033[01;31mFt_printf object files deleted\033[0m"

fclean: libfclean clean
	@rm -f $(NAME) a.out
	@echo "\033[01;31mFt_printf executable files deleted\033[0m"

re: fclean all

liball:
	@$(LIBMAKE) all

libclean:
	@$(LIBMAKE) clean
libfclean:
	@$(LIBMAKE) fclean

libre:
	@$(LIBMAKE) re

main: all
	@$(CC) $(FLAGS) $(NAME) main.c
	@echo  "\033[32mLibrary and main.c compilation finished\033[0m"

mre: fclean main

maind: all
	@$(CC) $(FLAGS) -Wno-format-invalid-specifier -Wno-format -Wno-macro-redefined -Wno-implicitly-unsigned-literal $(NAME) printf_main.c ft_printf.c libftprintf.a ft_printf.h
	@echo  "\033[32mLibrary and printf_main.c compilation with additional flags finished\033[0m"

mdre: fclean maind

debugmain:
	@$(LIBMAKE) debug
	@$(CC) $(FLAGS) -g ft_printf.c main.c
	@echo  "\033[32m DEBUG compilation finished\033[0m"