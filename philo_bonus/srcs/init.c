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

#include "philo_bonus.h"

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

void	init_person(t_rule *rule_)
{
	int	i;

	i = 0;
	rule_->person = malloc(sizeof(t_person) * rule_->num_philo);
	if (!rule_->person)
		exit_error("malloc error\n");
	while (i < rule_->num_philo)
	{
		rule_->person[i].id = i;
		rule_->person[i].eat_cnt = 0;
		rule_->person[i].rule = rule_;
		rule_->person[i].eat_time_last = get_time();
		i++;
	}
	return (0);
}

void	init_sem(t_rule *rule)
{
	destroy_sem()

	rule->sem_forks = sem_open("sem_forks", O_CREAT, 0644, rule->num_philo);
	rule->sem_person = sem_open("sem_person", O_CREAT, 0644, 1);
	rule->sem_eat_cnt = sem_open("sem_eat_cnt", O_CREAT, 0644, 1);
	rule->sem_death_cnt = sem_open("sem_death_cnt", O_CREAT, 0644, 1);
	rule->sem_time = sem_open("sem_time", O_CREAT, 0644, 1);
	if (rule->sem_forks == SEM_FAILED || rule->sem_person == SEM_FAILED \
		rule->sem_eat_cnt == SEM_FAILED || rule->sem_death_cnt == SEM_FAILED \
		rule->sem_time == SEM_FAILED)
		exit_error("semaphore error\n");
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
	init_sem(rule);
	init_person(rule);
	return (0);
}
