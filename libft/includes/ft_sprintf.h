/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 16:47:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/05/03 08:33:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H

/*
** INCLUDES
*/

# include <stdarg.h>

/*
** MACROS
*/

# define ERROR -1
# define BUFF_SIZE 4096

/*
** TYPEDEF && STRUCTURES
*/

typedef struct		s_printf
{
	char			buffer[BUFF_SIZE];
	char			*result;
	unsigned int	actual;
	unsigned int	ret;
}					t_printf;

typedef struct		s_type
{
	int			precision;
	int			i;
	int			sharp;
	int			plus;
	int			neg;
	int			space;
	int			zero;
	long long	width;
	long long	prec;
	int			warning;
	int			hh;
	int			h;
	int			l;
	int			ll;
	int			lmaj;
	char		conv;
}					t_type;

typedef struct		s_dconv
{
	char					*str;
	long long int			nbr;
	unsigned long long int	nbr2;
	int						width;
	long long				prec;
	int						len;
	double					doub;
	long double				ldoub;
}					t_dconv;

typedef struct		s_double
{
	char					sign;
	char					ldouble[10];
	char					exposant[20];
	char					mantisse[64];
	char					infinity[10001];
	char					real[10001];
	int						exp;
	unsigned long long		coop;
	int						i;
}					t_double;

/*
** A RANGER
*/

void				rework_str(t_dconv *var, t_double *doub);
void				zero_doub(t_dconv *var);
void				send_to_buffer(t_type *type, t_printf *data, va_list *ap);

/*
** INITIALISATION
*/

char				*ft_sprintf(const char *format, ...);

/*
** PARSER
*/

int					start_fullish_attr(t_printf *data, char *format
	, va_list *ap);

/*
** PRINTER
*/

void				ft_putbuffer(t_printf *data);
void				ft_add_char_to_buff(t_printf *data, char c);

/*
** CALCULS
*/

void				double_calculator(t_dconv *var);
void				infinity_mul(t_dconv *var, t_double *doub, int type);
void				infinity_mul2(t_dconv *var, t_double *doub);
void				infinity_div(t_dconv *var, t_double *doub, int type);
void				infinity_div2(t_dconv *var, t_double *doub);
void				infinity_add(t_double *doub, t_dconv *var, int type);
void				infinity_add5(t_double *doub, t_dconv *var);
void				ft_ntoa(t_dconv *var);
void				ft_ntoa2(t_dconv *var);
void				ft_ntootoa(t_dconv *var);
void				ft_ntohtoa(t_dconv *var, char *base);

/*
** UTILITYS
*/

void				ft_memset1(void *ptr, char c, int len);
int					ft_strlen1(char *str);
int					ft_strchr1(char needle, char *haystack);
void				ft_memmove1(char *dest, const char *src, int n);
int					free_error(void *ptr);
void				free_time(t_dconv *var);
void				ft_uppercase(char *str);
void				adjust_str(t_type *type, t_dconv *var);

/*
** CONVERSIONS
*/

int					add_x_to_buffer(t_type *type, t_printf *data, va_list *ap);
int					add_xmaj_to_buffer(t_type *type, t_printf *data
	, va_list *ap);
void				add_c_to_buffer(t_type *type, t_printf *data, va_list *ap);
void				add_s_to_buffer(t_type *type, t_printf *data, va_list *ap);
int					add_d_to_buffer(t_type *type, t_printf *data, va_list *ap);
int					add_o_to_buffer(t_type *type, t_printf *data, va_list *ap);
void				add_p_to_buffer(t_type *type, t_printf *data, va_list *ap);
int					add_u_to_buffer(t_type *type, t_printf *data, va_list *ap);
int					add_f_to_buffer(t_type *type, t_printf *data, va_list *ap);
void				add_percent_to_buffer(t_type *type, t_printf *data);

#endif
