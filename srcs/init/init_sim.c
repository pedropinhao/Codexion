/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:20:06 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/02 16:07:58 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "types.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

t_status	alloc_arrays(t_sim *simulation)
{
	size_t	coders_size;
	size_t	dongles_size;

	coders_size = sizeof(t_coder) * simulation->config.number_of_coders;
	dongles_size = sizeof(t_dongle) * simulation->config.number_of_coders;
	simulation->dongles = malloc(dongles_size);
	if (!simulation->dongles)
		return (ERROR_MALLOC);
	memset(simulation->dongles, 0, dongles_size);
	simulation->coders = malloc(coders_size);
	if (!simulation->coders)
	{
		free(simulation->dongles);
		simulation->dongles = NULL;
		return (ERROR_MALLOC);
	}
	memset(simulation->coders, 0, coders_size);
	return (OK);
}

t_status	init_mutexes(t_sim *simulation)
{
	if (pthread_mutex_init(&simulation->log_mutex, NULL))
	{
		return (ERROR_MUTEX_INIT);
	}
	if (pthread_mutex_init(&simulation->state_mutex, NULL))
	{
		pthread_mutex_destroy(&simulation->log_mutex);
		return (ERROR_MUTEX_INIT);
	}
	simulation->stopped = 0;
	return (OK);
}

t_status	init_sim(t_sim *simulation)
{
	t_status	status;

	simulation->dongles = NULL;
	simulation->coders = NULL;
	simulation->started_ms = get_time();
	if (simulation->started_ms == -1)
		return (ERROR_CLOCK);
	status = init_mutexes(simulation);
	if (status != OK)
		return (status);
	status = alloc_arrays(simulation);
	if (status != OK)
	{
		destroy_mutexes(simulation);
		return (status);
	}
	status = init_dongles(simulation);
	if (status != OK)
	{
		free_arrays(simulation);
		destroy_mutexes(simulation);
		return (status);
	}
	init_coders(simulation);
	return (status);
}
