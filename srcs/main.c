#include "philo.h"

//	number_of_philosophers
//	time_to_die
//	time_to_eat
//	time_to_sleep
//	[number_of_times_each_philosophers_must_eat]



int	main(int argc, char **argv)
{
	t_rule rule;

	if (argc != 5 && argc != 6)
		exit_error("incorrect argument number!");
	init_rule(argc, argv, &rule);
}