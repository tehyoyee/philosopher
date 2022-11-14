/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:18 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:12:01 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_time(void)
{
	struct timeval	time;
	long long		ms;

	if (gettimeofday(&time, NULL))
		exit_error("time error");
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	eating_time(t_person *p)
{
	long long	previous_time;

	previous_time = get_time();
	while (1)
	{
		if (get_time() - previous_time >= (long long)p->rule->time_to_eat)
			break ;
		usleep(200);
	}
}

void	sleeping_time(t_person *p)
{
	long long	previous_time;

	previous_time = get_time();
	while (1)
	{
		if (get_time() - previous_time >= (long long)p->rule->time_to_sleep)
			break ;
		usleep(200);
	}
}
