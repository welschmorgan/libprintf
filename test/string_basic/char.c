#include "libftprintf.h"
#include "libft.h"
#include <limits.h>
#include <stdio.h>

int		main()
{
	int		code;
	code = 0;
	code = code >= 0 ? ft_printf("test_char('a'): %c\n", 'a') : code;
	code = code >= 0 ? ft_printf("test_char('z'): %c\n", 'z') : code;
	code = code >= 0 ? ft_printf("test_char('0'): %c\n", '0') : code;
	code = code >= 0 ? ft_printf("test_char('9'): %c\n", '9') : code;
	return (code);
}
