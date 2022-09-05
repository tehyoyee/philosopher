#include "philo.h"

int	check_args(t_rule *rule)
{
	if (rule->num_philo < 2 || rule->num_philo > 100 || \
		rule->time_to_die < 60 || rule->time_to_eat < 60 \
		|| rule->time_to_sleep < 60)
		return (-1);
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
		rule_->person[i].time = 0;
		rule_->person[i].eat_time = 0;
		rule_->person[i].rule = rule_;
		i++;
	}
	return (0);
}

int	init_mutex(t_rule *rule)
{
	int	i;

	i = 0;
	rule->fork = malloc(sizeof(pthread_mutex_t) * rule->num_philo);
	if (!rule->fork)
		return (-1);
	while (i < rule->num_philo)
	{
		if (pthread_mutex_init(&rule->fork[i], NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&rule->show_status, NULL))
		return (-1);
	if (pthread_mutex_init(&rule->eat, NULL))
		return (-1);
	return (0);
}

int	init_rule(int argc, char **argv, t_rule *rule)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0)
			return (-1);
		i++;
	}
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule->num_must_eat = ft_atoi(argv[5]);
	if (check_args(rule))
		return (-1);
	if (init_mutex(rule))
		return (-1);
	if (init_person(rule))
		return (-1);
	return (0);
}