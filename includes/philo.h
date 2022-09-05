#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_person {
	int				id;
	int				left_fork;
	int				right_fork;
	int				time;
	int				eat_time;
	pthread_t		thread;
	struct s_rule	*rule;
}			t_person;

typedef struct s_rule {
	int	num_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_must_eat;
	long long	start_time;
	pthread_mutex_t *fork;
	pthread_mutex_t show_status;
	pthread_mutex_t eat;
	struct s_person	*person;
}			t_rule;

int			exit_error(char *msg);
int			ft_atoi(const char *str);
int			init_rule(int argc, char **argv, t_rule *rule);
int			run_thread(t_rule *rule, t_person *person);
long long	set_time();

#endif