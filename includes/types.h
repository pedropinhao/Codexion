/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 19:31:48 by psilva-p          #+#    #+#             */
/*   Updated: 2026/10/31 20:04:50 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <pthread.h>

# define FT_SCHED_EDF 6644838
# define FT_SCHED_FIFO 1718183535

typedef struct s_sim	t_sim;

typedef enum e_status
{
	OK = 0,
	ERROR_NON_INT = 1,
	ERROR_OVERFLOW = 2,
	ERROR_SCHEDULER = 3,
	ERROR_SIGNED_INT = 4,
	ERROR_EMPTY_ARG = 5,
	ERROR_NULL_POINTER = 6,
	ERROR_INVALID_TYPE = 7,
	ERROR_INVALID_SCHEDULER = 8,
	ERROR_INVALID_ARG_COUNT = 9,
	ERROR_NO_CODER = 10,
	ERROR_MALLOC = 11,
	ERROR_CLOCK = 12,
	ERROR_MONITOR_THREAD = 13,
	ERROR_MUTEX_INIT = 14,
	ERROR_COND_INIT = 15,
}	t_status;

typedef enum e_parser_type
{
	FT_INT,
	FT_SCHEDULER,
}	t_type;

typedef struct s_config
{
	int	number_of_coders;
	int	time_to_burnout;
	int	time_to_compile;
	int	time_to_debug;
	int	time_to_refactor;
	int	number_of_compiles_required;
	int	dongle_cooldown;
	int	scheduler;
}	t_config;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				*waiters;
	long			ready_at_ms;
	bool			held;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	t_sim			*sim;
	t_dongle		*left;
	t_dongle		*right;
	pthread_t		thread;
	int				compiles;
	long			last_compile_ms;
}	t_coder;

typedef struct s_sim
{
	t_config		config;
	long			started_ms;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_t		monitor_thread;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	state_mutex;
	bool			stopped;
}	t_sim;

#endif
