/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 12:19:12 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/02 13:03:27 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "types.h"
#include "utils/utils.h"

t_status	init_dongle(t_dongle *dongle)
{
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (ERROR_MUTEX_INIT);
	if (pthread_cond_init(&dongle->cond, NULL))
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (ERROR_COND_INIT);
	}
	dongle->waiters = NULL;
	dongle->ready_at_ms = 0;
	dongle->held = 0;
	return (OK);
}

t_status	init_dongles(t_sim *simulation)
{
	int			i;
	t_status	status;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		status = init_dongle(&simulation->dongles[i]);
		if (status != OK)
		{
			destroy_dongles(simulation, i);
			return (status);
		}
		i++;
	}
	return (OK);
}
