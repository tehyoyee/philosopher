#include "philo.h"

void	init_rule(int argc, char **argv, t_rule *rule)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (atoi(argv[i]) <= 0)
			exit_error("incorrect argument");
		i++;
	}
	rule->num_philo = ft_atoi(argv[1]);
	rule->time_to_die = ft_atoi(argv[2]);
	rule->time_to_eat = ft_atoi(argv[3]);
	rule->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rule->num_must_eat = ft_atoi(argv[5]);
}