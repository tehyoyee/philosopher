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

#include "philo.h"

void	eat_full_check(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_philo && rule->num_must_eat && \
		rule->person[i].eat_cnt >= rule->num_must_eat)
		i++;
	if (i == rule->num_philo)
	{
		rule->eat_full++;
	}
}

void	take_fork(t_person *p)
{
	if (p->id % 2)
		usleep(100);
	if (p->id % 2)
	{
		pthread_mutex_lock(&(p->rule->fork[p->left_fork]));
		show_status(p->rule, "has taken a fork", p->id);
		pthread_mutex_lock(&(p->rule->fork[p->right_fork]));
		show_status(p->rule, "has taken a fork", p->id);
	}
	else
	{
		pthread_mutex_lock(&(p->rule->fork[p->right_fork]));
		show_status(p->rule, "has taken a fork", p->id);
		pthread_mutex_lock(&(p->rule->fork[p->left_fork]));
		show_status(p->rule, "has taken a fork", p->id);	
	}
	p->eat_time_last = get_time();
	show_status(p->rule, "is eating", p->id);
	p->eat_cnt++;
	eating_time(p);
	pthread_mutex_unlock(&(p->rule->fork[p->left_fork]));
	pthread_mutex_unlock(&(p->rule->fork[p->right_fork]));
}

void	*ft_thread(void *person)
{
	t_person	*p;

	p = person;
	while (!p->rule->death)
	{
		take_fork(p);
		if (p->rule->eat_full)
		{
			break ;
		}
		show_status(p->rule, "is sleeping", p->id);
		sleeping_time(p);
		show_status(p->rule, "is thinking", p->id);
	}
	return (0);
}

void	die_philo(t_rule *rule)
{
	int			i;
	long long	temp;

	while (!rule->eat_full)
	{
		i = 0;
		while (i < rule->num_philo)
		{
			temp = get_time() - rule->person[i].eat_time_last;
			if (temp > (long long)rule->time_to_die)
			{
				rule->death = 1;
				printf("%lld %d died\n", get_time() - rule->start_time, rule->person[i].id + 1);
				break ;
			}
			i++;
		}
		eat_full_check(rule);
		if (rule->death)
		{
			break ;
		}
	}
}

int	run_thread(t_rule *rule)
{
	int	i;

	i = 0;
	rule->start_time = get_time();
	while (i < rule->num_philo)
	{
		pthread_create(&rule->person[i].thread, NULL, \
			ft_thread, &rule->person[i]);
		i++;
	}
	die_philo(rule);
	i = 0;
	while (i < rule->num_philo)
		pthread_join(rule->person[i++].thread, NULL);
	i = 0;
	while (i < rule->num_philo)
		pthread_mutex_destroy(&rule->fork[i++]);
	pthread_mutex_destroy(&rule->fulling_eat);
	pthread_mutex_destroy(&rule->eat);
	pthread_mutex_destroy(&rule->show_status);
	free(rule->person);
	free(rule->fork);
	return (0);
}
