/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 10:15:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/07 18:55:30 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <unistd.h>

int			ft_printf_write(t_printf_env *env,
							char const *str,
							size_t n)
{
	return (env->writer(env, str, n));
}

int			ft_printf_write_string_pad(t_printf_env *env,
									   char const *str,
									   char padc)
{
	t_printf_pad_fn			func;

	ft_printf_pad_init(&env->padder, env);
	func = (env->options & PO_RIGHT) != 0
		? ft_printf_pad_r
		: ft_printf_pad_l;
	ft_printf_pad_set(&env->padder, func, str, padc);
	env->padder.func(&env->padder);
	ft_printf_write(env, env->padder.buf, ft_strlen(env->padder.buf));
	ft_printf_pad_reset(&env->padder);
	return (env->code);
}

int			ft_printf_write_w(t_printf_env *env,
							wchar_t const *str,
							size_t n)
{
	return (env->writer_w(env, str, n));
}

int			ft_printf_write_string_pad_w(t_printf_env *env,
										 wchar_t const *str,
										 wchar_t padc)
{
	t_printf_pad_fn			func;

	ft_printf_pad_init(&env->padder, env);
	func = (env->options & PO_RIGHT) != 0
		? ft_printf_pad_r
		: ft_printf_pad_l;
	ft_printf_pad_set_w(&env->padder, func, str, padc);
	env->padder.func(&env->padder);
	ft_printf_write_w(env, env->padder.wbuf, env->padder.max);
	ft_printf_pad_reset(&env->padder);
	return (env->code);
}

int			ft_printf_write_number_pad(t_printf_env *env,
									   t_printf_arg const *arg,
									   unsigned base,
									   char const *prefix)
{
	char					*buf;
	char					padc;
	int						code;
	int						len;

	code = 0;
	buf = ft_printf_arg_stringer(env, arg, base);
	len = ft_strlen(buf) + 1 + (prefix ? ft_strlen(prefix) : 0);
	buf = ft_strrealloc(buf, len);
	if (prefix)
	{
		ft_strnrot_r(buf, len, ft_strlen(prefix));
		ft_strncpy(buf, prefix, ft_strlen(prefix));
	}
	if (env->upper)
		ft_strtoupper(buf);
	buf = (char*)ft_realloc((void*)buf, sizeof(char) * len);
	padc = ' ';
	if ((env->options & PO_ZERO) != 0
		&& (env->options & PO_RIGHT) == 0)
		padc = '0';
	if ((env->options & PO_SIGN) != 0)
	{
		if (arg->sign)
		{
			ft_strnrot_one_r(buf, len);
			buf[0] = '+';
		}
	}
	else
	{
		if ((env->options & PO_BLANK) != 0)
		{
			ft_strnrot_one_r(buf, len);
			buf[0] = ' ';
		}
	}
	code += ft_printf_write_string_pad(env, buf, padc);
	ft_strdel(&buf);
	return (code);
}

int			ft_printf_write_console(t_printf_env *env,
										   char const *str,
										   size_t n)
{
	int		len;

	len = write(env->fd, str, n);
	env->written += len;
	return (len);
}


int			ft_printf_write_buffer(t_printf_env *env,
								   char const *str,
								   size_t n)
{
	char	*pbuf;
	int		len;

	if (!str)
		return (0);
	len = str ? ft_strlen(str) : 0;
	len = len < (int)n ? len : (int)n;
	if ((env->written + (size_t)len) >= env->buffer_cap)
	{
		env->code = PS_BUF_TOO_SMALL;
		return (env->code);
	}
	pbuf = env->buffer + env->written;
	ft_strncpy(pbuf, str, len);
	len = ft_strlen(pbuf);
	env->written += len;
	return (len);
}

int			ft_printf_write_console_w(t_printf_env *env,
									  wchar_t const *str,
									  size_t n)
{
	int		len;

	(void)n;
	len = ft_putwstr_fd(str, env->fd);
	env->written += len;
	return (len);
}


int			ft_printf_write_buffer_w(t_printf_env *env,
									 wchar_t const *str,
									 size_t n)
{
	wchar_t	*pbuf;
	int		len;

	if (!str)
		return (0);
	len = str ? ft_wstrlen(str) : 0;
	len = len < (int)n ? len : (int)n;
	if ((env->written + (size_t)len) >= env->buffer_cap)
	{
		env->code = PS_BUF_TOO_SMALL;
		return (env->code);
	}
	pbuf = env->wbuffer + env->written;
	ft_wstrncpy(pbuf, str, len);
	len = ft_wstrlen(pbuf);
	env->written += len;
	return (len);
}
