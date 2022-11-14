/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:13 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:54 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_fork(t_person *p)
{
	if (p->id % 2)
		usleep(p->rule->time_to_eat / 2);
	sem_wait(p->rule->sem_forks);
	show_status(p->rule, "has taken a fork", p->id);
	sem_wait(p->rule->sem_forks);
	show_status(p->rule, "has taken a fork", p->id);
}

void	take_eat(t_person *p)
{
	pick_fork(p);
	sem_wait(p->rule->sem_time);
	p->eat_time_last = get_time();
	sem_post(p->rule->sem_time);
	show_status(p->rule, "is eating", p->id);
	sem_wait(p->rule->sem_eat_cnt);
	p->eat_cnt++;
	sem_post(p->rule->sem_eat_cnt);
	eating_time(p);
	sem_post(p->rule->sem_forks);
	sem_post(p->rule->sem_forks);
}

void	die_msg(t_person *p)
{
	sem_post(p->rule->sem_time);
	printf("%lld %d died\n", get_time() - p->rule->start_time, \
	p->id + 1);
	sem_post(p->rule->sem_done);
}

void	*detect(void *arg)
{
	long long	temp;
	t_person	*p;

	p = arg;
	while (1)
	{
		usleep(1000);
		sem_wait(p->rule->sem_eat_cnt);
		if (p->eat_cnt == p->rule->num_must_eat)
		{
			sem_post(p->rule->sem_eat_cnt);
			break ;
		}
		sem_post(p->rule->sem_eat_cnt);
		sem_wait(p->rule->sem_time);
		temp = get_time() - p->eat_time_last;
		if (get_time() - p->eat_time_last > (long long)p->rule->time_to_die)
		{
			die_msg(p);
			break ;
		}
		sem_post(p->rule->sem_time);
	}
	return (0);
}

void	run_process(t_person *p)
{
	pthread_t	checker_thread;

	pthread_create(&checker_thread, NULL, &detect, p);
	pthread_detach(checker_thread);
	while (1)
	{
		take_eat(p);
		if (p->eat_cnt == p->rule->num_must_eat)
			exit(0);
		show_status(p->rule, "is sleeping", p->id);
		sleeping_time(p);
		show_status(p->rule, "is thinking", p->id);
	}
}
