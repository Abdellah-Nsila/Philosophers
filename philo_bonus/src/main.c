/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:25 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/12 15:33:20 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
# define THREADS 5
# define PLAYERS 100
# define SLOTS 4
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
#include <unistd.h>


void	*routine(void *arg)
{
	t_proc	*proc;

	proc = (t_proc *)arg;
	
	printf("%sPlayers: %d Waiting in the login queue\n%s",BYEL, proc->id, RESET);
	sem_wait(proc->sem);
	printf("%sPlayers: %d Logged in\n%s",BGRN, proc->id, RESET);
	printf("%sPlayers: %d Palying now .....\n%s",BBLU, proc->id, RESET);
	usleep(500000);
	sem_post(proc->sem);
	printf("%sPlayers: %d Logged out\n%s",BRED, proc->id, RESET);
	return (NULL);
}

int main(void)
{
	t_proc	proc;
	int	pid;
	int	i = 0;
	pid_t	w;
	int		status;

	sem_unlink(SLOT_SEM);

	// Open (or create) a named semaphore with an initial value of 3.
	proc.sem = sem_open(SLOT_SEM, O_CREAT | O_EXCL, 0644, SLOTS);
	if (proc.sem == SEM_FAILED) {
		perror("sem_open");
		exit(EXIT_FAILURE);
	}
	printf("Semaphore created with initial value 3\n");


	while (i < PLAYERS)
	{
		pid = fork();
		if (pid == -1)
			return (pid);
		if (pid == 0)
		{
			proc.id = i + 1;
			pthread_create(&proc.thread, NULL, &routine, &proc);
			pthread_join(proc.thread, NULL);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	w = wait(&status);
	while (w > 0)
	{
		w = wait(&status);
	}
	printf("Done\n");
	if (pid)
	{
		sem_close(proc.sem);
		sem_unlink(SLOT_SEM);
	}

	return (EXIT_SUCCESS);
}

