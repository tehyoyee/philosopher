#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_person {
	int				id;
	int				left_fork;
	int				right_fork;
	struct s_rule	*rule;
}			t_person;

typedef struct s_rule {
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
	pthread_mutex_t *fork;
}			t_rule;

void	exit_error(char *msg);
int		ft_atoi(const char *str);
void	init_rule(int argc, char **argv, t_rule *rule);

#endif