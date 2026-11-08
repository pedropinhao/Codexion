/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 21:34:01 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 22:18:17 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "routines/routines.h"
#include "types.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>

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
	return (OK);
}

t_status	join_threads(t_sim *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		if (pthread_join(simulation->coders[i].thread, NULL))
			return (ERROR_CODER_THREAD);
		i++;
	}
	return (OK);
}
