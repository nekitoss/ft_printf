#define DEBUG
#include "ft_printf.h"

#define FLAGS "#0-+ "
#define MODIF "hljz"
#define SKIP "#-+0 hljz123456789."
#define CONV "idDoOuUxXsScCp%"
#define EOS -1
//#define FULL_L "#-+0hljzidDoOuUxXsScCp"

#define DIEZ flags[0]
#define ZERO flags[1]
#define MINUS flags[2]
#define PLUS flags[3]
#define SPACE flags[4]
#define _HH flags[5]
#define H_ flags[6]
#define _LL flags[7]
#define L_ flags[8]
#define J_ flags[9]
#define Z_ flags[10]
#define DOT flags[11]

typedef struct  print_list
{
	size_t	flags[12];
	char	*pre;
	char	*body;
	// char	*curr_pos;
	char	*start;
	char	*middle;
	char	*end;
	char	convertor;
	size_t	len;
}               p_list;

void	print_struct(p_list *ls)
{
	printf("\ndiez=%zu\n", ls->DIEZ);
	printf("zero=%zu\n", ls->ZERO);
	printf("minus=%zu\n", ls->MINUS);
	printf("plus=%zu\n", ls->PLUS);
	printf("space=%zu\n", ls->SPACE);
	printf("hh=%zu\n", ls->_HH);
	printf("h=%zu\n", ls->H_);
	printf("ll=%zu\n", ls->_LL);
	printf("l=%zu\n", ls->L_);
	printf("j=%zu\n", ls->J_);
	printf("z=%zu\n", ls->Z_);
	printf("dots=%zu\n", ls->DOT);
	// printf("fl_list=%s\n", ls->fl_list);
	printf("pre=%s\n", ls->pre);
	printf("body=%s\n", ls->body);
	// printf("curr_pos=%s\n", ls->curr_pos);
	printf("convertor=%c\n", ls->convertor);
	printf("len=%ld\n\n", ls->len);
}

int		err(int errnum)
{
	write(1, "Error occured in ", 17);
	ft_putnbr(errnum);
	exit(errnum);
	// exit(-1);
	return (0);
}

size_t		ft_count(char *str, char c)
{
	size_t res;

	res = 0;
	while (*str != '\0')
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}

void	search_flags(p_list *ls){
	int tmp;

	tmp = 0;
	ls->DIEZ = ft_count(ls->pre, '#');
	ls->ZERO = ft_count(ls->pre, '0');
	ls->MINUS = ft_count(ls->pre, '-');
	ls->PLUS = ft_count(ls->pre, '+');
	ls->SPACE = ft_count(ls->pre, ' ');
	tmp = ft_count(ls->pre, 'h');
	ls->_HH = tmp > 1 ? (tmp % 2) ^ 1 << 0 : 0;
	ls->H_ = tmp % 2;
	tmp = ft_count(ls->pre, 'l');
	ls->_LL = tmp > 1 ? (tmp % 2) ^ 1 << 0 : 0;
	ls->L_ = tmp % 2;
	ls->J_ = ft_count(ls->pre, 'j');
	ls->Z_ = ft_count(ls->pre, 'z');
	ls->DOT = ft_count(ls->pre, '.');
}

char	*ft_newstrnchar(size_t len, char c)
{
	return(((char *)ft_memset(ft_strnew(len), c, len)));
}

void	clear_struct(p_list *ls)
{
	// ls->flags[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	ft_bzero((char *)ls, sizeof(ls->flags));
}

void	ft_freelist(p_list **ls)
{
	// ft_strdel(&((*ls)->fl_list));
	ft_strdel(&((*ls)->pre));
	*ls = NULL;
}

void 	conv_percent(p_list *ls)
{
	ls->len += ft_putstr("%");
}

void	conv_d(p_list *ls)
{
	printf("%p", ls);
}

void	conv_c(p_list *ls)
{
	printf("let's convert that ***t to char = %p\n", ls);
}


void	make_conversion(p_list *ls)
{
	(ls->convertor == 'i') ? conv_d(ls) : 0 ;
	// (ls->convertor == 'd') ? conv_d(ls) : 0 ;
	// (ls->convertor == 'D') ? conv_d2(ls) : 0 ;
	// (ls->convertor == 'o') ? conv_o(ls) : 0 ;
	// (ls->convertor == 'O') ? conv_o2(ls) : 0 ;
	// (ls->convertor == 'u') ? conv_u(ls) : 0 ;
	// (ls->convertor == 'U') ? conv_u2(ls) : 0 ;
	// (ls->convertor == 'x') ? conv_x(ls) : 0 ;
	// (ls->convertor == 'X') ? conv_x2(ls) : 0 ;
	// (ls->convertor == 's') ? conv_s(ls) : 0 ;
	// (ls->convertor == 'S') ? conv_s2(ls) : 0 ;
	// (ls->convertor == 'c') ? conv_c(ls) : 0 ;
	// (ls->convertor == 'C') ? conv_c2(ls) : 0 ;
	// (ls->convertor == 'p') ? conv_p(ls) : 0 ;
	(ls->convertor == '%') ? conv_percent(ls) : 0 ;
	(ls->convertor == '\0') ? conv_c(ls) : 0 ;
}

void	cut_a_piece(p_list *ls, int pos, char *str)
{
	while (ls->start)
	{
		if (ls->middle < ls->end)
			ls->len += ft_putnstr(ls->middle + 1, ls->end - ls->middle);
			// PRINT_D_MSG("ls->len = %zu\n", ls->len);
		if (!(ls->start[1]) && *(ls->start) == '%')
			break ;
		ls->start = ls->end + 1;
		pos = ft_strcstr(ls->start, SKIP, 0);
			PRINT_D_MSG("pos=%d\n", pos);
		ls->middle = ls->start + ((pos > 0) ? pos : 0);
		ls->end = ft_strchr(ls->start, '%');
			PRINT_D_MSG("ls->start =pos_%03ld=%s\n", -(str - ls->start), ls->start);
			PRINT_D_MSG("ls->middle=pos_%03ld=%s\n", -(str - ls->middle), ls->middle);
			PRINT_D_MSG("ls->end   =pos_%03ld=%s\n", -(str - ls->end), ls->end);
		if (!ls->end)
			return ;
		ls->pre = ft_strsub(ls->start, 0, (ls->middle - ls->start));
		ls->convertor = !(ft_strchr(CONV, *(ls->middle))) ? '\0' : *(ft_strchr(CONV, *(ls->middle)));
				ASSERT_D(ls->convertor, "is_conv = %c\n", ls->convertor);
				ASSERT_D(!ls->convertor, "%c = is_NOT_conv\n", *(ls->middle));
		make_conversion(ls);
		if (ls->middle != ls->end)
			ls->len += ft_putnstr(ls->middle + (ls->convertor ? 1 : 0), ls->end - ls->middle - (ls->convertor ? 1 : 0));
		break ;


	}
}

int		ft_printf(char *str, ...)
{
	
	p_list	*ls;
	PRINT_D_MSG("input = %s\n", str);
	ls = (p_list *)ft_memalloc(sizeof(p_list));
	// ls->fl_list = ft_strjoin(FLAGS, MODIF);
	// print_struct(ls);
	va_list	ap;
	va_start(ap, str);
	struct_set_functions(ls);
	ls->start = str;
	ls->end = ft_strchr(str, '%');
	if (ls->end)
	{
		ls->len += ft_putnstr(ls->start, ls->end - ls->start);
		ls->middle = ls->end;
		cut_a_piece(ls, 0, str);
		if (ls->pre)
			search_flags(ls);
		print_struct(ls);
		//vartypevar = va_arg(ap, vartype);
		va_end(ap);
		ft_freelist(&ls);
	}
	else
		return ((int)ft_putstr(str));

	return (0);
	//return(number_of_sym_printed) or -1 if error
}
