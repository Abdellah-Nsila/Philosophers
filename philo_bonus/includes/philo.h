/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/14 17:01:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "functions.h"
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif

# define USAGE_MSG "philo: Usage: \
./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define INPUT_ERROR "philo: Invalid input: %s: \
Value must be a positive integer.\n"
# define TIME_ERROR "philo: Invalid input: %s: \
Value must be between 0 and 2147483647.\n"
# define PHILO_ERROR "philo: Invalid input: %s: \
there must be > 0.\n"
# define APT_ERROR "philo: Invalid input: %s: \
there must be >= 0.\n"
# define MAX 1024

# define FORKS_SEM "forks_sem"
# define HALF_SEM "half_sem"
# define PRINT_SEM "print_sem"
# define COND_SEM "cond_sem" 
# define SIGNAL_SEM "signal_sem"
# define EMMITER_SEM "emmiter_sem"
# define DONE_SEM "done_sem"
# define DIED_SEM "died_sem"
# define PHILO_DONE_SEM "done_sem_"
# define PHILO_MEAL_SEM "meal_sem_"

typedef enum e_state
{
	TAKING_FORK,
	THINKING,
	EATING,
	SLEEPING,
	DIED,
}	t_state;

typedef struct s_sem
{
	char	*name;
	sem_t	*ptr;
}				t_sem;

typedef struct s_philo
{
	pthread_t		self_monitor;
	pthread_t		global_monitor;
	time_t			last_meal_time;
	int				id;
	int				meals_eaten;
	t_sem			meal_sem;
	t_sem			done_sem;
	t_bool			is_done;
	int				exit_code;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_of_philos;
	int				max_meals;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			global_start_time;
	t_sem			forks_sem;
	t_sem			half_sem;
	t_sem			signal_sem;
	t_sem			emmiter_sem;
	t_sem			done_sem;
	t_sem			died_sem;
	t_sem			print_sem;
	pthread_t		done_monitor;
}				t_data;

t_bool	ft_is_valid_number(char *str);
t_bool	ft_validate_arg(char **arr, int size);
t_bool	ft_check_parse(int ac, char **av);

char	*ft_rand_semname(int id, char *base);
void	ft_create_psem(t_sem *sem, int socket, int id, char *base);
void	ft_create_sem(t_sem *sem, char *name, int socket);
void	ft_init_sem(t_data *data);
void	ft_free_sem(t_sem *sem, t_bool is_allocated);
void	ft_destroy_sem(t_data *data);

void	ft_init_data(t_data *data, int ac, char **av);
void	ft_destroy(t_data *data, int exit_code);

void	ft_child_process(t_data *data, int id);
t_bool	ft_launch_processes(t_data *data, pid_t pids[MAX]);

void	ft_launch_died_signal(t_data *data, t_philo *philo);
void	*ft_self_monitor(void *arg);
void	*ft_global_monitor(void *arg);

void	ft_eat(t_data *data, t_philo *philo);
void	ft_think(t_philo *philo);
t_bool	ft_philo_routine(t_data *data, t_philo *philo);
t_bool	ft_check_edge_case(t_data *data, t_philo *philo);
void	*ft_start_simulation(t_data *data, t_philo *philo);

time_t	ft_get_time(void);
void	ft_usleep(time_t milliseconds);
void	ft_start_delay(time_t start_time);

int		ft_wait_thread(pthread_t thr);
void	ft_philo_exit(t_data *data, t_philo *philo);

void	ft_format_msg(time_t timestamp, int id, int type);
void	ft_print_msg(t_data *data, t_philo *philo, int type);

#endif
