/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 15:00:13 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:11:11 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor/monitor.h"
#include "utils/utils.h"
#include "types.h"

static void	data_retrieval(t_coder *coder, long *last_compile_ms,
	int *nb_compiles)
{
	pthread_mutex_lock(&coder->sim->state_mutex);
	*nb_compiles = coder->compiles;
	*last_compile_ms = coder->last_compile_ms;
	pthread_mutex_unlock(&coder->sim->state_mutex);
}

static t_status	check_coder(t_sim *simulation, int index, long current_time,
	int *done)
{
	long	last_compile_ms;
	long	elapsed_time;
	int		nb_compiles;

	data_retrieval(&simulation->coders[index], &last_compile_ms, &nb_compiles);
	elapsed_time = current_time - last_compile_ms;
	if (nb_compiles >= simulation->config.number_of_compiles_required)
		*done += 1;
	if (elapsed_time > simulation->config.time_to_burnout)
		return (BURNOUT_DETECTED);
	return (OK);
}

static int	scan_coders(t_sim *simulation, long now_ms, int *coders_done)
{
	int	i;
	int	id;

	id = 0;
	i = -1;
	while (++i < simulation->config.number_of_coders)
		if (check_coder(simulation, i, now_ms,
				coders_done) == BURNOUT_DETECTED && id == 0)
			id = simulation->coders[i].id;
	return (id);
}

static t_status	monitor_pass(t_sim *simulation)
{
	long		now_ms;
	int			coders_done;
	int			burnout_coder_id;

	if (simulation_is_stopped(simulation))
		return (SIM_STOPPED);
	coders_done = 0;
	burnout_coder_id = 0;
	now_ms = get_time();
	if (now_ms < 0)
		return (simulation_stop_setter(simulation), ERROR_CLOCK);
	burnout_coder_id = scan_coders(simulation, now_ms, &coders_done);
	if (coders_done >= simulation->config.number_of_coders)
		return (simulation_stop_setter(simulation), SIM_COMPLETED);
	if (burnout_coder_id != 0)
		return (log_burnout(simulation, burnout_coder_id), BURNOUT_DETECTED);
	return (OK);
}

void	*monitor_routine(void *argument)
{
	t_sim		*simulation;
	t_status	status;

	simulation = (t_sim *)argument;
	status = OK;
	while (1)
	{
		status = monitor_pass(simulation);
		if (status != OK)
			return (NULL);
		sleep_function(simulation, 1);
	}
}
