/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 23:00:08 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 23:12:12 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINES_H
# define ROUTINES_H

# include "types.h"
# include "utils/utils.h"

t_status	wait_for_dongles(t_coder *coder);
t_status	compile(t_coder *coder);
t_status	refactor(t_coder *coder);
t_status	debug(t_coder *coder);
void		*coder_routine(void *argument);
void		lone_coder_routine(t_coder *coder);

#endif
