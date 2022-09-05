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
		return (exit_error("incorrect argument number!"));
	else if (init_rule(argc, argv, &rule))
		return (exit_error("argument"));
	printf("n_p : %d\nt_d : %d\nt_e : %d\nt_s : %d\nn_e : %d\n\n", rule.num_philo, rule.time_to_die, rule.time_to_eat, rule.time_to_sleep, rule.num_must_eat);
	for (int i = 0; i < rule.num_philo; i++)
	{
		printf("id = %d\nleft_fork = %d\nright_fork = %d\n\n", rule.person[i].id, rule.person[i].left_fork, rule.person[i].right_fork);
	}
}