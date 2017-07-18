#include "ft_printf.h"

int			my_err(int errnum)
{
	write(1, "Error occured in ", 17);
	ft_putnbr(errnum);
	return (0);
}

int			ft_isswappable(char c)
{
	if (c == ' ' || c == '+' || c == '-')
		return (1);
	else
		return (0);
}

void		ft_add_prefix(p_list *ls)
{
	char	*tmp;

	if (DIEZ && (ls->convertor == 'X' || ls->convertor == 'x'
									|| ls->convertor == 'p'))
	{
		tmp = ft_strdup((ls->convertor == 'X') ? "0X" : "0x");
		BODY = ft_strjoin_d(&tmp, &(BODY), 3);
		DIEZ = 0;
	}
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

int			search_zero_flag(char *str)
{
	int		result;
	size_t	pos;

	result = 0;
	pos = 0;
	if (str && *str)
	{
		while (str[pos + 1] != '\0')
		{
			if (pos == 0 && *str == '0')
			{
				ft_strchrdel(str, 0);
				result = 1;
				continue ;
			}
			if (!(ft_isdigit(str[pos])) && str[pos + 1] == '0')
			{
				ft_strchrdel(str, pos + 1);
				result = 1;
			}
			else
				pos++;
		}
	}
	return (result);
}

void		search_flags(p_list *ls)
{
	int tmp;

	tmp = 0;
	DIEZ = ft_count(ls->pre, '#') ? 1 : 0;
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

char		*ft_newstrchar(size_t len, char c)
{
	return (((char *)ft_memset((void *)ft_strnew(len), c, len)));
}

void		clear_struct(p_list *ls)
{
	ft_bzero((char *)ls->flags, sizeof(ls->flags));
	ft_strdel(&(ls->pre));
	ft_strdel(&(BODY));
	ls->precision = -1;
	ls->width = -1;
	ls->middle = NULL;
	ls->convertor = -1;
}

size_t		ft_freelist(p_list **ls)
{
	size_t len;

	len = (*ls)->len;
	va_end((*ls)->ap);
	ft_strdel(&((*ls)->pre));
	ft_strdel(&((*ls)->bod));
	free(*ls);
	*ls = NULL;
	return (len);
}

uintmax_t	ft_unsigned_size(p_list *ls)
{
	uintmax_t	num;

	num = va_arg(ls->ap, uintmax_t);
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

intmax_t	ft_signed_size(p_list *ls)
{
	intmax_t	num;

	num = va_arg(ls->ap, intmax_t);
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

void		flag_width_dec2(p_list *ls)
{
	ssize_t	body_len;
	char	*tmp;

	body_len = ft_strlen(BODY);
	if (ls->width > body_len)
	{
		tmp = ft_newstrchar(ls->width - body_len, ZERO && !MINUS
							&& ls->precision == EOS ? '0' : ' ');
		(*tmp == ' ') ? ft_add_prefix(ls) : 0;
		if (ls->precision && ft_isswappable(*BODY) && *tmp == '0')
			ft_swap_chr(BODY, tmp);
		if (MINUS)
			BODY = ft_strjoin_d(&(BODY), &(tmp), 3);
		else
			BODY = ft_strjoin_d(&(tmp), &(BODY), 3);
	}
	ft_add_prefix(ls);
	ls->len += ft_putnstr(BODY, ft_strlen(BODY));
}

void		flag_width_dec(p_list *ls)
{
	ssize_t	body_len;
	char	*tmp;

	if (ft_isdigit(*BODY) && (PLUS || SPACE))
	{
		tmp = ft_strdup(PLUS ? "+" : " ");
		BODY = ft_strjoin_d(&(tmp), &(BODY), 3);
	}
	body_len = ft_strlen(BODY);
	if (ls->precision && !(ft_isdigit(*BODY)))
		body_len--;
	if (ls->precision > body_len)
	{
		tmp = ft_newstrchar((ls->precision - body_len), '0');
		if (ft_isswappable(*BODY))
			ft_swap_chr(BODY, tmp);
		BODY = ft_strjoin_d(&(tmp), &(BODY), 3);
	}
	flag_width_dec2(ls);
}

void		flag_width_str(p_list *ls)
{
	ssize_t	body_len;
	char	*tmp;
	int		kostil;

	kostil = ((!(*BODY) && (ls->convertor == 'c'
				|| ls->convertor == 'C')) ? 1 : 0);
	if (ls->convertor == 's' && ls->precision > EOS &&
				ls->precision < (ssize_t)ft_strlen(BODY))
		BODY = ft_strsub_d(&(BODY), 0, ls->precision);
	body_len = ((ls->precision && (ls->convertor == 'c' ||
				ls->convertor == 'C')) || kostil ? 1 : ft_strlen(BODY));
	if (body_len < ls->width)
	{
		tmp = ft_newstrchar(ls->width - body_len,
							ZERO && !MINUS ? '0' : ' ');
		if (MINUS)
			BODY = ft_strjoin_d(&(BODY), &(tmp), 3);
		else
			BODY = ft_strjoin_d(&(tmp), &(BODY), 3);
	}
	(kostil && MINUS) ? ft_putchar(0) : 0;
	ls->len += ft_putnstr(BODY, ft_strlen(BODY)) + kostil;
	(kostil && !MINUS) ? ft_putchar(0) : 0;
}

void		conv_percent(p_list *ls)
{
	BODY = ft_strnew(1);
	*(BODY) = '%';
	flag_width_str(ls);
}

void		conv_d(p_list *ls)
{
	intmax_t d;

	d = ft_signed_size(ls);
	if (!(ls->precision) && !d)
		BODY = ft_strnew(0);
	else
		BODY = ft_itoa(d);
	flag_width_dec(ls);
}

void		conv_o(p_list *ls)
{
	uintmax_t o;

	PLUS = 0;
	SPACE = 0;
	o = ft_unsigned_size(ls);
	if (!(ls->precision) && !o)
	{
		if (!DIEZ)
			BODY = ft_strnew(0);
		else
		{
			BODY = ft_strnew(1);
			*BODY = '0';
		}
	}
	else
		BODY = ft_itoa_base_u(o, 8, 0, (DIEZ && o) ? 1 : 0);
	flag_width_dec(ls);
}

void		conv_u(p_list *ls)
{
	uintmax_t u;

	PLUS = 0;
	SPACE = 0;
	u = ft_unsigned_size(ls);
	if (!(ls->precision) && !u)
		BODY = ft_strnew(0);
	else
		BODY = ft_itoa_base_u(u, 10, 0, 0);
	flag_width_dec(ls);
}

void		conv_x(p_list *ls, int big_l)
{
	uintmax_t x;

	PLUS = 0;
	SPACE = 0;
	x = ft_unsigned_size(ls);
	!x ? DIEZ = 0 : 0;
	if (DIEZ)
	{
		if (ls->width > 2)
			ls->width -= 2;
		else if (ls->width != EOS)
			ls->width = 0;
	}
	if (!(ls->precision) && !x)
		BODY = ft_strnew(0);
	else
		BODY = ft_itoa_base_u(x, 16, big_l, 0);
	flag_width_dec(ls);
}

void		conv_p(p_list *ls)
{
	uintmax_t p;

	DIEZ = 1;
	J_ = 1;
	PLUS = 0;
	SPACE = 0;
	p = ft_unsigned_size(ls);
	if (DIEZ)
	{
		if (ls->width > 2)
			ls->width -= 2;
		else if (ls->width != EOS)
			ls->width = 0;
	}
	if (!(ls->precision) && !p)
		BODY = ft_strnew(0);
	else
		BODY = ft_itoa_base_u(p, 16, 0, 0);
	flag_width_dec(ls);
}

char		*convert_wc_to_str(unsigned long long c, char *str)
{
	str = ft_strnew(4);
	if (c <= 0x0000007F)
	{
		str[0] = c;
	}
	else if (c <= 0x000007FF)
	{
		str[1] = (c & 0b00111111) | 0b10000000;
		str[0] = ((c >> 6) & 0b00011111) | 0b11000000;
	}
	else if (c <= 0x0000FFFF)
	{
		str[2] = (c & 0b00111111) | 0b10000000;
		str[1] = ((c >> 6) & 0b00111111) | 0b10000000;
		str[0] = ((c >> 12) & 0b00001111) | 0b11100000;
	}
	else if (c <= 0x001FFFFF)
	{
		str[3] = (c & 0b00111111) | 0b10000000;
		str[2] = ((c >> 6) & 0b00111111) | 0b10000000;
		str[1] = ((c >> 12) & 0b00111111) | 0b10000000;
		str[0] = ((c >> 18) & 0b00000111) | 0b11110000;
	}
	return (str);
}

void		conv_c_whitechar(p_list *ls)
{
	wint_t wc_c;

	wc_c = va_arg(ls->ap, wint_t);
	BODY = convert_wc_to_str(wc_c, NULL);
	flag_width_str(ls);
}

void		conv_s_whitechar(p_list *ls)
{
	wchar_t		*wc_s;
	ssize_t		i;
	char		*tmp;
	ssize_t		ch_len;

	BODY = ft_strnew(0);
	wc_s = va_arg(ls->ap, wchar_t *);
	i = 0;
	ch_len = 0;
	if (!wc_s)
		BODY = ft_strdup("(null)");
	else
	{
		while (wc_s[i])
		{
			tmp = convert_wc_to_str(wc_s[i], NULL);
			ch_len += ft_strlen(tmp);
			if (ls->precision == EOS || ch_len <= ls->precision)
				BODY = ft_strjoin_d(&(BODY), &tmp, 3);
			else
				break ;
			i++;
		}
	}
	flag_width_str(ls);
}

void		conv_c(p_list *ls)
{
	char c;

	if (!L_)
	{
		c = (ls->convertor == -1 ? *(ls->middle) : va_arg(ls->ap, int));
		BODY = ft_strnew(1);
		*(BODY) = c;
		flag_width_str(ls);
	}
	else
		conv_c_whitechar(ls);
}

void		conv_s(p_list *ls)
{
	char *s;

	if (!L_)
	{
		s = va_arg(ls->ap, char *);
		if (!s)
			BODY = ft_strdup("(null)");
		else
			BODY = ft_strdup(s);
		flag_width_str(ls);
	}
	else
		conv_s_whitechar(ls);
}

void		conv_big(p_list *ls)
{
	_LL = 0;
	L_ = 1;
	(ls->convertor == 'D') ? conv_d(ls) : 0;
	(ls->convertor == 'O') ? conv_o(ls) : 0;
	(ls->convertor == 'U') ? conv_u(ls) : 0;
	(ls->convertor == 'S') ? conv_s(ls) : 0;
	(ls->convertor == 'C') ? conv_c(ls) : 0;
}

void		make_conversion(p_list *ls)
{
	(ls->convertor == 'i') ? conv_d(ls) : 0;
	(ls->convertor == 'd') ? conv_d(ls) : 0;
	(ls->convertor == 'D') ? conv_big(ls) : 0;
	(ls->convertor == 'o') ? conv_o(ls) : 0;
	(ls->convertor == 'O') ? conv_big(ls) : 0;
	(ls->convertor == 'u') ? conv_u(ls) : 0;
	(ls->convertor == 'U') ? conv_big(ls) : 0;
	(ls->convertor == 'x') ? conv_x(ls, 0) : 0;
	(ls->convertor == 'X') ? conv_x(ls, 1) : 0;
	(ls->convertor == 's') ? conv_s(ls) : 0;
	(ls->convertor == 'S') ? conv_big(ls) : 0;
	(ls->convertor == 'c') ? conv_c(ls) : 0;
	(ls->convertor == 'C') ? conv_big(ls) : 0;
	(ls->convertor == 'p') ? conv_p(ls) : 0;
	(ls->convertor == '%') ? conv_percent(ls) : 0;
	(ls->convertor == -1) ? conv_c(ls) : 0;
}

size_t		convert_last_numb(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

	pos = ft_strcstr_f(ls->pre, DIGITS, 1);
	tmp1 = ft_strsub(ls->pre, 0, pos + 1);
	pos = ft_strcstr(tmp1, DIGITS, 1);
	tmp2 = ft_strsub(tmp1, ++pos, ft_strlen(tmp1));
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

size_t		convert_r_dot(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

	pos = ft_strcstr_f(ls->pre, ".", 1);
	if (!ft_isdigit(*(ls->pre + pos + 1)))
		return (0);
	tmp1 = ft_strsub(ls->pre, pos + 1, ft_strlen(ls->pre));
	pos = ft_strcstr(tmp1, DIGITS, 1);
	tmp2 = ft_strsub(tmp1, 0, (pos > -1) ? pos : (int)ft_strlen(tmp1));
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

size_t		convert_l_dot(p_list *ls)
{
	int		pos;
	char	*tmp1;
	char	*tmp2;
	size_t	res;

	pos = ft_strcstr_f(ls->pre, ".", 1);
	if (pos <= 0)
		return (0);
	tmp1 = ft_strsub(ls->pre, 0, pos);
	if (!ft_isdigit(*(ls->pre + pos - 1)))
	{
		pos = ft_strcstr(tmp1, DIGITS, 1);
		if (pos == EOS)
		{
			ft_strdel(&tmp1);
			return (0);
		}
		tmp1 = ft_strsub_d(&(tmp1), 0, pos);
	}
	pos = ft_strcstr(tmp1, DIGITS_D, 1);
	tmp2 = ft_strsub(tmp1, ++pos, ft_strlen(tmp1));
	res = ft_atoi(tmp2);
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (res);
}

int			find_last_number(p_list *ls)
{
	int		pos;
	char	*tmp;

	pos = ft_strlen(ls->pre);
	if (ft_isdigit(*(ls->pre + pos)) || *(ls->pre + pos) == '.')
		return (ft_strcstr(ls->pre, DIGITS_D, 1));
	pos = ft_strcstr_f(ls->pre, DIGITS_D, 1);
	if (pos != EOS)
	{
		tmp = ft_strsub(ls->pre, 0, pos);
		pos = ft_strcstr(tmp, DIGITS_D, 1);
		ft_strdel(&tmp);
	}
	return (pos);
}

void		search_precision_and_width(p_list *ls, int dot, int dig, int ascii)
{
	if (dot == EOS && dig != EOS)
		ls->width = convert_last_numb(ls);
	else if (dot > EOS && dig > EOS)
	{
		ls->precision = 0;
		if (dot < dig)
		{
			ls->precision = convert_r_dot(ls);
			if (dot < ascii && ascii < dig)
				ls->width = convert_last_numb(ls);
			else
				ls->width = convert_l_dot(ls);
		}
		else
		{
			ls->width = convert_l_dot(ls);
		}
	}
	else if (dot > EOS && dig == EOS)
	{
		ls->width = 0;
		ls->precision = 0;
	}
}

void		cut_a_piece_part1(p_list *ls)
{
	ls->end = ft_strchr(ls->start, '%');
	ls->pre = ft_strsub(ls->start, 0, (ls->middle - ls->start));
	if (ls->pre && *(ls->pre))
	{
		search_flags(ls);
		search_precision_and_width(ls, ft_strcstr_f(ls->pre, ".", 1),
			ft_strcstr_f(ls->pre, DIGITS, 1), find_last_number(ls));
	}
}

void		cut_a_piece(p_list *ls, int pos)
{
	while (ls->start)
	{
		if (!(ls->start[1]) && *(ls->start) == '%')
			break ;
		ls->start = ls->end + 1;
		pos = ft_strcstr(ls->start, SKIP, 0);
		ls->middle = ((pos >= 0) ? ls->start + pos : ls->ptr_end);
		cut_a_piece_part1(ls);
		ls->convertor = !(ft_strchr(CONV, *(ls->middle))) ? -1 : *(ls->middle);
		make_conversion(ls);
		(!ls->end) ? (ls->end = ls->ptr_end) : 0;
		if (ls->middle < ls->end)
			ls->len += ft_putnstr(ls->middle + 1, ls->end - ls->middle - 1);
		if (ls->end != ls->ptr_end && ls->convertor == '%')
		{
			pos = ft_strcstr_f(ls->end + 1, "%", 0);
			ls->len += ft_putnstr(ls->end + 1,
							(pos > EOS ? pos : ls->ptr_end - ls->end - 1));
			ls->end = (pos > EOS) ? ls->end + pos + 1 : ls->ptr_end;
		}
		clear_struct(ls);
		if (ls->end == ls->ptr_end)
			return ;
	}
}

int			ft_printf(char *str, ...)
{
	p_list	*ls;

	ls = (p_list *)ft_memalloc(sizeof(p_list));
	ls->end = ft_strchr(str, '%');
	if (ls->end)
	{
		clear_struct(ls);
		va_start(ls->ap, str);
		ls->start = str;
		ls->ptr_end = ft_strchr(ls->start, 0);
		ls->len += ft_putnstr(ls->start, ls->end - ls->start);
		ls->middle = ls->end;
		cut_a_piece(ls, 0);
		return ((int)ft_freelist(&ls));
	}
	else
	{
		return ((int)ft_putstr(str));
	}
	return (0);
}
