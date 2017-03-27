#include "ft_printf.h"

int		ft_printf(char *str, ...)
{
	va_list	ap;

	va_start(ap, str);

	printf("try to find %%%%  =  \"%s\"\n", ft_strstr(str, "%%"));

	//vartypevar = va_arg(ap, vartype);
	va_end(ap);
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
