/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:03:54 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/07 19:24:21 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include <stdio.h>

int		test_float(char const *name,
				   char const *fmt,
				   float f)
{
	int	code;
	static char	buf[255] = {0};

	code = 0;
	ft_strcpy(buf + code, "test_float(");
	code = ft_strlen(buf);
	ft_strcpy(buf + code, name);
	code = ft_strlen(buf);
	ft_strcpy(buf + code, "): ");
	code = ft_strlen(buf);
	ft_strcpy(buf + code, fmt);
	code = ft_strlen(buf);
	ft_strcpy(buf + code, "\n");
	code = ft_strlen(buf);
	code = ft_printf(buf, f);
	printf("\tlibc -> ");
	code = (code != printf(buf, f));
	return (code);
}
int		main()
{
	int		code;
	code = 0;
	code = code >= 0 ? test_float("3.14, %%f", "%f", 3.14) : code;
	code = code >= 0 ? test_float("-3.14, %%f", "%f", -3.14) : code;
	code = code >= 0 ? test_float("3.14345, %%f", "%f", 3.14345) : code;
	code = code >= 0 ? test_float("0.0, %%f", "%f", 0.0) : code;

	code = code >= 0 ? test_float("3.14, %%Lf", "%Lf", 3.14) : code;
	code = code >= 0 ? test_float("-3.14, %%Lf", "%Lf", -3.14) : code;
	code = code >= 0 ? test_float("3.14345, %%Lf", "%Lf", 3.14345) : code;
	code = code >= 0 ? test_float("0.0, %%Lf", "%Lf", 0.0) : code;
	return (code);
}
