/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_and_width.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:28:03 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:28:04 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		convert_last_numb(t_p_list *ls)
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

size_t		convert_r_dot(t_p_list *ls)
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

size_t		convert_l_dot(t_p_list *ls)
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

int			find_last_number(t_p_list *ls)
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

void		search_precision_and_width(t_p_list *ls, int dot, int dig, int ascii)
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
