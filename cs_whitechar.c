/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cs_whitechar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:29:07 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:29:09 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void		conv_c_whitechar(t_p_list *ls)
{
	wint_t wc_c;

	wc_c = va_arg(ls->ap, wint_t);
	BODY = convert_wc_to_str(wc_c, NULL);
	flag_width_str(ls);
}

void		conv_s_whitechar(t_p_list *ls)
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

void		conv_c(t_p_list *ls)
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

void		conv_s(t_p_list *ls)
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
