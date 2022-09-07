/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:04 by taehykim          #+#    #+#             */
/*   Updated: 2022/09/06 16:30:05 by taehykim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (-1);
		i++;
	}
	return (0);
}

int	init_person(t_rule *rule_)
{
	int	i;

	i = 0;
	rule_->person = malloc(sizeof(t_person) * rule_->num_philo);
	if (!rule_->person)
		return (-1);
	while (i < rule_->num_philo)
	{
		rule_->person[i].id = i;
		rule_->person[i].left_fork = i;
		rule_->person[i].right_fork = (i + 1) % rule_->num_philo;
		rule_->person[i].eat_cnt = 0;
		rule_->person[i].rule = rule_;
		rule_->person[i].eat_time_last = get_time();
		i++;
	}
	return (0);
}

int	allocate_mutex(t_rule *rule)
{
	rule->fork = malloc(sizeof(pthread_mutex_t) * rule->num_philo);
	if (!rule->fork)
		return (-1);
	rule->person_mutex = malloc(sizeof(pthread_mutex_t) * rule->num_philo);
	if (!rule->person_mutex)
	{
		ft_free_mutex(rule);
		return (-1);
	}
	return (0);
}

int	init_mutex(t_rule *rule)
{
	int	i;

	if (allocate_mutex(rule))
		return (-1);
	i = 0;
	while (i < rule->num_philo)
	{
		if (pthread_mutex_init(&rule->fork[i], NULL))
			return (-1);
		if (pthread_mutex_init(&rule->person_mutex[i], NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&rule->eat_cnt_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&rule->death_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&rule->time, NULL))
		return (-1);
	return (0);
}

int	init_rule(int argc, char **argv, t_rule *rule)
{
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	rule->death = 0;
	rule->eat_full = 0;
	if (argc == 6)
		rule->num_must_eat = ft_atoi(argv[5]);
	else
		rule->num_must_eat = 0;
	if (check_args(argc, argv))
		return (-1);
	if (init_mutex(rule) || init_person(rule))
	{
		ft_free_mutex(rule);
		return (-1);
	}
	return (0);
}
