/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:13 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/06 16:30:15 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pick_fork(t_person *p)
{
	if (p->id % 2)
		usleep(1000);
	sem_wait(p->rule->sem_forks);
	show_status(p->rule, "has taken a fork", p->id);
	sem_wait(p->rule->sem_forks);
	show_status(p->rule, "has taken a fork", p->id);
}

void	take_eat(t_person *p)
{
	pick_fork(p);
	p->eat_time_last = get_time();
	sem_wait(p->rule->sem_time);
	sem_post(p->rule->sem_time);
	show_status(p->rule, "is eating", p->id);
	sem_wait(p->rule->sem_person);
	p->eat_cnt++;
	sem_post(p->rule->sem_person);
	eating_time(p);
	sem_post(p->rule->sem_forks);
	sem_post(p->rule->sem_forks);
}

void	*detect(void *arg)
{
	long long	temp;
	t_person	*p;
	t_rule		*rule;

	p = arg;
	rule = p->rule;
	while (1)
	{
		if (p->eat_cnt == rule->num_must_eat)
			break ;
		temp = get_time() - p->eat_time_last;
		if (temp > (long long)rule->time_to_die)
		{
			printf("%lld %d died\n", get_time() - rule->start_time, \
				p->id + 1);
			sem_post(rule->sem_done);
			break ;
		}
		usleep(1000);
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
	return ;
}

int	end_process(t_rule *rule)
{
	destroy_sem();
	destroy_process(rule);
	free(rule->pids);
	free(rule->person);
	return (0);
}
