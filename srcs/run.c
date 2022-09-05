#include "philo.h"

int	run_thread(t_rule *rule, t_person *person)
{
	int	i;

	i = 0;
	rule->start_time = set_time();
	while (i < rule->num_philo)
	{
		pthread_create(&person[i]->thread, NULL, ft_thread, &rule->person[i]);
	}
}