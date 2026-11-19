/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:34:01 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:14:15 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "monitor/monitor.h"
#include "routines/routines.h"
#include "types.h"

t_status	init_threads(t_sim	*simulation)
{
	int	i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		if (pthread_create(&simulation->coders[i].thread,
				NULL, coder_routine, &simulation->coders[i]))
			return (ERROR_CODER_THREAD);
		i++;
	}
	if (pthread_create(&simulation->monitor_thread, NULL,
			monitor_routine, simulation))
		return (ERROR_MONITOR_THREAD);
	return (OK);
}

t_status	join_threads(t_sim *simulation)
{
	int	i;

	i = -1;
	while (++i < simulation->config.number_of_coders)
	{
		if (pthread_join(simulation->coders[i].thread, NULL))
			return (ERROR_CODER_THREAD);
	}
	if (pthread_join(simulation->monitor_thread, NULL))
		return (ERROR_MONITOR_THREAD);
	return (OK);
}
