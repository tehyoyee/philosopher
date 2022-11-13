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

int	pick_fork(t_person *p)
{
	if (p->id % 2)
		usleep(p->rule->time_to_eat / 2);
	// pthread_mutex_lock(&(p->rule->fork[p->left_fork]));
	sem_wait("fork[%d]", p->left_fork);
	show_status(p->rule, "has taken a fork", p->id);
	if (p->right_fork == p->left_fork)
	{
		pthread_mutex_unlock(&(p->rule->fork[p->left_fork]));
		return (-1);
	}
	pthread_mutex_lock(&(p->rule->fork[p->right_fork]));
	show_status(p->rule, "has taken a fork", p->id);
	return (0);
}

int	take_eat(t_person *p)
{
	if (pick_fork(p))
		return (-1);
	pthread_mutex_lock(&p->rule->time);
	p->eat_time_last = get_time();
	pthread_mutex_unlock(&p->rule->time);
	show_status(p->rule, "is eating", p->id);
	pthread_mutex_lock(&p->rule->person_mutex[p->id]);
	p->eat_cnt++;
	pthread_mutex_unlock(&p->rule->person_mutex[p->id]);
	eating_time(p);
	pthread_mutex_unlock(&(p->rule->fork[p->left_fork]));
	pthread_mutex_unlock(&(p->rule->fork[p->right_fork]));
	return (0);
}

void	*ft_thread(void *person)
{
	t_person	*p;

	p = person;
	pthread_mutex_lock(&p->rule->death_mutex);
	while (!p->rule->death)
	{
		pthread_mutex_unlock(&p->rule->death_mutex);
		if (take_eat(p))
			return (0);
		pthread_mutex_lock(&p->rule->eat_cnt_mutex);
		if (p->rule->eat_full)
		{
			pthread_mutex_unlock(&p->rule->eat_cnt_mutex);
			break ;
		}
		pthread_mutex_unlock(&p->rule->eat_cnt_mutex);
		show_status(p->rule, "is sleeping", p->id);
		sleeping_time(p);
		show_status(p->rule, "is thinking", p->id);
		pthread_mutex_lock(&p->rule->death_mutex);
	}
	pthread_mutex_unlock(&p->rule->death_mutex);
	return (0);
}

int	end_thread(t_rule *rule)
{
	int	i;

	i = 0;
	while (i < rule->num_philo)
		pthread_join(rule->person[i++].thread, NULL);
	i = 0;
	while (i < rule->num_philo)
	{
		pthread_mutex_destroy(&rule->fork[i]);
		pthread_mutex_destroy(&rule->person_mutex[i++]);
	}
	pthread_mutex_destroy(&rule->eat_cnt_mutex);
	pthread_mutex_destroy(&rule->death_mutex);
	pthread_mutex_destroy(&rule->time);
	free(rule->person);
	free(rule->fork);
	free(rule->person_mutex);
	return (0);
}

int	run_thread(t_rule *rule)
{
	int	i;

	i = 0;
	rule->start_time = get_time();
	while (i < rule->num_philo)
	{
		if (pthread_create(&rule->person[i].thread, NULL, \
			ft_thread, &rule->person[i]))
			return (-1);
		i++;
	}
	die_philo(rule);
	end_thread(rule);
	return (0);
}
