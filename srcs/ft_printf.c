/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 07:42:15 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 20:24:34 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"
#include <stdio.h>


char const				*g_printf_status[PS_COUNT + 1] = {
	"success",
	"buffer too small",
	"invalid conversion specifier",
	"invalid flag specifier",
	"invalid size modifier",
	"invalid precision specifier",
	"unknown status code"
};

char const				*ft_printf_status(t_printf_status status)
{
	return (g_printf_status[status]);
}

int			ft_printf(const char *format, ...)
{
	int		code;
	va_list	args;

	va_start(args, format);
	code = ft_vprintf(format, args);
	va_end(args);
	return (code);
}

int			ft_printf_precision(t_printf_env *env)
{
	int				len;

	memset((void*)&env->prec, 0, sizeof(t_printf_prec));
	memset((void*)&env->prec.values, -1, sizeof(int) * 2);
	if (*env->format != '.' && !ft_isdigit(*env->format))
		return (env->code);
	if (*env->format != '.' && ft_isdigit(*env->format))
		env->prec.starts[0] = env->format;
	while (*env->format == '.' || ft_isdigit(*env->format))
	{
		if (*env->format == '.')
		{
			if (env->prec.starts[1])
				break ;
			env->format++;
			env->prec.starts[1] = env->format;
		}
		env->format++;
	}
	if (env->prec.starts[0])
	{
		if (env->prec.starts[1])
			len = env->prec.starts[1] - env->prec.starts[0];
		else
			len = env->format - env->prec.starts[0];
		ft_strncpy(env->prec.parts[0], env->prec.starts[0], len < 32 ? len : 32);
		env->prec.values[0] = ft_atoi(env->prec.parts[0]);
		if (env->prec.values[0] < 0)
			env->code = PS_INVALID_PREC;
	}
	if (FTPRINTF_SUCCESS(env->code) && env->prec.starts[1])
	{
		len = env->format - env->prec.starts[1];
		ft_strncpy(env->prec.parts[1], env->prec.starts[1], len < 32 ? len : 32);
		env->prec.values[1] = ft_atoi(env->prec.parts[1]);
		if (env->prec.values[1] < 0)
			env->code = PS_INVALID_PREC;
	}
	return (env->code);
}

int			ft_printf_preprocessor(t_printf_env *env)
{
	t_printf_trigger const	*pflag;
	t_printf_trigger const	*psize_mod;

	ft_printf_restore(env);
	while (42)
	{
		pflag = ft_printf_find_flag(env->format);
		if (!pflag)
			break ;
		/*printf("Found flag: %s\n", pflag->name);*/
		env->format += ft_strlen(pflag->name);
		env->code = pflag->func(env);
	}
	psize_mod = ft_printf_find_size_mod(env->format);
	if (FTPRINTF_SUCCESS(env->code))
		env->code = ft_printf_precision(env);
	if (FTPRINTF_SUCCESS(env->code) && psize_mod)
	{
		env->format += ft_strlen(psize_mod->name);
		env->code = psize_mod->func(env);
	}
	return (env->code);
}

int			ft_printf_processor(t_printf_env *env)
{
	env->converter = ft_printf_find_conv(env->format);
	if (env->converter)
	{
		env->format += ft_strlen(env->converter->name);
		env->upper = ft_strisupper(env->converter->name);
		env->code = env->converter->func(env);
	}
	return (env->code);
}

int			ft_printf_loop(t_printf_env *env)
{
	int		code;

	code = env->code;
	while (FTPRINTF_SUCCESS(code)
		   && env
		   && env->format && *env->format)
	{
		if (*env->format == '%')
		{
			env->format++;
			if (*env->format == '%')
			{
				code = ft_printf_write(env, env->format, 1);
				if (!FTPRINTF_SUCCESS(code))
					break ;
				env->format++;
			}
			else
			{
				code = ft_printf_preprocessor(env);
				if (!FTPRINTF_SUCCESS(code))
					break ;
				code = ft_printf_processor(env);
				if (!FTPRINTF_SUCCESS(code))
					break ;
			}
		}
		else
		{
			code = ft_printf_write(env, env->format, 1);
			if (!FTPRINTF_SUCCESS(code))
				break ;
			env->format++;
		}
	}
	return (env->code);
}

int			ft_vprintf(const char *format,
					   va_list ap)
{
	t_printf_env	env;

	if (!format)
		return (-1);
	ft_printf_init(&env, format, ap);
	ft_printf_config(&env, 1, ft_printf_write_console);
	ft_printf_loop(&env);
	ft_printf_reset(&env);
	/*ft_putendl(ft_printf_status(env.code));*/
	return (env.written);
}
