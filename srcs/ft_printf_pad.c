/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pad.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 13:33:18 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/08 10:53:01 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int							ft_printf_pad_reset(t_printf_padder *pad)
{
	if (pad->wbuf)
		ft_wstrdel(&pad->wbuf);
	if (pad->buf)
		ft_strdel(&pad->buf);
	return (0);
}

int							ft_printf_pad_init(t_printf_padder *pad, t_printf_env *env)
{
	ft_memset((void*)pad, 0, sizeof(t_printf_padder));
	pad->env = env;
	return (0);
}

int							ft_printf_pad_set_w(t_printf_padder *pad,
												t_printf_pad_fn func,
												wchar_t const *str,
												wchar_t c)
{
	pad->wide = 1;
	pad->wstr = str;
	pad->min = pad->env->prec.values[0];
	pad->max = pad->env->prec.values[1];
	pad->len = (int)ft_wstrlen(str);
	if (pad->min >= 0)
		pad->len = pad->len < pad->min ? pad->min : pad->len;
	if (pad->max >= 0)
		pad->len = pad->len > pad->max ? pad->max : pad->len;
	pad->min = pad->min < 0 ? pad->len : pad->min;
	pad->max = pad->max < 0 ? pad->len : pad->max;
	pad->wch = c;
	pad->wbuf = ft_wstrnew(pad->max);
	if (pad->wbuf)
		ft_wstrncpy(pad->wbuf, pad->wstr, pad->max);
	pad->func = func;
	return (0);
}

int							ft_printf_pad_set(t_printf_padder *pad,
											  t_printf_pad_fn func,
											  char const *str,
											  char c)
{
	pad->wide = 0;
	pad->str = str;
	pad->min = pad->env->prec.values[0];
	pad->max = pad->env->prec.values[1];
	pad->len = (int)ft_strlen(str);
	if (pad->min >= 0 && pad->len < pad->min)
		pad->len = pad->min;
	if (pad->env->converter->type == PC_STRING_LO
		|| pad->env->converter->type == PC_STRING_UP)
	{
		if (pad->max >= 0 && pad->len > pad->max)
			pad->len = pad->max;
	}
	pad->ch = c;
	pad->buf = ft_strnew(pad->len);
	if (pad->buf)
		ft_strncpy(pad->buf, str, pad->len);
	pad->func = func;
	return (0);
}

int							ft_printf_pad_r(t_printf_padder *pad)
{
	if (pad->wide)
		ft_wstrnpad_r(pad->wbuf, pad->len, pad->wch);
	else
		ft_strnpad_r(pad->buf, pad->len, pad->ch);
	return (0);
}

int							ft_printf_pad_l(t_printf_padder *pad)
{
	if (pad->wide)
		ft_wstrnpad_l(pad->wbuf, pad->len, pad->wch);
	else
		ft_strnpad_l(pad->buf, pad->len, pad->ch);
	return (0);
}
