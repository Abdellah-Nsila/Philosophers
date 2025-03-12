/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abnsila <abnsila@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:00:25 by abnsila           #+#    #+#             */
/*   Updated: 2025/03/11 16:48:49 by abnsila          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/philo.h"
# define THREADS 5
# define PLAYERS 20
# define SLOTS 5

sem_t	sem;

void	*routine(void *arg)
{
	int	*n;
	
	n = (int *)arg;
	printf("%sPlayers: %d Waiting in the login queue\n%s",BYEL, *n, RESET);
	sem_wait(&sem);
	printf("%sPlayers: %d Logged in\n%s",BGRN, *n, RESET);
	printf("%sPlayers: %d Palying now .....\n%s",BBLU, *n, RESET);
	usleep(500000);
	sem_post(&sem);
	printf("%sPlayers: %d Logged out\n%s",BRED, *n, RESET);
	free(arg);
	return (NULL);
}

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
// 	{
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

int main(void) {
    // Open (or create) a named semaphore with an initial value of 3.
    sem_t *sem = sem_open("/my_named_sem", O_CREAT | O_EXCL, 0644, 3);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore created with initial value 3\n");

    // Decrement (wait) on the semaphore.
    if (sem_wait(sem) < 0) {
        perror("sem_wait");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore acquired (value decremented)\n");

    // Simulate some work.
    sleep(2);

    // Increment (post) to release the semaphore.
    if (sem_post(sem) < 0) {
        perror("sem_post");
        exit(EXIT_FAILURE);
    }
    printf("Semaphore released (value incremented)\n");

    // Clean up: close and unlink the named semaphore.
    if (sem_close(sem) < 0) {
        perror("sem_close");
        exit(EXIT_FAILURE);
    }
    if (sem_unlink("/my_named_sem") < 0) {
        perror("sem_unlink");
        exit(EXIT_FAILURE);
    }
    return 0;
}

