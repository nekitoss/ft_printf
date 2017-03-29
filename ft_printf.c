#include "ft_printf.h"

#define MIN(a, b) (a < b ? a : b)
#define FLAGS "#-+0"
#define MODIF "hljz"
#define FL_MOD "#-+0hljz"
#define CONV "idDoOuUxXsScCp"
#define FULL_L "#-+0hljzidDoOuUxXsScCp"

char	*ft_newstrnchar(size_t len, char c)
{
	return(((char *)ft_memset(ft_strnew(len), c, len)));
}



int		ft_printf(char *str, ...)
{
	char *tmp;
	int pos;
	va_list	ap;

	va_start(ap, str);
	pos = ft_strcstr(str, FL_MOD, 0);
	printf("i=%d\n", pos);
	// if (pos > 0)
	// 	tmp = str + pos;
	// else
	// 	tmp = str + ft_strcstr(str, FL_MOD, 0);
	tmp = (pos > 0 ? str + pos : NULL);
	printf("try to find end =  \"%s\"\n", tmp);
	// printf("%s\n", ft_newstrnchar(5, '*'));
	//vartypevar = va_arg(ap, vartype);
	va_end(ap);
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
