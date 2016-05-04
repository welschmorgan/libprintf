/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 14:58:44 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/01 22:50:29 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libftprintf.h"

int							ft_printf_flag_hash(t_printf_env *env)
{
	env->options |= PO_ALTERN;
	return (env->code);
}

int							ft_printf_flag_zero(t_printf_env *env)
{
	env->options |= PO_ZERO;
	return (env->code);
}

int							ft_printf_flag_minus(t_printf_env *env)
{
	env->options |= PO_RIGHT;
	return (env->code);
}

int							ft_printf_flag_plus(t_printf_env *env)
{
	env->options |= PO_SIGN;
	return (env->code);
}

int							ft_printf_flag_space(t_printf_env *env)
{
	env->options |= PO_BLANK;
	return (env->code);
}
