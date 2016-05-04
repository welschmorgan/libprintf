/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwelsch <mwelsch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 22:03:19 by mwelsch           #+#    #+#             */
/*   Updated: 2016/05/02 22:08:35 by mwelsch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int		main()
{
	void	*ptr;
	int		code;

	code = 0;
	ptr = &code;
	printf("test_ptr: %p\n", ptr);
	ft_printf("test_ptr: %p\n", ptr);
	return (code);
}
