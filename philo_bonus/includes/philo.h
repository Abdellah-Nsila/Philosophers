/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/28 17:28:26 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "functions.h"
# include "colors.h"
# include <unistd.h>
# include <time.h>
# include <sys/time.h>
# include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
# include <pthread.h>
# include <semaphore.h>

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef LONG_MAX
#  define LONG_MAX 9223372036854775807
# endif

# define USAGE_MSG "%sphilo: Usage: \
./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n%s"
# define INPUT_ERROR "%sphilo: Invalid input: %s: \
Value must be a positive integer.\n%s"
# define ARG_ERROR "%sphilo: Invalid input: %s: \
Value must be between 0 and 2147483647.\n%s"
# define PHILO_ERROR "%sphilo: Invalid input: %s: \
there must be between 1 and %d philosophers.\n%s"
# define PHILO_MAX 200
# define FORKS "forks_sem"
# define PRINT "print_sem"


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
	sem_t	*sem;
}				t_sem;

typedef struct s_philo
{
	int				id;
	pthread_t		routine_thread;
	pthread_t		monitor_thread;
	time_t			last_meal_time;
	int				meals_eaten;
	t_bool			stop_flag;
	sem_t			meal_sem;
	sem_t			stop_sem;
	int				exit_code;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_of_philos;		// Total philosophers
	int				max_meals;			// Optional: meals per philosopher
	time_t			time_to_die;		// Max time without eating (ms)
	time_t			time_to_eat;		// Eating duration (ms)
	time_t			time_to_sleep;		// Sleeping duration (ms)
	time_t			global_start_time;	// Start time for all processes (ms)
	t_sem			forks_sem;			// Protect forks
	t_sem			signal_sem;			// Protect Signal
	t_sem			done_sem;			// Protect done
	t_sem			died_sem;			// Protect died
	t_sem			print_sem;			// Protect Log
}				t_data;

typedef struct s_proc
{
	int				id;
	pthread_t		thread;
	sem_t			*sem;
}				t_proc;

// Parsing
t_bool	ft_is_valid_number(char *str);
t_bool	ft_validate_arg(char **arr, int size);
t_bool	ft_check_parse(int ac, char **av);

// Processes
void	ft_child_process(t_data *data);
void	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX]);

// Threads
void	ft_init_philo(t_data *data, t_philo *philo);
void	ft_launch_threads(t_data *data, t_philo *philo);

// Monitor
t_bool	ft_did_finish_eat(t_data *data, t_philo *philo);
t_bool	ft_is_died(t_data *data, t_philo *philo);
void	*ft_philo_monitor(void *arg);
t_bool	ft_launch_monitor(t_data *data, pid_t pids[PHILO_MAX]);

// Actions
t_bool	ft_take_forks(t_data *data, t_philo *philo);
t_bool	ft_eat(t_data *data, t_philo *philo);
void	ft_think(t_philo *philo);
t_bool	ft_philo_routine(t_data *data, t_philo *philo);
void	*ft_start_simulation(void *arg);

// Time Utils
time_t	get_current_time(void);
void	ft_usleep(t_philo *philo, time_t milliseconds);
void	ft_start_delay(time_t start_time);

// Utils
t_bool	ft_stop_simulation(t_data *data);
void	ft_print_data(t_data *data);

// Structs Utils
void	ft_init_data(t_data *data, int ac, char **av);
void	ft_destroy(t_data *data);

// Status
void	ft_colored_msg(time_t timestamp, int id, int type);
void	ft_format_msg(time_t timestamp, int id, int type);
void	ft_print_msg(t_data *data, t_philo *philo, int type);

// Error
void	ft_exit_process(t_data *data, t_philo *philo, int exit_code);
void	ft_exit(t_data *data, int exit_code);

#endif
