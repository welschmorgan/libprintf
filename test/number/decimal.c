/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:03:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/02 22:09:06 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <limits.h>
#include <stdio.h>

int		main()
{
	int		code;
	code = 0;
	code = code >= 0 ? ft_printf("test_dec: %d\n", 0) : code;
	code = code >= 0 ? ft_printf("test_dec(INT_MIN): %d\n", INT_MIN) : code;
	code = code >= 0 ? ft_printf("test_dec(INT_MAX): %d\n", INT_MAX) : code;
	code = code >= 0 ? ft_printf("test_dec(5 min & max): '%5.5d'\n", 42) : code;
	code = code >= 0 ? ft_printf("test_dec(5 max): '%.5d'\n", 42) : code;
	code = code >= 0 ? ft_printf("test_dec(zero pad): '%05d'\n", 42) : code;
	code = code >= 0 ? ft_printf("test_dec(zero pad & pad right): '%0-5d'\n", 42) : code;
	code = code >= 0 ? ft_printf("test_dec(show sign): '%+5d'\n", 42) : code;
	code = code >= 0 ? printf("test_dec(show sign,real): '%+5d'\n", 42) : code;
	code = code >= 0 ? ft_printf("test_dec(pad right): '%-5d'\n", 42) : code;
	return (code);
}
