/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_die.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:54:01 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/07 17:54:03 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_full_check(t_rule *rule)
{
	int	i;

	i = 0;
	usleep(1000);
	pthread_mutex_lock(&rule->person_mutex[i]);
	while (i < rule->num_philo && rule->num_must_eat && \
		rule->person[i].eat_cnt >= rule->num_must_eat)
	{
		pthread_mutex_unlock(&rule->person_mutex[i]);
		pthread_mutex_lock(&rule->person_mutex[++i]);
	}
	pthread_mutex_unlock(&rule->person_mutex[i]);
	if (i == rule->num_philo)
	{
		pthread_mutex_lock(&rule->eat_cnt_mutex);
		rule->eat_full++;
		pthread_mutex_unlock(&rule->eat_cnt_mutex);
		return (-1);
	}
	return (0);
}

int	detect_person_whether_die(t_rule *rule)
{
	int			i;
	long long	temp;

	i = 0;
	while (i < rule->num_philo)
	{
		usleep(1000);
		pthread_mutex_lock(&rule->time);
		temp = get_time() - rule->person[i].eat_time_last;
		pthread_mutex_unlock(&rule->time);
		if (temp > (long long)rule->time_to_die)
		{
			pthread_mutex_lock(&rule->death_mutex);
			rule->death++;
			pthread_mutex_unlock(&rule->death_mutex);
			printf("%lld %d died\n", get_time() - rule->start_time, \
				rule->person[i].id + 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	die_philo(t_rule *rule)
{
	while (1)
	{
		if (detect_person_whether_die(rule))
			break ;
		if (eat_full_check(rule))
			break ;
	}
}
