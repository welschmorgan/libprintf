/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/01 21:21:36 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/02 08:33:38 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftprintf.h>
#include <libft.h>

int		test_char_extended();
int		test_string_extended();

int		main()
{
	int	code;

	code = 0;
	code += test_char_extended();
	code += test_string_extended();
	return (code);
}

int		test_char_extended()
{
	int	code;

	code = 0;
	code = code >= 0 ? ft_printf("test_char_ext('é'): %lc\n", L'é') : code;
	return (code);
}
int		test_string_extended()
{
	int		code;
	static wchar_t const	*str[] = { L"²³¹¹",
									   L"Je t\'aime mon bébé ! ♡❤♥",
									   L"äåéëþüúíóö«»áßðfghïœø¶øæœ®©b®bñµçç",
									   L"chinese string(hanzi): 汉字/漢字"
	};

	code = 0;
	code = code >= 0 ? ft_printf("test_str_ext('²³¹¹'): %ls\n", str[0]) : code;
	code = code >= 0 ? ft_printf("test_str_ext('²³¹¹'): %ls\n", str[1]) : code;
	code = code >= 0 ? ft_printf("test_str_ext('²³¹¹'): %ls\n", str[2]) : code;
	code = code >= 0 ? ft_printf("test_str_ext(chinese): %ls\n", str[3]) : code;
	return (code);
}
