/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/30 07:33:20 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/03 20:22:54 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libftprintf.h"


int			ft_printf_init(t_printf_env *env,
						   char const *format,
						   va_list args)
{
	env->code = PS_SUCCESS;
	env->format = format;
	ft_memcpy((void*)env->args, (const void*)args, sizeof(va_list));
	ft_printf_pad_init(&env->padder, env);
	env->converter = NULL;
	env->options = 0;
	env->written = 0;
	env->buffer_cap = 0;
	env->buffer = NULL;
	env->wbuffer_cap = 0;
	env->wbuffer = NULL;
	env->size_modifier = PSM_INT;
	env->arg.type = env->size_modifier;
	env->arg.value.ll = 0;
	env->arg.sign = 1;
	env->upper = 0;
	env->fd = 1;
	env->writer = ft_printf_write_console;
	env->writer_w = ft_printf_write_console_w;
	ft_memset((void*)&env->prec, 0, sizeof(t_printf_prec));
	ft_memset((void*)&env->prec.values, -1, sizeof(int) * 2);
	return (env->code);
}

int			ft_printf_restore(t_printf_env *env)
{
	env->upper = 0;
	env->size_modifier = PSM_INT;
	env->arg.type = env->size_modifier;
	env->arg.value.ll = 0;
	env->arg.sign = 1;
	env->options = 0;
	env->converter = NULL;
	memset((void*)&env->prec, 0, sizeof(t_printf_prec));
	memset((void*)&env->prec.values, -1, sizeof(int) * 2);
	return (0);
}

int			ft_printf_config(t_printf_env *env,
							 int fd,
							 t_printf_writer writer)
{
	if (fd > 0)
		env->fd = fd;
	if (writer)
		env->writer = writer;
	return (env->code);
}

int			ft_printf_reset(t_printf_env *env)
{
	(void)env;
	return (0);
}
