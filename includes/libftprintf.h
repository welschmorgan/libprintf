/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 07:19:34 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 20:27:10 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_PRINTF_H
# define	FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include <inttypes.h>
# include <wchar.h>
# define FTPRINTF_TRIGGER_MAX	2

# define FTPRINTF_SUCCESS(code) (code >= 0)


/*
  Vous devez gérer les conversions suivantes : sSpdDioOuUxXcC
  • Vous devez gérer le %%
  • Vous devez gérer les flags #0-+ et espace
  • Vous devez gérer la taille minimum du champ
  • Vous devez gérer la précision
  • Vous devez gérer les flags hh h l ll j z
 */

typedef enum				e_printf_status
{
	PS_SUCCESS = 0,
	PS_BUF_TOO_SMALL = -100,
	PS_INVALID_CONV = -101,
	PS_INVALID_FLAG = -102,
	PS_INVALID_SMOD = -103,
	PS_INVALID_PREC = -104,
	PS_COUNT = 6,
	PS_UNKNOWN = PS_COUNT
}							t_printf_status;

typedef enum				e_printf_conv
{
	PC_STRING_LO,
	PC_STRING_UP,
	PC_POINTER_LO,
	PC_DECIMAL_LO,
	PC_DECIMAL_UP,
	PC_INTEGER_LO,
	PC_OCTAL_LO,
	PC_OCTAL_UP,
	PC_BINARY_LO,
	PC_BINARY_UP,
	PC_UNSIGNED_LO,
	PC_UNSIGNED_UP,
	PC_HEXA_LO,
	PC_HEXA_UP,
	PC_CHAR_LO,
	PC_CHAR_UP,
	PC_COUNT,
	PC_UNKNOWN = PC_COUNT
}							t_printf_conv;

typedef enum				e_printf_flags
{
	PF_HASH,
	PF_ZERO,
	PF_MINUS,
	PF_PLUS,
	PF_SPACE,
	PF_COUNT,
	PF_UNKNOWN = PF_COUNT
}							t_printf_flags;

typedef enum				e_printf_size_mods
{
	PSM_CHAR,
	PSM_SHORT,
	PSM_INT,
	PSM_LONG,
	PSM_LLONG,
	PSM_INTMAXT,
	PSM_SIZET,
	PSM_COUNT,
	PSM_UNKNOWN = PSM_COUNT
}							t_printf_size_mods;

typedef enum				e_printf_option
{
	PO_ZERO = 1 << 1,
	PO_SIGN = 1 << 2,
	PO_ALTERN = 1 << 3,
	PO_RIGHT = 1 << 4,
	PO_BLANK = 1 << 5,
	PO_UNSIGNED = 1 << 6,
	PO_COUNT = 6
}							t_printf_option;

struct						s_printf_env;
struct						s_printf_arg;
struct						s_printf_padder;
struct						s_printf_trigger;
struct						s_printf_prec;

typedef int					(*t_printf_func)(struct s_printf_env *);

typedef int					(*t_printf_writer)(struct s_printf_env *,
											   char const *,
											   size_t);

typedef int					(*t_printf_writer_w)(struct s_printf_env *,
												 wchar_t const *,
												 size_t);

typedef int					(*t_printf_pad_fn)(struct s_printf_padder *);


typedef int					(*t_printf_arg_getter)(struct s_printf_env *,
												   struct s_printf_arg *);
typedef char				*(*t_printf_arg_stringer)(struct s_printf_env *env,
													  struct s_printf_arg const *arg,
													  unsigned base);


typedef union				u_printf_arg_value
{
	char					c;
	short					s;
	int						i;
	unsigned				u;
	long					l;
	long long				ll;
	intmax_t				it;
	size_t					st;
}							t_printf_arg_value;

typedef struct				s_printf_arg
{
	t_printf_size_mods		type;
	t_printf_arg_getter		getter;
	t_printf_arg_stringer	stringer;
	int						sign;
	t_printf_arg_value		value;
}							t_printf_arg;

typedef struct				s_printf_trigger
{
	int						type;
	char					name[FTPRINTF_TRIGGER_MAX + 1];
	t_printf_func			func;
}							t_printf_trigger;

typedef struct				s_printf_prec
{
	char const				*starts[2];
	char					parts[2][32];
	int						values[2];
}							t_printf_prec;

typedef struct				s_printf_padder
{
	struct s_printf_env		*env;
	int						wide;
	wchar_t const			*wstr;
	char const				*str;
	wchar_t					*wbuf;
	char					*buf;
	int						len;
	int						min;
	int						max;
	t_printf_pad_fn			func;
	char					ch;
	wchar_t					wch;
}							t_printf_padder;

typedef struct				s_printf_env
{
	char const				*format;
	t_printf_status			code;
	int						fd;
	va_list					args;
	t_printf_prec			prec;
	unsigned				options;
	t_printf_size_mods		size_modifier;
	char					*buffer;
	size_t					buffer_cap;
	wchar_t					*wbuffer;
	int						upper;
	size_t					wbuffer_cap;
	size_t					written;
	t_printf_writer			writer;
	t_printf_writer_w		writer_w;
	t_printf_padder			padder;
	t_printf_trigger const	*converter;
	t_printf_arg			arg;
}							t_printf_env;

int							ft_printf_arg_get_char(t_printf_env *env,
												   t_printf_arg *arg);
int							ft_printf_arg_get_short(t_printf_env *env,
													t_printf_arg *arg);
int							ft_printf_arg_get_int(t_printf_env *env,
												  t_printf_arg *arg);
int							ft_printf_arg_get_uint(t_printf_env *env,
												   t_printf_arg *arg);
int							ft_printf_arg_get_uchar(t_printf_env *env,
												   t_printf_arg *arg);
int							ft_printf_arg_get_long(t_printf_env *env,
												   t_printf_arg *arg);
int							ft_printf_arg_get_llong(t_printf_env *env,
													t_printf_arg *arg);
int							ft_printf_arg_get_imax(t_printf_env *env,
												   t_printf_arg *arg);
int							ft_printf_arg_get_sizet(t_printf_env *env,
													t_printf_arg *arg);

char						*ft_printf_arg_stringer_int(t_printf_env *env,
														t_printf_arg const *arg,
														unsigned base);

char						*ft_printf_arg_stringer_uint(t_printf_env *env,
														 t_printf_arg const *arg,
														 unsigned base);
char						*ft_printf_arg_stringer_uchar(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base);

char						*ft_printf_arg_stringer_long(t_printf_env *env,
														 t_printf_arg const *arg,
														 unsigned base);
char						*ft_printf_arg_stringer_llong(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base);
char						*ft_printf_arg_stringer_imaxt(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base);
char						*ft_printf_arg_stringer_sizet(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base);

char						*ft_printf_arg_stringer(t_printf_env *env,
													t_printf_arg const *arg,
													unsigned base);

int							ft_printf_arg_set(t_printf_arg *arg,
											  t_printf_size_mods type,
											  t_printf_arg_value value);

int							ft_printf_arg_get(t_printf_env *env,
											  t_printf_size_mods type,
											  t_printf_arg *arg);

int							ft_printf_pad_reset(t_printf_padder *pad);
int							ft_printf_pad_init(t_printf_padder *pad, t_printf_env *env);
int							ft_printf_pad_set(t_printf_padder *pad,
											  t_printf_pad_fn func,
											  char const *str,
											  char c);
int							ft_printf_pad_set_w(t_printf_padder *pad,
												t_printf_pad_fn func,
												wchar_t const *str,
												wchar_t c);
int							ft_printf_pad_l(t_printf_padder *pad);
int							ft_printf_pad_r(t_printf_padder *pad);


int							ft_printf(const char *format,
									  ...);
int							ft_dprintf(int fd,
									   const char *format,
									   ...);
int							ft_printf(const char *format,
									  ...);
int							ft_sprintf(char *str,
									   const char *format,
									   ...);
int							ft_snprintf(char *str,
										size_t size,
										const char *format,
										...);

int							ft_vprintf(const char *format,
									   va_list ap);
int							ft_vdprintf(int fd,
										const char *format,
										va_list ap);
int							ft_vsprintf(char *str,
										const char *format,
										va_list ap);
int							ft_vsnprintf(char *str,
										 size_t size,
										 const char *format,
										 va_list ap);

int							ft_printf_write(t_printf_env *env,
											char const *str,
											size_t n);


int							ft_printf_write_string_pad(t_printf_env *env,
													   char const *str,
													   char c);
int							ft_printf_write_w(t_printf_env *env,
											  wchar_t const *str,
											  size_t n);


int							ft_printf_write_string_pad_w(t_printf_env *env,
														 wchar_t const *str,
														 wchar_t c);
int							ft_printf_write_number_pad(t_printf_env *env,
													   t_printf_arg const *arg,
													   unsigned base,
													   char const *prefix);

int							ft_printf_write_console(t_printf_env *env,
													char const *str,
													size_t n);
int							ft_printf_write_buffer(t_printf_env *env,
												   char const *str,
												   size_t n);

int							ft_printf_write_console_w(t_printf_env *env,
													  wchar_t const *str,
													  size_t n);
int							ft_printf_write_buffer_w(t_printf_env *env,
													 wchar_t const *str,
													 size_t n);

/*
** Printf env funcs
*/
int							ft_printf_init(t_printf_env *env,
										   char const *format,
										   va_list args);
int							ft_printf_restore(t_printf_env *env);
int							ft_printf_config(t_printf_env *env,
											 int fd,
											 t_printf_writer writer);
int							ft_printf_reset(t_printf_env *env);

char const					*ft_printf_status(t_printf_status status);

t_printf_trigger const		*ft_printf_find_conv(char const *name);
t_printf_trigger const		*ft_printf_find_flag(char const *name);
t_printf_trigger const		*ft_printf_find_size_mod(char const *name);
t_printf_trigger const		*ft_printf_find_trigger(char const *name,
													t_printf_trigger const *haystack,
													size_t n);

int							ft_printf_conv_string(t_printf_env *env);
int							ft_printf_conv_pointer(t_printf_env *env);
int							ft_printf_conv_decimal(t_printf_env *env);
int							ft_printf_conv_octal(t_printf_env *env);
int							ft_printf_conv_binary(t_printf_env *env);
int							ft_printf_conv_unsigned(t_printf_env *env);
int							ft_printf_conv_hexa(t_printf_env *env);
int							ft_printf_conv_char(t_printf_env *env);

int							ft_printf_flag_hash(t_printf_env *env);
int							ft_printf_flag_zero(t_printf_env *env);
int							ft_printf_flag_minus(t_printf_env *env);
int							ft_printf_flag_plus(t_printf_env *env);
int							ft_printf_flag_space(t_printf_env *env);

int							ft_printf_size_mod_char(t_printf_env *env);
int							ft_printf_size_mod_short(t_printf_env *env);
int							ft_printf_size_mod_int(t_printf_env *env);
int							ft_printf_size_mod_uint(t_printf_env *env);
int							ft_printf_size_mod_long(t_printf_env *env);
int							ft_printf_size_mod_llong(t_printf_env *env);
int							ft_printf_size_mod_intmaxt(t_printf_env *env);
int							ft_printf_size_mod_sizet(t_printf_env *env);

#endif
