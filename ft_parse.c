/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwchoi <jiwchoi@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 20:37:53 by jiwchoi           #+#    #+#             */
/*   Updated: 2021/02/07 16:27:30 by jiwchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_parse_zero_minus(const char **fmt, va_list ap, t_flag *flag)
{
	while (**fmt == '-' || **fmt == '0')
	{
		if (**fmt == '-')
			flag->minus = 1;
		else
			flag->zero = 1;
		*fmt += 1;
	}
}

void	ft_parse_width(const char **fmt, va_list ap, t_flag *flag)
{
	int	tmp;

	if (**fmt == '*' || ft_isdigit(**fmt))
	{
		if (**fmt == '*')
		{
			tmp = va_arg(ap, int);
			if (tmp < 0)
			{
				flag->minus = 1;
				tmp *= -1;
			}
			*fmt += 1;
		}
		else
			tmp = ft_atoi_printf(fmt);
	}
	flag->width = tmp;
}

void	ft_parse_precision(const char **fmt, va_list ap, t_flag *flag)
{
	if (**fmt == '*' || ft_isdigit(**fmt))
	{
		if (**fmt == '*')
		{
			flag->precision = va_arg(ap, int);
			*fmt += 1;
		}
		else
			flag->precision = ft_atoi_printf(fmt);
	}
}

#include "./libft/libft.h"
#include <stdio.h>
void	ft_parse(const char **fmt, t_flag *flag, va_list ap)
{
	ft_parse_zero_minus(fmt, ap, flag);
	ft_parse_width(fmt, ap, flag);
	if (**fmt == '.' && (*fmt)++)
		ft_parse_precision(fmt, ap, flag);
	//ft_load_data(fmt, ap);
	if (**fmt == 'd')
	{
		char *result = ft_itoa(va_arg(ap, int));
		int len = flag->precision - ft_strlen(result);
		char *pre;
		if (len)
		{
			pre = malloc(len + 1);
			ft_memset(pre, '0', len);
			pre[len] = 0;
		}
		result = ft_strjoin(pre, result);
		printf("\n-------------%s\n", result);
	}
}