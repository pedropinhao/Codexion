/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 18:43:42 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 22:25:17 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void	log_burnout(t_sim *simulation, int coder_id)
{
	long	now_ms;
	long	elapsed_time_ms;

	if (simulation_is_stopped(simulation))
		return ;
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->stopped = true;
	pthread_mutex_unlock(&simulation->state_mutex);
	pthread_mutex_lock(&simulation->log_mutex);
	now_ms = get_time();
	if (now_ms < 0)
	{
		pthread_mutex_unlock(&simulation->log_mutex);
		return ;
	}
	elapsed_time_ms = now_ms - simulation->started_ms;
	printf("%ld %i burned out\n", elapsed_time_ms,
		coder_id);
	pthread_mutex_unlock(&simulation->log_mutex);
}

void	log_state(t_sim *simulation, int coder_id, const char *message)
{
	long	now_ms;
	long	elapsed_time_ms;

	if (simulation_is_stopped(simulation))
		return ;
	pthread_mutex_lock(&simulation->log_mutex);
	now_ms = get_time();
	if (now_ms < 0)
	{
		pthread_mutex_unlock(&simulation->log_mutex);
		return ;
	}
	elapsed_time_ms = now_ms - simulation->started_ms;
	printf("%ld %d %s\n", elapsed_time_ms,
		coder_id, message);
	pthread_mutex_unlock(&simulation->log_mutex);
}
