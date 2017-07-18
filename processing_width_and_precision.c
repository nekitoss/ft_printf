/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing_width_and_precision.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:30:25 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:30:27 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_add_prefix(t_p_list *ls)
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

char		*ft_newstrchar(size_t len, char c)
{
	return (((char *)ft_memset((void *)ft_strnew(len), c, len)));
}

void		flag_width_dec2(t_p_list *ls)
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

void		flag_width_dec(t_p_list *ls)
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

void		flag_width_str(t_p_list *ls)
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
