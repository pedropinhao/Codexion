/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psilva-p <psilva-p@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 18:52:00 by psilva-p          #+#    #+#             */
/*   Updated: 2026/11/08 22:50:12 by psilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "utils/utils.h"

static void	lock_dongles(t_coder *coder)
{
	if (coder->left == coder->right)
		pthread_mutex_lock(&coder->left->mutex);
	else if (coder->left < coder->right)
	{
		pthread_mutex_lock(&coder->left->mutex);
		pthread_mutex_lock(&coder->right->mutex);
	}
	else
	{
		pthread_mutex_lock(&coder->right->mutex);
		pthread_mutex_lock(&coder->left->mutex);
	}
}

static void	unlock_dongles(t_coder *coder)
{
	if (coder->left == coder->right)
		pthread_mutex_unlock(&coder->left->mutex);
	else if (coder->left < coder->right)
	{
		pthread_mutex_unlock(&coder->left->mutex);
		pthread_mutex_unlock(&coder->right->mutex);
	}
	else
	{
		pthread_mutex_unlock(&coder->right->mutex);
		pthread_mutex_unlock(&coder->left->mutex);
	}
}

t_status	release_dongles(t_coder *coder, long cooldown)
{
	long		now_ms;
	t_dongle	*left;
	t_dongle	*right;

	left = coder->left;
	right = coder->right;
	lock_dongles(coder);
	now_ms = get_time();
	left->held = false;
	left->ready_at_ms = now_ms + cooldown;
	right->held = false;
	right->ready_at_ms = now_ms + cooldown;
	unlock_dongles(coder);
	return (OK);
}

t_status	take_dongles(t_coder *coder)
{
	long		now_ms;

	if (coder->left == coder->right)
		return (DONGLE_BUSY);
	lock_dongles(coder);
	now_ms = get_time();
	if (now_ms < 0)
	{
		unlock_dongles(coder);
		return (ERROR_CLOCK);
	}
	if (coder->left->held || coder->right->held)
	{
		unlock_dongles(coder);
		return (DONGLE_BUSY);
	}
	if (now_ms < coder->left->ready_at_ms || now_ms < coder->right->ready_at_ms)
	{
		unlock_dongles(coder);
		return (DONGLE_COOLING);
	}
	coder->left->held = true;
	coder->right->held = true;
	unlock_dongles(coder);
	return (OK);
}
