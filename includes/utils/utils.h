/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 16:10:57 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/02 13:38:17 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <sys/time.h>
# include "types.h"

long	get_time(void);
void	destroy_mutexes(t_sim *simulation);
void	free_arrays(t_sim *simulation);
void	destroy_dongles(t_sim *simulation, int number_dongles);
void	destroy_sim(t_sim *simulation);

#endif
