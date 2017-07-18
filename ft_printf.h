/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nekitoss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 20:41:41 by nekitoss          #+#    #+#             */
/*   Updated: 2017/07/18 20:41:45 by nekitoss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"
# include <inttypes.h>
# include <wchar.h>

# define SKIP "#-+0 hljz123456789."
# define CONV "idDoOuUxXsScCp%"
# define EOS -1
# define DIGITS "0123456789"
# define DIGITS_D "0123456789."

# define DIEZ ls->flags[0]
# define ZERO ls->flags[1]
# define MINUS ls->flags[2]
# define PLUS ls->flags[3]
# define SPACE ls->flags[4]
# define _HH ls->flags[5]
# define H_ ls->flags[6]
# define _LL ls->flags[7]
# define L_ ls->flags[8]
# define J_ ls->flags[9]
# define Z_ ls->flags[10]
# define DOT ls->flags[11]
# define BODY ls->bod

typedef struct	s_print_p_list
{
	char	flags[12];
	char	*pre;
	char	*bod;
	char	*start;
	char	*middle;
	char	*end;
	char	*ptr_end;
	char	convertor;
	size_t	len;
	ssize_t	precision;
	ssize_t	width;
	va_list	ap;
}				t_p_list;

int				ft_printf(char *str, ...);
int				my_err(int errnum);
void			ft_add_prefix(t_p_list *ls);
size_t			ft_count(char *str, char c);
int				search_zero_flag(char *str);
void			search_flags(t_p_list *ls);
char			*ft_newstrchar(size_t len, char c);
void			clear_struct(t_p_list *ls);
size_t			ft_freelist(t_p_list **ls);
uintmax_t		ft_unsigned_size(t_p_list *ls);
intmax_t		ft_signed_size(t_p_list *ls);
void			flag_width_dec(t_p_list *ls);
void			flag_width_str(t_p_list *ls);
void			conv_percent(t_p_list *ls);
void			conv_d(t_p_list *ls);
void			conv_o(t_p_list *ls);
void			conv_u(t_p_list *ls);
void			conv_x(t_p_list *ls, int big_l);
void			conv_p(t_p_list *ls);
char			*convert_wc_to_str(unsigned long long c, char *str);
void			conv_c_whitechar(t_p_list *ls);
void			conv_s_whitechar(t_p_list *ls);
void			conv_c(t_p_list *ls);
void			conv_s(t_p_list *ls);
void			conv_big(t_p_list *ls);
void			make_conversion(t_p_list *ls);
size_t			convert_last_numb(t_p_list *ls);
size_t			convert_r_dot(t_p_list *ls);
size_t			convert_l_dot(t_p_list *ls);
int				find_last_number(t_p_list *ls);
void			search_precision_and_width(t_p_list *ls, int dot,
												int dig, int ascii);
void			cut_a_piece(t_p_list *ls, int pos);
void			flag_width_dec2(t_p_list *ls);
void			cut_a_piece_part1(t_p_list *ls);
int				ft_isswappable(char c);
#endif
