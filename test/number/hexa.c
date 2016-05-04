/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:04:22 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 21:13:10 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main()
{
	int		code;

	code = 0;
	code = code >= 0 ? ft_printf("test_hexa(0x0, simple): %x\n", 0) : code;
	code = code >= 0 ? ft_printf("test_hexa(0xf, simple): %x\n", 15) : code;
	code = code >= 0 ? ft_printf("test_hexa(deadbeef, simple): %x\n", 0xdeadbeef) : code;
	code = code >= 0 ? ft_printf("test_hexa(DEADBEEF, upper): %X\n", 0xdeadbeef) : code;
	code = code >= 0 ? ft_printf("test_hexa(deadbeef, alt.): %#x\n", 0xdeadbeef) : code;
	code = code >= 0 ? ft_printf("test_hexa(deadbeef): alt. upper %#X\n", 0xdeadbeef) : code;
	return (code);
}
