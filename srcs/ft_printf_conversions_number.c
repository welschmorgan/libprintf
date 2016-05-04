/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conversions_number.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 14:57:09 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 21:24:44 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"

int							ft_printf_conv_decimal(t_printf_env *env)
{
	if (env->upper)
		env->size_modifier = PSM_LONG;
	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	ft_printf_write_number_pad(env, &env->arg, 10, NULL);
	return (env->code);
}

int							ft_printf_conv_binary(t_printf_env *env)
{
	env->options |= PO_UNSIGNED;
	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	ft_printf_write_number_pad(env, &env->arg, 2, NULL);
	return (env->code);
}

int							ft_printf_conv_octal(t_printf_env *env)
{
	char const				*prefix;

	env->options |= PO_UNSIGNED;
	if (env->upper)
		env->size_modifier = PSM_LONG;
	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	prefix = NULL;
	if ((env->options & PO_ALTERN) != 0 && env->arg.value.l)
		prefix = "0";
	ft_printf_write_number_pad(env, &env->arg, 8, prefix);
	return (env->code);
}

int							ft_printf_conv_unsigned(t_printf_env *env)
{
	env->options |= PO_UNSIGNED;
	if (env->upper)
		env->size_modifier = PSM_LONG;
	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	ft_printf_write_number_pad(env, &env->arg, 10, NULL);
	return (env->code);
}

int							ft_printf_conv_hexa(t_printf_env *env)
{
	char const				*prefix;

	prefix = NULL;
	env->options |= PO_UNSIGNED;
	  env->size_modifier = PSM_LONG;
	ft_printf_arg_get(env, env->size_modifier, &env->arg);
	if ((env->options & PO_ALTERN) != 0)
		prefix = (env->upper ? "0X" : "0x");
	ft_printf_write_number_pad(env, &env->arg, 16, prefix);
	return (env->code);
}
