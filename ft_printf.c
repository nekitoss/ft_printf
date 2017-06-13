#define DEBUG
#include "ft_printf.h"

#define FLAGS "#0-+ "
#define MODIF "hljz"
#define SKIP "#-+0 hljz123456789."
#define CONV "idDoOuUxXsScCp"
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
	char	*fl_list;
	char	flags[11];
	char	*pre;
	char	*body;
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

	printf("diez=%d\n", ls->DIEZ);
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
	printf("fl_list=%s\n", ls->fl_list);
	printf("pre=%s\n", ls->pre);
	printf("body=%s\n", ls->body);
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

void	ft_freelist(p_list **ls)
{
	ft_strdel(&((*ls)->fl_list));
	ft_strdel(&((*ls)->pre));
	*ls = NULL;
}

int		ft_printf(char *str, ...)
{
	// char	*(plist->body);
	char	convertor;
	int		pos;
	p_list	*plist;

	PRINT_D_MSG("input = %s\n", str);
	plist = ft_memalloc(sizeof(p_list));
	plist->fl_list = ft_strjoin(FLAGS, MODIF);
	//plist = (p_list *)malloc(sizeof(p_list));
	// plist->h = 100;
	// print_struct(plist);
	// ft_bzero(plist, sizeof(p_list));
	// ft_memset(plist, 0,sizeof(p_list));
	va_list	ap;
	va_start(ap, str);
	pos = ft_strcstr(str, SKIP, 0);
		PRINT_D_MSG("try to find SKIP = %d\n", pos);
	(plist->body) = (pos >= 0 ? str + pos : NULL);
		ASSERT_D(!(plist->body), "no flag or modifier found\n");
		ASSERT_D((plist->body), "found end at =  \"%s\"\n", (plist->body));
	if ((plist->body))
	{
		if (*(plist->body) == '%')
		{
				PRINT_D_MSG("print_percent\n");
		}
		else
		{
			convertor = !(ft_strchr(CONV, *(plist->body))) ? '\0' : *(ft_strchr(CONV, *(plist->body)));
				ASSERT_D(convertor, "is_conv = %c\n", convertor);
				ASSERT_D(!convertor, "is_conv = false\n");
			plist->pre = ft_strsub(str, 0, -(str - plist->body));
		}
		//if (ft_strchr(CONV, *tmp))

	}
	// print_struct(plist);
	search_flags(plist);
	print_struct(plist);
	//vartypevar = va_arg(ap, vartype);
	va_end(ap);
	ft_freelist(&plist);
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
