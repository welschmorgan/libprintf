/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_size_modifiers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 14:59:56 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/01 17:56:07 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int							ft_printf_size_mod_char(t_printf_env *env)
{
	env->size_modifier = PSM_CHAR;
	return (env->code);
}

int							ft_printf_size_mod_short(t_printf_env *env)
{
	env->size_modifier = PSM_SHORT;
	return (env->code);
}

int							ft_printf_size_mod_int(t_printf_env *env)
{
	env->size_modifier = PSM_INT;
	return (env->code);
}

int							ft_printf_size_mod_long(t_printf_env *env)
{
	env->size_modifier = PSM_LONG;
	return (env->code);
}

int							ft_printf_size_mod_llong(t_printf_env *env)
{
	env->size_modifier = PSM_LLONG;
	return (env->code);
}

int							ft_printf_size_mod_intmaxt(t_printf_env *env)
{
	env->size_modifier = PSM_INTMAXT;
	return (env->code);
}

int							ft_printf_size_mod_sizet(t_printf_env *env)
{
	env->size_modifier = PSM_SIZET;
	return (env->code);
}
