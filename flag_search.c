/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:25:16 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:25:17 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

void		search_flags(t_p_list *ls)
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
