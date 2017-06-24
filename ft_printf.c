#define DEBUG
#include "ft_printf.h"

#define FLAGS "#0-+ "
#define MODIF "hljz"
#define SKIP "#-+0 hljz123456789."
#define CONV "idDoOuUxXsScCp%"
#define EOS -1
#define DIGITS "0123456789"
#define DIGITS "0123456789"
#define DEL &(ls->del_text)
#define TEMP &(ls->tmp_text)
//#define FULL_L "#-+0hljzidDoOuUxXsScCp"

#define DIEZ ls->flags[0]
#define ZERO ls->flags[1]
#define MINUS ls->flags[2]
#define PLUS ls->flags[3]
#define SPACE ls->flags[4]
#define _HH ls->flags[5]
#define H_ ls->flags[6]
#define _LL ls->flags[7]
#define L_ ls->flags[8]
#define J_ ls->flags[9]
#define Z_ ls->flags[10]
#define DOT ls->flags[11]

typedef struct  print_list
{
	char	flags[12];
	char	*pre;
	char	*body;
	// char	*curr_pos;
	char	*start;
	char	*middle;
	char	*end;
	char	convertor;
	size_t	len;
	size_t	precision;
	size_t	width;
	char	*tmp_text;
	char	*del_text;
}               p_list;

void	print_struct(p_list *ls)
{
	printf("\ndiez=%d\n", DIEZ);
	printf("zero=%d\n", ZERO);
	printf("minus=%d\n", MINUS);
	printf("plus=%d\n", PLUS);
	printf("space=%d\n", SPACE);
	printf("hh=%d\n", _HH);
	printf("h=%d\n", H_);
	printf("ll=%d\n", _LL);
	printf("l=%d\n", L_);
	printf("j=%d\n", J_);
	printf("z=%d\n", Z_);
	printf("dots=%d\n", DOT);
	// printf("fl_list=%s\n", ls->fl_list);
	printf("pre=%s\n", ls->pre);
	printf("body=%s\n", ls->body);
	// printf("curr_pos=%s\n", ls->curr_pos);
	printf("convertor=%c\n", ls->convertor);
	printf("len=%ld\n", ls->len);
	printf("precision=%ld\n", ls->precision);
	printf("width=%ld\n\n", ls->width);
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
	DIEZ = ft_count(ls->pre, '#') ? 1 : 0;
	// ZERO = ft_count(ls->pre, '0') ? 1 : 0;
	MINUS = ft_count(ls->pre, '-') ? 1 : 0;
	PLUS = ft_count(ls->pre, '+') ? 1 : 0;
	SPACE = ft_count(ls->pre, ' ') ? 1 : 0;
	tmp = ft_count(ls->pre, 'h');
	_HH = tmp > 1 ? (tmp % 2) ^ 1 << 0 : 0;
	H_ = tmp % 2;
	tmp = ft_count(ls->pre, 'l');
	_LL = tmp > 1 ? (tmp % 2) ^ 1 << 0 : 0;
	L_ = tmp % 2;
	J_ = ft_count(ls->pre, 'j') ? 1 : 0;
	Z_ = ft_count(ls->pre, 'z') ? 1 : 0;
	DOT = ft_count(ls->pre, '.') ? 1 : 0;
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
/*
12z.zzs
12z01.22zzs
12z01.22zzz44zzz5s
0zz.zzs
zz.22zzs
0zz11.22zzs
zz0.22zzs
zz01.22zzs
zz01.zzs
zz11.22zzs
*/
void	search_precision_and_width(p_list *ls)
{
	int start;
	int end;

	start = 0;
	end = 0;
	if (DOT)
	{
			PRINT_D_MSG("pre = %s\n", ls->pre);
		end = ft_strcstr_f(ls->pre, DIGITS, 1);
			PRINT_D_MSG("digit at=%d\n", end);
		if (end > -1 && *(ls->pre + end + 1) == '.')
		{
				PRINT_D_MSG("this is width with 0 precision\n");
			ls->del_text = ft_strsub(ls->pre, 0, end + 1);
				PRINT_D_MSG("cut1=%s\n", ls->del_text);
			start = ft_strcstr(ls->del_text, DIGITS, 1);
				PRINT_D_MSG("start text at=%d\n", start);
			ls->tmp_text = ft_strsub(ls->del_text, ++start, ft_strlen(ls->del_text));
			ft_strdel(DEL);
				PRINT_D_MSG("cut2=%s\n", ls->tmp_text);
			// ZERO = (*(ls->tmp_text) == '0') ? 1 : 0;
			ls->width = ft_atoi(ls->tmp_text);
			ls->precision = 0;
			ft_strdel(TEMP);
		}
		else if (end > -1)
		{
				PRINT_D_MSG("this is width\n");
			ls->del_text = ft_strsub(ls->pre, 0, end + 1);
				PRINT_D_MSG("cut1=%s\n", ls->del_text);
			start = ft_strcstr(ls->del_text, DIGITS, 1);
				PRINT_D_MSG("start text at=%d\n", start);
			ls->tmp_text = ft_strsub(ls->del_text, ++start, ft_strlen(ls->del_text));
				PRINT_D_MSG("cut2=%s\n", ls->tmp_text);
			if (start != EOS  && *(ls->pre + start) == '.')
				ls->precision = ft_atoi(ls->tmp_text);
			else
				ls->width = ft_atoi(ls->tmp_text);
			ft_strdel(TEMP);
				ls->tmp_text = ft_strsub(ls->del_text, 0, ++start);
			ft_strdel(DEL);
				PRINT_D_MSG("cut3=%s\n", ls->tmp_text);
		}
		else
		{
				PRINT_D_MSG("no_numbers, but dot is present\n");
			ls->precision = 0;
			ls->width = 0;
		}
	}

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
	// struct_set_functions(ls);
	ls->start = str;
	ls->end = ft_strchr(str, '%');
	if (ls->end)
	{
		ls->len += ft_putnstr(ls->start, ls->end - ls->start);
		ls->middle = ls->end;
		cut_a_piece(ls, 0, str);
		if (ls->pre)
		{
			search_flags(ls);
			search_precision_and_width(ls);
		}
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
