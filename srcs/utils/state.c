/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 23:41:16 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:13:08 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"

int	simulation_is_stopped(t_sim *simulation)
{
	int	stopped;

	pthread_mutex_lock(&simulation->state_mutex);
	stopped = simulation->stopped;
	pthread_mutex_unlock(&simulation->state_mutex);
	return (stopped);
}

void	simulation_stop_setter(t_sim *simulation)
{
	pthread_mutex_lock(&simulation->state_mutex);
	simulation->stopped = true;
	pthread_mutex_unlock(&simulation->state_mutex);
}
