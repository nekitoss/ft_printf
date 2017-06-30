// #define DEBUG
#include "ft_printf.h"

#define FLAGS "#0-+ "
#define MODIF "hljz"
#define SKIP "#-+0 hljz123456789."
#define CONV "idDoOuUxXsScCp%"
#define EOS -1
#define DIGITS "0123456789"
#define DIGITS_D "0123456789."
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
#define BODY ls->bod

typedef struct  print_list
{
	char	flags[12];
	char	*pre;
	char	*bod;
	char	*start;
	char	*middle;
	char	*end;
	char	*ptr_end;
	char	convertor;
	size_t	len;
	size_t	precision;
	size_t	width;
	va_list	ap;
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
	printf("bod=%s\n", BODY);
	// printf("curr_pos=%s\n", ls->curr_pos);
	printf("convertor=%c\n", ls->convertor);
	printf("len=%ld\n", ls->len);
	printf("width=%ld\n", ls->width);
	printf("precision=%ld\n\n", ls->precision);
}

int		my_err(int errnum)
{
	write(1, "Error occured in ", 17);
	ft_putnbr(errnum);
	// exit(errnum);
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

int		search_zero_flag(char *str)
{
	if (str && *str)
	{
		if (*str == '0')
			return (1);
		while (*(str + 1) != '\0')
		{
			if ((!(ft_isdigit(*str)) && *str != '.') && *(str + 1) == '0')
				return (1);
			str++;
		}
	}
	return (0);
}

void	search_flags(p_list *ls){
	int tmp;

	tmp = 0;
	DIEZ = ft_count(ls->pre, '#') ? 1 : 0;
	// ZERO = ft_count(ls->pre, '0') ? 1 : 0;
	ZERO = search_zero_flag(ls->pre);
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
	ft_bzero((char *) ls->flags, sizeof((ls->flags[0]) * 12));
	ft_strdel(&(ls->pre));
	ft_strdel(&(BODY));
	ls->precision = -1;
	ls->width = -1;
	ls->middle = NULL;
	ls->convertor = 0;
}

size_t	ft_freelist(p_list **ls)
{
	size_t len;
	
	len = (*ls)->len;
	// ft_strdel(&((*ls)->fl_list));
	ft_strdel(&((*ls)->pre));
	*ls = NULL;
	return (len);
}

void	flag_width(p_list *ls)
{
	size_t body_len;

	body_len = ft_strlen(BODY);
	if (body_len < ls->width)
	{
		tmp =;//zero or space string
		if (MINUS)
			BODY = ft_strjoin_d(&(BODY), &(tmp), 3);
		else
		{

		}
	}
	ls->len += ft_putnstr(BODY, ft_strlen(BODY));
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
	char c;

	c = (!(ls->convertor) ? *(ls->middle) : va_arg(ls->ap, int));
	BODY = ft_strnew(1);
	*(BODY) = c;
	// ls->len += ft_putchar(c);
}

void	make_conversion(p_list *ls)
{
	// (ls->convertor == 'i') ? conv_d(ls) : 0 ;
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
	(ls->convertor == 'c') ? conv_c(ls) : 0 ;
	// (ls->convertor == 'C') ? conv_c2(ls) : 0 ;
	// (ls->convertor == 'p') ? conv_p(ls) : 0 ;
	(ls->convertor == '%') ? conv_percent(ls) : 0 ;
	(ls->convertor == '\0') ? conv_c(ls) : 0 ;
}

size_t	convert_last_numb(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

		// PRINT_D_MSG("last_numb: pre = %s\n", ls->pre);
	pos = ft_strcstr_f(ls->pre, DIGITS, 1);
		// PRINT_D_MSG("digit at=%d is %c\n", pos, *(ls->pre + pos));
	tmp1 = ft_strsub(ls->pre, 0, pos + 1);
		// PRINT_D_MSG("tmp1=%s\n", tmp1);
	pos = ft_strcstr(tmp1, DIGITS, 1);
		// PRINT_D_MSG("start text at=%d\n", pos);
	tmp2 = ft_strsub(tmp1, ++pos, ft_strlen(tmp1));
		// PRINT_D_MSG("tmp2=%s\n", tmp2);
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

size_t	convert_r_dot(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

		// PRINT_D_MSG("r_dot: pre = %s\n", ls->pre);
	pos = ft_strcstr_f(ls->pre, ".", 1);
		// PRINT_D_MSG("digit/dot at=%d is %c\n", pos, *(ls->pre + pos));
	if (!ft_isdigit(*(ls->pre + pos + 1)))
		return (0);
	tmp1 = ft_strsub(ls->pre, pos + 1, ft_strlen(ls->pre));
		// PRINT_D_MSG("tmp1=%s\n", tmp1);
	pos = ft_strcstr(tmp1, DIGITS, 1);
		// PRINT_D_MSG("start text at=%d\n", pos);
	tmp2 = ft_strsub(tmp1, 0, (pos > -1) ? pos : (int)ft_strlen(tmp1));
		// PRINT_D_MSG("tmp2=%s\n", tmp2);
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

size_t	convert_l_dot(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

		// PRINT_D_MSG("l_dot: pre = %s\n", ls->pre);
	pos = ft_strcstr_f(ls->pre, ".", 1);
		// PRINT_D_MSG("dot at=%d is %c\n", pos, *(ls->pre + pos));
	if (pos == 0 || !ft_isdigit(*(ls->pre + pos - 1)))
		return (0);
	tmp1 = ft_strsub(ls->pre, 0, pos);
		// PRINT_D_MSG("tmp1=%s\n", tmp1);
	pos = ft_strcstr(tmp1, DIGITS, 1);
		// PRINT_D_MSG("start text at=%d\n", pos);
	tmp2 = ft_strsub(tmp1, ++pos, ft_strlen(tmp1));
		// PRINT_D_MSG("tmp2=%s\n", tmp2);
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

int		find_last_number(p_list *ls)
{
	int		pos;
	char	*tmp;

	pos = ft_strlen(ls->pre);
	// PRINT_D_MSG("find len = %d\n", pos);
	if (ft_isdigit(*(ls->pre + pos)) || *(ls->pre + pos) == '.')
		return (ft_strcstr(ls->pre, DIGITS_D, 1));
	tmp = ft_strsub(ls->pre, 0, ft_strcstr_f(ls->pre, DIGITS_D, 1));
	// PRINT_D_MSG("tmp = %s\n", tmp);
	pos = ft_strcstr(tmp, DIGITS_D, 1);
	// PRINT_D_MSG("pos = %d\n", pos);
	ft_strdel(&tmp);
	return (pos);
}

void	search_precision_and_width(p_list *ls, int dot, int dig, int ascii)
{
	// PRINT_D_MSG("dot=%d, dig=%d, ascii=%d\n", dot, dig, ascii);
	if (dot == EOS && dig != EOS)
	{
			// PRINT_D_MSG("no dot, searching width\n");
		ls->width = convert_last_numb(ls);
	}
	else if (dot > EOS && dig > EOS)
	{
		ls->precision = 0;
			// PRINT_D_MSG("dot is present, \n");
		if (dot < dig)
		{
			ls->precision = convert_r_dot(ls);
			if (dot < ascii && ascii < dig)
			{
					// PRINT_D_MSG("text between dot and digits, apply with and precision after dot\n")
				ls->width = convert_last_numb(ls);
			}
			else
			{
					// PRINT_D_MSG("there are numbers near dot, searching numbers around dot\n")
				ls->width = convert_l_dot(ls);
			}
		}
		else
		{
				// PRINT_D_MSG("no numbers after dot, search width before dot\n")
			ls->width = convert_l_dot(ls);
		}
	}
}

uintmax_t	ft_unsigned_size(p_list *ls, va_list *ap)
{
	uintmax_t	num;

	num = va_arg(*ap, uintmax_t);
	if (J_)
		num = (uintmax_t)num;
	else if (Z_)
		num = (size_t)num;
	else if (_LL)
		num = (unsigned long long int)num;
	else if (L_)
		num = (unsigned long int)num;
	else if (H_)
		num = (unsigned short int)num;
	else if (_HH)
		num = (unsigned char)num;
	else
		num = (unsigned int)num;
	return (num);
}

intmax_t	ft_signed_size(p_list *ls, va_list *ap)
{
	intmax_t	num;

	num = va_arg(*ap, intmax_t);
	if (J_)
		num = (intmax_t)num;
	else if (Z_)
		num = (size_t)num;
	else if (_LL)
		num = (long long int)num;
	else if (L_)
		num = (long int)num;
	else if (H_)
		num = (signed short int)num;
	else if (_HH)
		num = (signed char)num;
	else
		num = (int)num;
	return (num);
}

void	cut_a_piece(p_list *ls, int pos, char *str)
{
#ifdef DEBUG
	size_t i=1;
#endif
#ifndef DEBUG
	str = NULL;
#endif
	while (ls->start)
	{
		PRINT_D_MSG("\n\n###PART____%zu___###\n\n", i++);
		// if (ls->middle < ls->end)
		// 	ls->len += ft_putnstr(ls->middle + 1, ls->end - ls->middle);
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
		ls->pre = ft_strsub(ls->start, 0, (ls->middle - ls->start));
		ls->convertor = !(ft_strchr(CONV, *(ls->middle))) ? '\0' : *(ft_strchr(CONV, *(ls->middle)));
				ASSERT_D(ls->convertor, "is_conv = %c\n", ls->convertor);
				ASSERT_D(!ls->convertor, "%c = is_NOT_conv\n", *(ls->middle));
		make_conversion(ls);
		(!ls->end) ? (ls->end = ft_strchr(ls->start, 0)) : 0;
		if (ls->middle < ls->end)
			ls->len += ft_putnstr(ls->middle + 1, ls->end - ls->middle - 1);
		if (ls->pre)
		{
			search_flags(ls);
			ls->precision = -1;
			ls->width = -1;
			if (*(ls->pre))
				search_precision_and_width(ls, ft_strcstr_f(ls->pre, ".", 1), ft_strcstr_f(ls->pre, DIGITS, 1), find_last_number(ls));
		}			
#ifdef DEBUG
		print_struct(ls);
#endif
		if (ls->end == ls->ptr_end)
			return ;
		clear_struct(ls);
	}
}

int		ft_printf(char *str, ...)
{
	p_list	*ls;

		PRINT_D_MSG("input = %s\n", str);
	ls = (p_list *)ft_memalloc(sizeof(p_list));
	va_start(ls->ap, str);
	ls->start = str;
	ls->end = ft_strchr(str, '%');
	if (ls->end)
	{
		ls->ptr_end = ft_strchr(ls->start, 0);
		ls->len += ft_putnstr(ls->start, ls->end - ls->start);
		ls->middle = ls->end;
		cut_a_piece(ls, 0, str);
		va_end(ls->ap);
		return ((int)ft_freelist(&ls));
	}
	else
	{
		va_end(ls->ap);
		return ((int)ft_putstr(str));
	}
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
