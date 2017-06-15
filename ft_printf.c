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

typedef struct  print_list
{
	// int 	diez;
	// int 	zero;
	// int 	minus;
	// int 	plus;
	// int 	space;
	// int 	hh;
	// int 	h;
	// int 	ll;
	// int 	l;
	// int 	j;
	// int 	z;
	// char	*fl_list;
	char	flags[11];
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
	// printf("diez=%d\n", ls->diez);
	// printf("zero=%d\n", ls->zero);
	// printf("minus=%d\n", ls->minus);
	// printf("plus=%d\n", ls->plus);
	// printf("space=%d\n", ls->space);
	// printf("hh=%d\n", ls->hh);
	// printf("h=%d\n", ls->h);
	// printf("ll=%d\n", ls->ll);
	// printf("l=%d\n", ls->l);
	// printf("j=%d\n", ls->j);
	// printf("z=%d\n", ls->z);

	printf("\ndiez=%d\n", ls->DIEZ);
	printf("zero=%d\n", ls->ZERO);
	printf("minus=%d\n", ls->MINUS);
	printf("plus=%d\n", ls->PLUS);
	printf("space=%d\n", ls->SPACE);
	printf("hh=%d\n", ls->_HH);
	printf("h=%d\n", ls->H_);
	printf("ll=%d\n", ls->_LL);
	printf("l=%d\n", ls->L_);
	printf("j=%d\n", ls->J_);
	printf("z=%d\n", ls->Z_);
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

int		ft_count(char *str, char c)
{
	int res;

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

// void	cut_a_piece(p_list *ls, char *str, int pos)
// {
// 	if (ls->start != NULL)
// 	{
// 		// ft_bzero((char *)ls, sizeof(p_list));
// 		// clear_struct(ls);
// 		ls->start = ft_strchr(str, '%');
// 			PRINT_D_MSG("start = %s\n", ls->start);
// 		// (ls->start) ? ft_putnstr(str, ls->start - str) : ft_putstr(str);
// 		ls->len += ft_putnstr(str, (ls->start) ? (ls->start - str) : ft_strlen(str));
// 		(ls->start) += (ls->start) ? 1 : 0;
// 		pos = ft_strcstr(ls->start, SKIP, 0);
// 			PRINT_D_MSG("try to find SKIP = %d\n", pos);
// 		if (pos == EOS)
// 			PRINT_D_MSG("skipped SKIPto EOF\n");
// 		(ls->body) = (pos >= 0 ? ls->start + pos : NULL);
// 			ASSERT_D(!(ls->body), "no flag or modifier found\n");
// 			ASSERT_D((ls->body), "found end at =  \"%s\"\n", (ls->body));
// 		if ((ls->body) && *(ls->body) != '%')
// 		{
// 			ls->convertor = !(ft_strchr(CONV, *(ls->body))) ? '\0' : *(ft_strchr(CONV, *(ls->body)));
// 				ASSERT_D(ls->convertor, "is_conv = %c\n", ls->convertor);
// 				ASSERT_D(!ls->convertor, "is_conv = false\n");
// 			ls->pre = ft_strsub(ls->start, 0, -(ls->start - ls->body));
// 		}
// 		else if ((ls->body) && *(ls->body) == '%')
// 		{
// 			ls->len += ft_putstr("%");
// 				PRINT_D_MSG("print_percent\n");			
// 		}
// 		else
// 		{
// 			ls->pre = ft_strsub(ls->start, 0, ft_strlen(ls->start));
// 		}
// 	}
// }

void 	conv_percent(p_list *ls)
{
	ls->len += ft_putstr("%");
}


void	make_conversion(p_list *ls)
{
	(ls->convertor == '%') ? conv_percent(ls) : 0 ;
}

void	cut_a_piece(p_list *ls, int pos, char *str)
{
	while (ls->start)
	{
		if (ls->middle < ls->end)
			ls->len = ft_putnstr(ls->middle + 1, ls->end - ls->middle);
			PRINT_D_MSG("ls->len = %zu\n", ls->len);
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
				ASSERT_D(!ls->convertor, "is_conv = false\n");
		make_conversion(ls);
		if (ls->middle != ls->end)
			ls->len = ft_putnstr()
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
