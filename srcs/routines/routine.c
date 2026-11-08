/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 22:59:41 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 23:29:56 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routines/routines.h"
#include "types.h"
#include "utils/utils.h"

t_status	wait_for_dongles(t_coder *coder)
{
	t_status	status;

	while (!simulation_is_stopped(coder->sim))
	{
		status = take_dongles(coder);
		if (status == OK)
			return (OK);
		if (status != DONGLE_BUSY && status != DONGLE_COOLING)
			return (status);
		if (sleep_function(coder->sim, 1) != OK)
			return (SIM_STOPPED);
	}
	return (SIM_STOPPED);
}

t_status	compile(t_coder *coder)
{
	t_status	status;

	status = wait_for_dongles(coder);
	if (status != OK)
		return (status);
	if (simulation_is_stopped(coder->sim))
	{
		release_dongles(coder, coder->sim->config.dongle_cooldown);
		return (SIM_STOPPED);
	}
	pthread_mutex_lock(&coder->sim->state_mutex);
	coder->last_compile_ms = get_time();
	pthread_mutex_unlock(&coder->sim->state_mutex);
	log_state(coder->sim, coder->id, "has taken a dongle");
	log_state(coder->sim, coder->id, "has taken a dongle");
	log_state(coder->sim, coder->id, "is compiling");
	status = sleep_function(coder->sim, coder->sim->config.time_to_compile);
	release_dongles(coder, coder->sim->config.dongle_cooldown);
	if (status != OK)
		return (status);
	pthread_mutex_lock(&coder->sim->state_mutex);
	coder->compiles++;
	pthread_mutex_unlock(&coder->sim->state_mutex);
	return (OK);
}

t_status	refactor(t_coder *coder)
{
	if (simulation_is_stopped(coder->sim))
		return (SIM_STOPPED);
	log_state(coder->sim, coder->id, "is refactoring");
	return (sleep_function(coder->sim, coder->sim->config.time_to_refactor));
}

t_status	debug(t_coder *coder)
{
	if (simulation_is_stopped(coder->sim))
		return (SIM_STOPPED);
	log_state(coder->sim, coder->id, "is debugging");
	return (sleep_function(coder->sim, coder->sim->config.time_to_debug));
}

void	*coder_routine(void *argument)
{
	t_coder		*coder;

	coder = (t_coder *)argument;
	if (coder->sim->config.number_of_coders == 1)
	{
		lone_coder_routine(coder);
		return (NULL);
	}
	while (!simulation_is_stopped(coder->sim))
	{
		if (compile(coder) != OK)
			break ;
		if (debug(coder) != OK)
			break ;
		if (refactor(coder) != OK)
			break ;
	}
	return (NULL);
}
