/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 15:22:40 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/07 17:02:09 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"

static t_printf_arg	const	g_printf_args[PSM_COUNT + 1] = {
	{PSM_CHAR, ft_printf_arg_get_char, ft_printf_arg_stringer_int, 1, {}},
	{PSM_SHORT, ft_printf_arg_get_short, ft_printf_arg_stringer_int, 1, {}},
	{PSM_INT, ft_printf_arg_get_int, ft_printf_arg_stringer_int, 1, {}},
	{PSM_FLOAT, ft_printf_arg_get_float, ft_printf_arg_stringer_float, 1, {}},
	{PSM_DOUBLE, ft_printf_arg_get_double, ft_printf_arg_stringer_double, 1, {}},
	{PSM_LDOUBLE, ft_printf_arg_get_ldouble, ft_printf_arg_stringer_double, 1, {}},
	{PSM_LONG, ft_printf_arg_get_long, ft_printf_arg_stringer_long, 1, {}},
	{PSM_LLONG, ft_printf_arg_get_llong, ft_printf_arg_stringer_llong, 1, {}},
	{PSM_INTMAXT, ft_printf_arg_get_imax, ft_printf_arg_stringer_imaxt, 1, {}},
	{PSM_SIZET, ft_printf_arg_get_sizet, ft_printf_arg_stringer_sizet, 1, {}},
	{PSM_UNKNOWN, NULL, NULL, 0, {}}
};

char						*ft_printf_arg_stringer_double(t_printf_env *env,
														   t_printf_arg const *arg,
														   unsigned base)
{
	(void)env;
	return (ft_ftoa(arg->value.d, 14, base));
}

char						*ft_printf_arg_stringer_float(t_printf_env *env,
														   t_printf_arg const *arg,
														   unsigned base)
{
	(void)env;
	return (ft_ftoa(arg->value.f, env->prec.values[1], base));
}


char						*ft_printf_arg_stringer_int(t_printf_env *env,
														t_printf_arg const *arg,
														unsigned base)
{
	(void)env;
	if ((env->options & PO_UNSIGNED) != 0)
		return (ft_ubtoa(arg->value.u, base));
	return (ft_ibtoa(arg->value.i, base));
}

char						*ft_printf_arg_stringer_long(t_printf_env *env,
														 t_printf_arg const *arg,
														 unsigned base)
{
	(void)env;
	return (ft_lbtoa(arg->value.l, base));
}
char						*ft_printf_arg_stringer_llong(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base)
{
	(void)env;
	return (ft_llbtoa(arg->value.ll, base));
}
char						*ft_printf_arg_stringer_imaxt(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base)
{
	(void)env;
	return (ft_lbtoa((long)arg->value.it, base));
}

char						*ft_printf_arg_stringer_sizet(t_printf_env *env,
														  t_printf_arg const *arg,
														  unsigned base)
{
	(void)env;
	return (ft_llbtoa((long long)arg->value.st, base));
}
int							ft_printf_arg_get_char(t_printf_env *env,
												   t_printf_arg *arg)
{
	arg->type = PSM_CHAR;
	arg->value.c = (char)va_arg(env->args, int);
	arg->sign = arg->value.c < 0 ? -1 : 1;
	return (0);
}
int							ft_printf_arg_get_short(t_printf_env *env,
													t_printf_arg *arg)
{
	arg->type = PSM_SHORT;
	arg->value.s = (short)va_arg(env->args, int);
	arg->sign = arg->value.s < 0 ? -1 : 1;
	return (0);
}
int							ft_printf_arg_get_float(t_printf_env *env,
													t_printf_arg *arg)
{
	arg->type = PSM_FLOAT;
	arg->value.f = (float)va_arg(env->args, double);
	arg->sign = arg->value.f < -FT_EPSILON ? -1 : 1;
	return (0);
}

int							ft_printf_arg_get_double(t_printf_env *env,
													 t_printf_arg *arg)
{
	arg->type = PSM_DOUBLE;
	arg->value.d = (double)va_arg(env->args, double);
	arg->sign = arg->value.d < -FT_EPSILON ? -1 : 1;
	return (0);
}

int							ft_printf_arg_get_ldouble(t_printf_env *env,
													 t_printf_arg *arg)
{
	arg->type = PSM_LDOUBLE;
	arg->value.d = (long double)va_arg(env->args, long double);
	arg->sign = arg->value.d < -FT_EPSILON ? -1 : 1;
	return (0);
}

int							ft_printf_arg_get_int(t_printf_env *env,
												  t_printf_arg *arg)
{
	arg->type = PSM_INT;
	if ((env->options & PO_UNSIGNED) != 0)
	{
		arg->value.u = (unsigned)va_arg(env->args, unsigned);
		arg->sign = 1;
	}
	else
	{
		arg->value.i = (int)va_arg(env->args, int);
		arg->sign = arg->value.i < 0 ? -1 : 1;
	}
	return (0);
}


int							ft_printf_arg_get_long(t_printf_env *env,
												   t_printf_arg *arg)
{
	arg->type = PSM_LONG;
	arg->value.l = (long)va_arg(env->args, long);
	arg->sign = arg->value.l < 0 ? -1 : 1;
	return (0);
}
int							ft_printf_arg_get_llong(t_printf_env *env,
													t_printf_arg *arg)
{
	arg->type = PSM_LLONG;
	arg->value.ll = (long long)va_arg(env->args, long long);
	arg->sign = arg->value.ll < 0 ? -1 : 1;
	return (0);
}
int							ft_printf_arg_get_imax(t_printf_env *env,
												   t_printf_arg *arg)
{
	arg->type = PSM_INTMAXT;
	arg->value.it = (intmax_t)va_arg(env->args, intmax_t);
	arg->sign = arg->value.it < 0 ? -1 : 1;
	return (0);
}
int							ft_printf_arg_get_sizet(t_printf_env *env,
													t_printf_arg *arg)
{
	arg->type = PSM_SIZET;
	arg->value.st = (size_t)va_arg(env->args, size_t);
	arg->sign = 1;
	return (0);
}

char						*ft_printf_arg_stringer(t_printf_env *env,
												   t_printf_arg const *arg,
													unsigned base)
{
	t_printf_arg const	*pknown;

	pknown = &g_printf_args[arg->type];
	return (pknown->stringer(env, arg, base));
}

int							ft_printf_arg_get(t_printf_env *env,
											  t_printf_size_mods type,
											  t_printf_arg *arg)
{
	t_printf_arg const	*pknown;

	pknown = &g_printf_args[type];
	return (pknown->getter(env, arg));
}

int							ft_printf_arg_set(t_printf_arg *arg,
											  t_printf_size_mods type,
											  t_printf_arg_value value)
{
	arg->type = type;
	ft_memcpy((void*)&arg->value,
			  (const void*)&value,
			  sizeof(t_printf_arg_value));
	return (0);

}
