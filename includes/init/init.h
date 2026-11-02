/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:54:18 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/01 12:56:57 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include "types.h"

t_status	init_numeric(char **av, t_config *config);
t_status	init_scheduler(char *av, t_config *config);
t_status	validate_config(t_config *config);
t_status	init_configs(int ac, char **av, t_config *config);
t_status	alloc_arrays(t_sim *simulation);
t_status	init_mutexes(t_sim *simulation);
t_status	init_sim(t_sim *simulation);
t_status	init_dongle(t_dongle	*dongle);
t_status	init_dongles(t_sim *simulation);
void		init_coder(int id, t_coder *coder, t_sim *simulation);
void		init_coders(t_sim *simulation);

#endif
