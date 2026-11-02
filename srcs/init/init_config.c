/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:53:55 by psilva-p          #+#    #+#             */
/*   Updated: 2026/10/29 13:26:48 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "parser/parser.h"
#include "types.h"

t_status	init_numeric(char **av, t_config *config)
{
	t_status	status;

	status = parse_arg(av[1], &config->number_of_coders, FT_INT);
	if (status == OK)
		status = parse_arg(av[2], &config->time_to_burnout, FT_INT);
	if (status == OK)
		status = parse_arg(av[3], &config->time_to_compile, FT_INT);
	if (status == OK)
		status = parse_arg(av[4], &config->time_to_debug, FT_INT);
	if (status == OK)
		status = parse_arg(av[5], &config->time_to_refactor, FT_INT);
	if (status == OK)
		status = parse_arg(av[6], &config->number_of_compiles_required, FT_INT);
	if (status == OK)
		status = parse_arg(av[7], &config->dongle_cooldown, FT_INT);
	return (status);
}

t_status	init_scheduler(char *av, t_config *config)
{
	return (parse_arg(av, &config->scheduler, FT_SCHEDULER));
}

t_status	validate_config(t_config *config)
{
	if (config->number_of_coders == 0)
		return (ERROR_NO_CODER);
	return (OK);
}

t_status	init_configs(int ac, char **av, t_config *config)
{
	t_status	status;

	if (ac != 9)
		return (ERROR_INVALID_ARG_COUNT);
	status = OK;
	status = init_numeric(av, config);
	if (status == OK)
		status = init_scheduler(av[8], config);
	if (status == OK)
		status = validate_config(config);
	return (status);
}
