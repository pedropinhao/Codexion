/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:34:06 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 22:18:09 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "init/init.h"
#include "utils/utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

int	main(int ac, char **av)
{
	t_sim		simulation;
	t_status	status;

	status = init_configs(ac, av, &simulation.config);
	if (status != OK)
		return (status);
	status = init_sim(&simulation);
	if (status != OK)
		return (status);
	status = init_threads(&simulation);
	if (status != OK)
		return (destroy_sim(&simulation), status);
	usleep(2000000);
	pthread_mutex_lock(&simulation.state_mutex);
	simulation.stopped = true;
	pthread_mutex_unlock(&simulation.state_mutex);
	status = join_threads(&simulation);
	if (status != OK)
		return (destroy_sim(&simulation), status);
	destroy_sim(&simulation);
	return (status);
}
