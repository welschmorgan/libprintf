/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:04:43 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/02 22:04:55 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main()
{
	int		code;
	code = 0;
	code = code >= 0 ? ft_printf("test_uint(0): %u\n", 0) : code;
	code = code >= 0 ? ft_printf("test_uint(42): %u\n", 42) : code;
	return (code);
}
