/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:34:06 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/02 15:47:21 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init/init.h"
#include "types.h"
#include "utils/utils.h"
#include <stdio.h>
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
	destroy_sim(&simulation);
	if (simulation.config.scheduler == FT_SCHED_EDF)
		printf("It's edf!\n");
	else if (simulation.config.scheduler == FT_SCHED_FIFO)
		printf("It's fifo!\n");
	return (status);
}
