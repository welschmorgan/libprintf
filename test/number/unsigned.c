/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:04:43 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/08 11:11:12 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

#include "libft.h"
#include "common.h"
#include <stdio.h>
#include <limits.h>

static t_test_suite	g_main_test_suite;
t_dlist				g_list;

int		tester(const char *name, const char *fmt, ...)
{
	va_list	args;
	int		code_ft;
	int		code_lc;
	static char	buf[80] = {0};

	va_start(args, fmt);
	snprintf(buf, 80, "* %s:\n", name);
	ft_putstr(buf);
	snprintf(buf, 80, "\tLibc -> ");
	printf("%s", buf);
	code_lc = vprintf(fmt, args);
	va_end(args);
	va_start(args, fmt);
	snprintf(buf, 80, "\tLibft -> ");
	ft_putstr(buf);
	code_ft = ft_vprintf(fmt, args);
	va_end(args);
	return (code_lc != code_ft);
}

int		test_basic(t_test *test)
{
	int		code;
	void	*ptr;

	(void)test;
	ptr = &code;
	code = 0;
	code = code >= 0 ? tester("test_uint(0)", "'%u'\n", 0) : code;
	code = code >= 0 ? tester("test_uint(42)", "'%u'\n", 42) : code;
	code = code >= 0 ? tester("test_uint(UINT_MAX)", "'%u'\n", UINT_MAX) : code;
	return (code);
}

int		init(int argc, char const *argv[])
{
	init_test_suite(&g_main_test_suite, "number_unsigned.log", argc, argv);
	push_test_suite(&g_main_test_suite, "number - unsigned basic", test_basic);
	return (0);
}

int		reset(void)
{
	reset_test_suite(&g_main_test_suite);
	return (0);
}

int		run()
{
	return (run_test_suite(&g_main_test_suite));
}

int		main(int argc, char const *argv[])
{
	int		code;

	code = init(argc, argv);
	code += run();
	code += reset();
	return (code);
}
