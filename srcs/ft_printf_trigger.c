/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_trigger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 08:56:57 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/07 14:11:15 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"


static t_printf_trigger const	g_printf_convs[PC_COUNT + 1] = {
	{PC_STRING_LO, "s", ft_printf_conv_string},
	{PC_STRING_UP, "S", ft_printf_conv_string},
	{PC_POINTER_LO, "p", ft_printf_conv_pointer},
	{PC_FLOAT_LO, "f", ft_printf_conv_float},
	{PC_FLOAT_UP, "F", ft_printf_conv_float},
	{PC_DECIMAL_LO, "d", ft_printf_conv_decimal},
	{PC_DECIMAL_UP, "D", ft_printf_conv_decimal},
	{PC_INTEGER_LO, "i", ft_printf_conv_decimal},
	{PC_OCTAL_LO, "o", ft_printf_conv_octal},
	{PC_OCTAL_UP, "O", ft_printf_conv_octal},
	{PC_BINARY_LO, "b", ft_printf_conv_binary},
	{PC_BINARY_UP, "B", ft_printf_conv_binary},
	{PC_UNSIGNED_LO, "u", ft_printf_conv_unsigned},
	{PC_UNSIGNED_UP, "U", ft_printf_conv_unsigned},
	{PC_HEXA_LO, "x", ft_printf_conv_hexa},
	{PC_HEXA_UP, "X", ft_printf_conv_hexa},
	{PC_CHAR_LO, "c", ft_printf_conv_char},
	{PC_CHAR_UP, "C", ft_printf_conv_char},
	{PC_COUNT, "", NULL}
};

static t_printf_trigger const	g_printf_flags[PF_COUNT + 1] = {
	{PF_HASH, "#", ft_printf_flag_hash},
	{PF_ZERO, "0", ft_printf_flag_zero},
	{PF_MINUS, "-", ft_printf_flag_minus},
	{PF_PLUS, "+", ft_printf_flag_plus},
	{PF_SPACE, " ", ft_printf_flag_space},
	{PF_COUNT, "", NULL},
};

static t_printf_trigger const	g_printf_size_mods[PSM_COUNT + 1] = {
	{PSM_CHAR, "hh", ft_printf_size_mod_char},
	{PSM_SHORT, "h", ft_printf_size_mod_short},
	{PSM_INT, "", ft_printf_size_mod_int},
	{PSM_FLOAT, "", NULL},
	{PSM_DOUBLE, "", NULL},
	{PSM_LDOUBLE, "", NULL},
	{PSM_LONG, "l", ft_printf_size_mod_long},
	{PSM_LLONG, "ll", ft_printf_size_mod_llong},
	{PSM_INTMAXT, "j", ft_printf_size_mod_intmaxt},
	{PSM_SIZET, "z", ft_printf_size_mod_sizet},
	{PF_COUNT, "", NULL},
};

t_printf_trigger const		*ft_printf_find_trigger(char const *name,
													t_printf_trigger const *haystack,
													size_t n)
{
	t_printf_trigger const	*conv;
	int						len;
	int						i;

	if (!haystack)
		return (NULL);
	i = 0;
	while (i < (int)n)
	{
		conv = &haystack[i];
		len = ft_strlen(conv->name);
		if (len)
		{
			len = len < FTPRINTF_TRIGGER_MAX
				? len
				: FTPRINTF_TRIGGER_MAX;
			if (!ft_strncmp(conv->name, name, len))
				break ;
		}
		i++;
	}
	conv = i == (int)n ? NULL : conv;
	if (conv && conv->name[0])
	{
		/*ft_putstr("Found trigger ");
		  ft_putendl(conv->name);*/
	}
	return (conv);
}

t_printf_trigger const		*ft_printf_find_conv(char const *name)
{
	return (ft_printf_find_trigger(name, g_printf_convs, PC_COUNT));
}

t_printf_trigger const		*ft_printf_find_flag(char const *name)
{
	return (ft_printf_find_trigger(name, g_printf_flags, PF_COUNT));
}
t_printf_trigger const		*ft_printf_find_size_mod(char const *name)
{
	return (ft_printf_find_trigger(name, g_printf_size_mods, PSM_COUNT));
}
