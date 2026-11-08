/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lone_coder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/08 22:49:39 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 22:58:22 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routines/routines.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stdbool.h>

void	lone_coder_routine(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->mutex);
	coder->left->held = true;
	pthread_mutex_unlock(&coder->left->mutex);
	log_state(coder->sim, coder->id, "has taken a dongle");
	while (!simulation_is_stopped(coder->sim))
		sleep_function(coder->sim, 1);
}
