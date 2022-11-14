/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehykim <taehykim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:30:04 by taehykim          #+#    #+#             */
/*   Updated: 2022/11/14 16:11:43 by taehykim         ###   ########.fr       */
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

void	init_sem(t_rule *rule)
{
	destroy_sem();
	rule->sem_forks = sem_open("sem_forks", O_CREAT, 0644, rule->num_philo);
	rule->sem_eat_cnt = sem_open("sem_eat_cnt", O_CREAT, 0644, 1);
	rule->sem_time = sem_open("sem_time", O_CREAT, 0644, 1);
	rule->sem_done = sem_open("sem_done", O_CREAT, 0644, 0);
	if (rule->sem_forks == SEM_FAILED || rule->sem_eat_cnt == SEM_FAILED \
	|| rule->sem_time == SEM_FAILED || rule->sem_done == SEM_FAILED)
		exit_error("semaphore error\n");
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
}

void	init_process(t_rule *rule)
{
	int	i;

	rule->pids = malloc(sizeof(int) * rule->num_philo);
	if (!rule->pids)
		exit_error("malloc error\n");
	i = 0;
	rule->start_time = get_time();
	while (i < rule->num_philo)
	{
		rule->pids[i] = fork();
		if (rule->pids[i] == -1)
			exit_error("fork error\n");
		if (rule->pids[i] == 0)
			run_process(&rule->person[i]);
		i++;
	}
}

int	init_rule(int argc, char **argv, t_rule *rule)
{
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule->num_must_eat = ft_atoi(argv[5]);
	else
		rule->num_must_eat = -1;
	if (check_args(argc, argv))
		return (-1);
	init_sem(rule);
	init_person(rule);
	init_process(rule);
	return (0);
}
