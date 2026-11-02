/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 12:48:29 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/02 13:37:47 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stdlib.h>

void	destroy_mutexes(t_sim *simulation)
{
	pthread_mutex_destroy(&simulation->log_mutex);
	pthread_mutex_destroy(&simulation->state_mutex);
}

void	free_arrays(t_sim *simulation)
{
	free(simulation->dongles);
	simulation->dongles = NULL;
	free(simulation->coders);
	simulation->coders = NULL;
}

void	destroy_dongles(t_sim *simulation, int number_dongles)
{
	int	i;

	i = 0;
	while (i < number_dongles)
	{
		pthread_cond_destroy(&simulation->dongles[i].cond);
		pthread_mutex_destroy(&simulation->dongles[i].mutex);
		i++;
	}
}

void	destroy_sim(t_sim *simulation)
{
	destroy_dongles(simulation, simulation->config.number_of_coders);
	free_arrays(simulation);
	destroy_mutexes(simulation);
}
