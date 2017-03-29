#define DEBUG
#include "ft_printf.h"

#define MIN(a, b) (a < b ? a : b)
#define FLAGS "#-+0 "
#define MODIF "hljz"
#define SKIP "#-+0 hljz123456789"
#define CONV "idDoOuUxXsScCp"
//#define FULL_L "#-+0hljzidDoOuUxXsScCp"



char	*ft_newstrnchar(size_t len, char c)
{
	return(((char *)ft_memset(ft_strnew(len), c, len)));
}



int		ft_printf(char *str, ...)
{
	char *tmp;
	char tmp2;
	int pos;
	va_list	ap;

	va_start(ap, str);
	pos = ft_strcstr(str, SKIP, 0);
		PRINT_D_MSG("try to find SKIP = %d\n", pos);
	tmp = (pos >= 0 ? str + pos : NULL);
		ASSERT_D(!tmp, "no flag ot modifier found\n");
		ASSERT_D(tmp, "found end at =  \"%s\"\n", tmp);
	if (tmp)
	{
		if (*tmp == '%')
			printf("print_percent\n");
		else
		{
			tmp2 = !(ft_strchr(CONV, *tmp)) ? '\0' : *(ft_strchr(CONV, *tmp));
			ASSERT_D(tmp2, "is_conv = %c\n", tmp2);
			ASSERT_D(!tmp2, "is_conv = false\n");
		}
		//if (ft_strchr(CONV, *tmp))

	}

	//vartypevar = va_arg(ap, vartype);
	va_end(ap);
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
