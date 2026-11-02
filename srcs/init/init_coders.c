/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 11:12:43 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/01 12:27:45 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "init/init.h"

void	init_coder(int id, t_coder *coder, t_sim *simulation)
{
	int	n;
	int	coder_index;

	coder_index = id - 1;
	n = simulation->config.number_of_coders;
	coder->id = id;
	coder->sim = simulation;
	coder->left = &simulation->dongles[coder_index];
	coder->right = &simulation->dongles[(coder_index + 1) % n];
	coder->compiles = 0;
	coder->last_compile_ms = simulation->started_ms;
}

void	init_coders(t_sim *simulation)
{
	int	i;

	i = 0;
	while (i < simulation->config.number_of_coders)
	{
		init_coder(i + 1, &simulation->coders[i], simulation);
		i++;
	}
}
