/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:35:25 by psilva-p          #+#    #+#             */
/*   Updated: 2026/10/29 13:30:53 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "types.h"

t_status	settings_setter(t_type type, int *base, int *offset)
{
	if (type == FT_INT)
	{
		*base = 10;
		*offset = '0';
		return (OK);
	}
	else if (type == FT_SCHEDULER)
	{
		*base = 256;
		*offset = 0;
		return (OK);
	}
	else
		return (ERROR_INVALID_TYPE);
}

int	is_allowed_char(char *allowed, char c)
{
	while (*allowed)
	{
		if (c == *allowed)
			return (1);
		allowed++;
	}
	return (0);
}

t_status	validate_arg(char *str, t_type type)
{
	int	i;

	if (!str)
		return (ERROR_NULL_POINTER);
	else if (!*str)
		return (ERROR_EMPTY_ARG);
	i = 0;
	while (str[i])
		i++;
	if (type == FT_INT && (str[0] == '-' || str[0] == '+'))
		return (ERROR_SIGNED_INT);
	if (type == FT_SCHEDULER && i > 4)
		return (ERROR_SCHEDULER);
	while (*str)
	{
		if (type == FT_INT && !(is_allowed_char(DECIMAL_BASE, *str)))
			return (ERROR_NON_INT);
		else if (type == FT_SCHEDULER && !is_allowed_char(SCHEDULER_BASE, *str))
			return (ERROR_SCHEDULER);
		str++;
	}
	return (OK);
}

t_status	push_digit(int *acc, int digit, int base)
{
	if (*acc > (INT_MAX - digit) / base)
		return (ERROR_OVERFLOW);
	*acc = (*acc * base) + digit;
	return (OK);
}

t_status	parse_arg(char *str, int *out, t_type type)
{
	int			value;
	int			base;
	int			offset;
	t_status	status;

	value = 0;
	status = validate_arg(str, type);
	if (status != OK)
		return (status);
	status = settings_setter(type, &base, &offset);
	if (status != OK)
		return (status);
	while (*str)
	{
		status = push_digit(&value, *str - offset, base);
		if (status != OK)
			return (status);
		str++;
	}
	if (type == FT_SCHEDULER && value != FT_SCHED_EDF && value != FT_SCHED_FIFO)
		return (ERROR_INVALID_SCHEDULER);
	*out = value;
	return (OK);
}
