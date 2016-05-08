/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions_string.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 14:57:49 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/08 11:05:46 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int							ft_printf_conv_pointer(t_printf_env *env)
{
	long					addr;
	char					*buf;

	addr = (long)va_arg(env->args, void*);
	if (!addr)
	{
		ft_printf_write(env, "(nil)", 5);
	}
	else
	{
		ft_printf_write(env, "0x", 2);
		buf = ft_lbtoa(addr >> 16, 16);
		if (buf)
		{
			ft_printf_write_string_pad(env, buf, ' ');
			ft_strdel(&buf);
		}
		buf = ft_lbtoa(addr & 0xffff, 16);
		if (buf)
		{
			ft_printf_write_string_pad(env, buf, ' ');
			ft_strdel(&buf);
		}
	}
	return (env->code);
}

int							ft_printf_conv_string(t_printf_env *env)
{
	char const				*str;
	wchar_t const			*wstr;
	int						isw;

	isw = env->size_modifier == PSM_LONG
		|| ft_strisupper(env->converter->name);
	if (isw)
	{
		wstr = (wchar_t const *)va_arg(env->args, wchar_t const*);
		if ((env->options & PO_BLANK) != 0
			&& (env->options & PO_SIGN) == 0
			&& !wstr[0])
			ft_printf_write(env, " ", 1);
		ft_printf_write_string_pad_w(env, wstr, L' ');
	}
	else
	{
		str = (char const*)va_arg(env->args, char const*);
		if ((env->options & PO_BLANK) != 0
			&& (env->options & PO_SIGN) == 0
			&& !str[0])
			ft_printf_write(env, " ", 1);
		ft_printf_write_string_pad(env, str, ' ');
	}
	return (env->code);
}

int							ft_printf_conv_char(t_printf_env *env)
{
	char					c[2];
	wchar_t					wc[2];
	int						isw;

	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	c[1] = 0;
	wc[1] = 0;
	isw = env->size_modifier == PSM_LONG
		|| ft_strisupper(env->converter->name);
	if (isw)
	{
		wc[0] = env->arg.value.l;
		ft_printf_write_w(env, &wc[0], 1);
	}
	else
	{
		c[0] = env->arg.value.c;
		ft_printf_write(env, &c[0], 1);
	}
	return (env->code);
}
