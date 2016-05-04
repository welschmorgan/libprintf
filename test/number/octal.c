/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:05:02 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 21:14:21 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main()
{
	int		code;
	code = 0;
	code = code >= 0 ? ft_printf("test_oct(0): %o\n", 0) : code;
	code = code >= 0 ? ft_printf("test_oct(42): %o\n", 42) : code;
	code = code >= 0 ? ft_printf("test_oct(42, alt): %#o\n", 42) : code;
	return (code);
}
