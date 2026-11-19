/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 16:10:38 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:13:24 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

t_status	sleep_function(t_sim *simulation, long duration_ms)
{
	long	start_ms;
	long	target_ms;
	long	now_ms;

	start_ms = get_time();
	if (start_ms < -1)
		return (ERROR_CLOCK);
	target_ms = start_ms + duration_ms;
	while (1)
	{
		if (simulation_is_stopped(simulation))
			return (SIM_STOPPED);
		now_ms = get_time();
		if (now_ms == -1)
			return (ERROR_CLOCK);
		if (now_ms >= target_ms)
			return (OK);
		usleep(100);
	}
}
