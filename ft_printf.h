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

typedef struct  print_list
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
}               p_list;

int				ft_printf(char *str, ...);
int				my_err(int errnum);
void			ft_add_prefix(p_list *ls);
size_t			ft_count(char *str, char c);
int				search_zero_flag(char *str);
void			search_flags(p_list *ls);
char			*ft_newstrchar(size_t len, char c);
void			clear_struct(p_list *ls);
size_t			ft_freelist(p_list **ls);
uintmax_t		ft_unsigned_size(p_list *ls);
intmax_t		ft_signed_size(p_list *ls);
void			flag_width_dec(p_list *ls);
void			flag_width_str(p_list *ls);
void		 	conv_percent(p_list *ls);
void			conv_d(p_list *ls);
void			conv_o(p_list *ls);
void			conv_u(p_list *ls);
void			conv_x(p_list *ls, int big_l);
void			conv_p(p_list *ls);
char			*convert_wc_to_str(unsigned long long c, char *str);
void			conv_c_whitechar(p_list *ls);
void			conv_s_whitechar(p_list *ls);
void			conv_c(p_list *ls);
void			conv_s(p_list *ls);
void			conv_big(p_list *ls);
void			make_conversion(p_list *ls);
size_t			convert_last_numb(p_list *ls);
size_t			convert_r_dot(p_list *ls);
size_t			convert_l_dot(p_list *ls);
int				find_last_number(p_list *ls);
void			search_precision_and_width(p_list *ls, int dot, int dig, int ascii);
void			cut_a_piece(p_list *ls, int pos);
void			flag_width_dec2(p_list *ls);
void			cut_a_piece_part1(p_list *ls);
#endif