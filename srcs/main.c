/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:34:06 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:13:36 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	if (status != OK || (status == SIM_STOPPED))
		return (destroy_sim(&simulation), status);
	status = join_threads(&simulation);
	if (status != OK)
		return (destroy_sim(&simulation), status);
	destroy_sim(&simulation);
	return (status);
}
