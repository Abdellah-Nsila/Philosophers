/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:25 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/13 15:45:50 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
# define THREADS 5
# define PLAYERS 4
# define SLOTS 2
# define SLOT_SEM "slots_sem"

// sem_t	sem;

// void	*routine(void *arg)
// {
// 	int	*n;
	
// 	n = (int *)arg;
// 	printf("%sPlayers: %d Waiting in the login queue\n%s",BYEL, *n, RESET);
// 	sem_wait(&sem);
// 	printf("%sPlayers: %d Logged in\n%s",BGRN, *n, RESET);
// 	printf("%sPlayers: %d Palying now .....\n%s",BBLU, *n, RESET);
// 	usleep(500000);
// 	sem_post(&sem);
// 	printf("%sPlayers: %d Logged out\n%s",BRED, *n, RESET);
// 	free(arg);
// 	return (NULL);
// }

// int	main()
// {
// 	int			i;
// 	int			*n;
// 	pthread_t	threads[PLAYERS];	

// 	i = 0;
// 	sem_init(&sem, 0, SLOTS);
// 	while (i < PLAYERS)
// 	{
// 		n = malloc(sizeof(int));
// 		*n = i + 1;
// 		pthread_create(&threads[i], NULL, &routine, n);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < PLAYERS)
// 	{2
// 		pthread_join(threads[i], NULL);
// 		i++;
// 	}
// 	sem_destroy(&sem);
// }


#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <math.h>


void	ft_init_sem(t_proc *proc)
{
	sem_unlink(SLOT_SEM);
	proc->sem = sem_open(SLOT_SEM, O_CREAT | O_EXCL, 0644, SLOTS);
	if (proc->sem == SEM_FAILED) {
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	printf("Semaphore created with initial value %d\n", SLOTS);
}

void	*routine(void *arg)
{
	t_proc	*proc;
	t_bool	crash;

	proc = (t_proc *)arg;
	srand(time(NULL) + getpid());
	while (true)
	{
		printf("%sPlayers: %d Waiting in the login queue\n%s",BYEL, proc->id, RESET);
		// Logged in
		sem_wait(proc->sem);
		printf("%sPlayers: %d Logged in\n%s",BGRN, proc->id, RESET);
		// Playing
		printf("%sPlayers: %d Palying now .....\n%s",BBLU, proc->id, RESET);
		usleep(500000);
		// Simulate a crash during playing
		crash = (rand() % (true - false + true)) + false; // number between 1 - 0 (true - flase)
		printf("%sPlayers: %d crash: %d\n%s", BCYN, proc->id, crash, RESET);
		if (crash == 1)
			exit(EXIT_FAILURE);
		// Logged out
		sem_post(proc->sem);
		printf("%sPlayers: %d Logged out\n%s",BRED, proc->id, RESET);
		usleep(1000000);
	}
	return (NULL);
}

void ft_launch_processes(t_proc *proc, pid_t pids[PLAYERS]){
	int	i;

	i = 0;
	while (i < PLAYERS)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		if (pids[i] == 0)
		{
			proc->id = i + 1;
			pthread_create(&proc->thread, NULL, &routine, proc);
			pthread_join(proc->thread, NULL);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

t_bool	ft_launch_monitor(pid_t pids[PLAYERS])
{
	int status;
	int exit_code;
	int i;
	t_bool	failure_found = false;
	int 	remaining = PLAYERS;
	
	// Monitor child processes in a non-blocking loop.
	while (remaining > 0) {
		pid_t wpid = waitpid(-1, &status, WNOHANG);
		if (wpid > 0) {
			remaining--;
			if (WIFEXITED(status)) {
				exit_code = WEXITSTATUS(status);
				printf("%sChild PID %d exited with code %d\n%s",BWHT, wpid, exit_code, RESET);
				if (exit_code == EXIT_FAILURE) {
					failure_found = true;
					printf("%sChild PID %d failed %d\n%s",BMAG, wpid, exit_code, RESET);
					// Immediately kill all child processes.
					for (i = 0; i < PLAYERS; i++) {
						kill(pids[i], SIGKILL);
					}
					break;
				}
			}
		}
		usleep(10000); // Sleep briefly to avoid busy-waiting.
	}
	return (failure_found);
}

// TODO go understand the logic of killen all procs after crash
// TODO separate think and get info init simulate this sense
int main(void)
{
	pid_t	pids[PLAYERS];
	t_proc	proc;
	t_bool	failure_found;


	ft_init_sem(&proc);
	ft_launch_processes(&proc, pids);
	failure_found = ft_launch_monitor(pids);
	
	// Wait for any remaining children to be reaped.
	while (wait(NULL) > 0)
		;
	if (failure_found)
		printf("%sA child failed. All children have been killed.\n%s",BHRED, RESET);
	else
		printf("%sAll children exited successfully.\n%s",BHGRN, RESET);
	
	sem_close(proc.sem);
	sem_unlink(SLOT_SEM);
	return EXIT_SUCCESS;
}