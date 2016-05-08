/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:03:54 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/08 12:07:42 by mwelsch          ###   ########.fr       */
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

int		test_long_basic(t_test *test)
{
	int		code;

	(void)test;
	code = 0;

	code = code >= 0 ? tester("3.14, %%lf", "'%lf'\n", 3.14) : code;
	code = code >= 0 ? tester("-3.14, %%lf", "'%lf'\n", -3.14) : code;
	code = code >= 0 ? tester("3.14345, %%lf", "'%lf'\n", 3.14345) : code;
	code = code >= 0 ? tester("0.0, %%lf", "'%lf'\n", 0.0) : code;

	return (code);
}
int		test_basic(t_test *test)
{
	int		code;

	(void)test;
	code = 0;

	code = code >= 0 ? tester("3.14, %%f", "'%f'\n", 3.14) : code;
	code = code >= 0 ? tester("-3.14, %%f", "'%f'\n", -3.14) : code;
	code = code >= 0 ? tester("3.14345, %%f", "'%f'\n", 3.14345) : code;
	code = code >= 0 ? tester("0.0, %%f", "'%f'\n", 0.0) : code;

	return (code);
}

int		init(int argc, char const *argv[])
{
	init_test_suite(&g_main_test_suite, "number_float.log", argc, argv);
	push_test_suite(&g_main_test_suite, "number - float basic", test_basic);
	push_test_suite(&g_main_test_suite, "number - long float basic", test_long_basic);
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
