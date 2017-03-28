#include "ft_printf.h"

char	*ft_newstrnchar(size_t len, char c)
{
	return(((char *)ft_memset(ft_strnew(len), c, len)));
}

int		ft_printf(char *str, ...)
{
	va_list	ap;

	va_start(ap, str);

	// printf("try to find %%%%  =  \"%s\"\n", ft_strstr(str, "%%"));
	printf("%s\n", ft_newstrnchar(5, '*'));
	//vartypevar = va_arg(ap, vartype);
	va_end(ap);
	return (0);
	//return(number_of_sym_printed) or -1 if error
}
