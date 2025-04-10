/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 11:45:07 by abnsila           #+#    #+#             */
/*   Updated: 2025/04/09 16:12:16 by abnsila          ###   ########.fr       */
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

# define FORKS_SEM "forks_sem"
# define PRINT_SEM "print_sem"
# define COND_SEM "cond_sem" 
# define SIGNAL_SEM "signal_sem"
# define EMMITER_SEM "emmiter_sem"
# define DONE_SEM "done_sem"
# define DIED_SEM "died_sem"
# define PHILO_DONE_SEM "done_sem_"
# define PHILO_MEAL_SEM "meal_sem_" COND_SEM


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
	pthread_t		routine;
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
	int				num_of_philos;		// Total philosophers
	int				max_meals;			// Optional: meals per philosopher
	time_t			time_to_die;		// Max time without eating (ms)
	time_t			time_to_eat;		// Eating duration (ms)
	time_t			time_to_sleep;		// Sleeping duration (ms)
	time_t			global_start_time;	// Start time for all processes (ms)
	t_sem			forks_sem;			// Protect forks
	t_sem			cond_sem;			// Protect cond
	t_sem			signal_sem;			// Protect Signal
	t_sem			emmiter_sem;		// Protect Emmiter
	t_sem			done_sem;			// Protect done
	t_sem			died_sem;			// Protect died
	t_sem			print_sem;			// Protect Log
	pthread_t		done_monitor;		// All philos they have reach the max meal eaten
}				t_data;



// Parsing
t_bool	ft_is_valid_number(char *str);
t_bool	ft_validate_arg(char **arr, int size);
t_bool	ft_check_parse(int ac, char **av);

// Semaphores Utils
char	*ft_rand_semname(int id, char *base);
void	ft_create_psem(t_sem *sem, int socket, int id, char *base);
void	ft_create_sem(t_sem *sem, char *name, int socket);
void	ft_init_sem(t_data *data);
void	ft_free_sem(t_sem *sem, t_bool is_allocated);
void	ft_destroy_sem(t_data *data);

// Structs Utils
void	ft_init_data(t_data *data, int ac, char **av);
void	ft_destroy(t_data *data, int exit_code);

// Processes
void	ft_child_process(t_data *data, int id);
t_bool	ft_launch_processes(t_data *data, pid_t pids[PHILO_MAX]);
int		ft_philo_init(int id, t_data *data, t_philo *philo);

// Threads Utils
void	ft_init_philo(t_data *data, t_philo *philo);

// Monitor
void	ft_launch_died_signal(t_data *data, t_philo *philo);
void	*ft_self_monitor(void *arg);
void	*ft_global_monitor(void *arg);

// Actions
t_bool	ft_take_forks(t_data *data, t_philo *philo);
t_bool	ft_eat(t_data *data, t_philo *philo);
void	ft_think(t_philo *philo);
t_bool	ft_philo_routine(t_data *data, t_philo *philo);
// void	*ft_start_simulation(t_data *data, t_philo *philo);
void	*ft_start_simulation(void *arg);

// Time Utils
time_t	get_current_time(void);
void	ft_usleep(t_philo *philo, time_t milliseconds);
void	ft_start_delay(time_t start_time);

// Utils
int	ft_wait_thread(pthread_t thr);

t_bool	ft_stop_simulation(t_data *data);
void	ft_print_data(t_data *data);

// Status
void	ft_colored_msg(time_t timestamp, int id, int type);
void	ft_format_msg(time_t timestamp, int id, int type);
void	ft_print_msg(t_data *data, t_philo *philo, int type);

// Error
void	ft_exit_process(t_data *data, t_philo *philo, int exit_code);
void	ft_exit(t_data *data, int exit_code);

#endif
