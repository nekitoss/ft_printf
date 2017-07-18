/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertor_choose_and_percent.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:24:45 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:24:47 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_percent(t_p_list *ls)
{
	BODY = ft_strnew(1);
	*(BODY) = '%';
	flag_width_str(ls);
}

void		conv_big(t_p_list *ls)
{
	_LL = 0;
	L_ = 1;
	(ls->convertor == 'D') ? conv_d(ls) : 0;
	(ls->convertor == 'O') ? conv_o(ls) : 0;
	(ls->convertor == 'U') ? conv_u(ls) : 0;
	(ls->convertor == 'S') ? conv_s(ls) : 0;
	(ls->convertor == 'C') ? conv_c(ls) : 0;
}

void		make_conversion(t_p_list *ls)
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
