/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doux.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:25:05 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:25:06 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_d(t_p_list *ls)
{
	intmax_t d;

	d = ft_signed_size(ls);
	if (!(ls->precision) && !d)
		BODY = ft_strnew(0);
	else
		BODY = ft_itoa(d);
	flag_width_dec(ls);
}

void		conv_o(t_p_list *ls)
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

void		conv_u(t_p_list *ls)
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

void		conv_x(t_p_list *ls, int big_l)
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

void		conv_p(t_p_list *ls)
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
