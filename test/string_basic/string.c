/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 20:45:26 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/02 20:45:59 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		main()
{
	int		code;
	static char const	*str[] = { "test string 1" };

	code = 0;
	code = code >= 0 ? ft_printf("Hello!\n") : code;
	code = code >= 0 ? ft_printf("test_str: '%s'\n", str[0]) : code;
	code = code >= 0 ? ft_printf("test_str(8 min): '%8s'\n", str[0]) : code;
	code = code >= 0 ? ft_printf("test_str(0 min 8 max): '%.8s'\n", str[0]) : code;

	code = code >= 0 ? ft_printf("test_str(8 min 0 max): '%8.s'\n", str[0]) : code;
	code = code >= 0 ? ft_printf("test_str(8 min & max): '%8.8s'\n", str[0]) : code;
	code = code >= 0 ? ft_printf("test_str(0 min & max ): '%.s'\n", str[0]) : code;
	return (code);
}
