/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 16:10:38 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 23:30:18 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_status	sleep_function(t_sim *simulation, long duration)
{
	long	remaining;
	long	sleep_time;
	bool	stopped;

	remaining = duration;
	while (remaining > 0)
	{
		pthread_mutex_lock(&simulation->state_mutex);
		stopped = simulation->stopped;
		pthread_mutex_unlock(&simulation->state_mutex);
		if (stopped)
			return (SIM_STOPPED);
		sleep_time = remaining;
		if (sleep_time > 1)
			sleep_time = 1;
		usleep(sleep_time * 1000);
		remaining -= sleep_time;
	}
	return (OK);
}
