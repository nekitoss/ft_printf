/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_funtions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:28:49 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:28:50 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

uintmax_t	ft_unsigned_size(t_p_list *ls)
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

intmax_t	ft_signed_size(t_p_list *ls)
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
