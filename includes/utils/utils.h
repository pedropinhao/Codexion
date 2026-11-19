/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 16:10:57 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/19 06:12:47 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "types.h"

long		get_time(void);
t_status	get_elapsed_time(long last_compile_ms, long *result);
t_status	sleep_function(t_sim *simulation, long duration);
void		destroy_mutexes(t_sim *simulation);
void		free_arrays(t_sim *simulation);
void		destroy_dongles(t_sim *simulation, int number_dongles);
void		destroy_sim(t_sim *simulation);
void		log_state(t_sim *simulation, int coder_id, const char *message);
void		log_burnout(t_sim *simulation, int coder_id);
void		log_state(t_sim *simulation, int coder_id, const char *message);
t_status	release_dongles(t_coder *coder, long cooldown);
t_status	take_dongles(t_coder *coder);
int			simulation_is_stopped(t_sim *simulation);
void		simulation_stop_setter(t_sim *simulation);

#endif
