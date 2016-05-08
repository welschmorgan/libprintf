/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:03:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/08 12:12:08 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft.h"
#include "common.h"
#include <limits.h>
#include <stdio.h>

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

int		test_limits(t_test *test)
{
	int		code;

	(void)test;
	code = 0;
	code = code >= 0 ? tester("test_dec(%%d, 0)", "'%d'\n", 0) : code;
	code = code >= 0 ? tester("test_dec(%%d, INT_MIN)", "'%d'\n", INT_MIN) : code;
	code = code >= 0 ? tester("test_dec(%%d, INT_MAX)", "'%d'\n", INT_MAX) : code;
	return (code);
}

int		test_padding(t_test *test)
{
	int	code;

	(void)test;
	code = 0;
	code = code >= 0 ? tester("test_dec(5 min & max)", "'%5.5d'\n", 42) : code;
	code = code >= 0 ? tester("test_dec(5 max)", "'%.5d'\n", 42) : code;
	code = code >= 0 ? tester("test_dec(zero pad)", "'%05d'\n", 42) : code;
	code = code >= 0 ? tester("test_dec(zero pad & pad right)", "'%0-5d'\n", 42) : code;
	code = code >= 0 ? tester("test_dec(show sign)", "'%+5d'\n", 42) : code;
	code = code >= 0 ? tester("test_dec(pad right)", "'%-5d'\n", 42) : code;
	return (code);
}

int		init(int argc, char const *argv[])
{
	init_test_suite(&g_main_test_suite, "number_decimal.log", argc, argv);
	push_test_suite(&g_main_test_suite, "number - decimal limits", test_limits);
	push_test_suite(&g_main_test_suite, "number - decimal padding", test_padding);
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
