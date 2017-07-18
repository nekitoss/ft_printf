/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:23:41 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:23:46 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		clear_struct(t_p_list *ls)
{
	ft_bzero((char *)ls->flags, sizeof(ls->flags));
	ft_strdel(&(ls->pre));
	ft_strdel(&(BODY));
	ls->precision = -1;
	ls->width = -1;
	ls->middle = NULL;
	ls->convertor = -1;
}

size_t		ft_freelist(t_p_list **ls)
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

void		cut_a_piece_part1(t_p_list *ls)
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

void		cut_a_piece(t_p_list *ls, int pos)
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
	t_p_list	*ls;

	ls = (t_p_list *)ft_memalloc(sizeof(t_p_list));
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
