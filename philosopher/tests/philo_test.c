#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo {
	int	number;
	int	fork_used;
	pthread_mutex_t	mutex;
} t_philo;

typedef struct s_params {
	int		number;
	t_philo	*philo_list;
} t_params;

// Il doit eat, wait 2 secondes, rendre les couverts
void	*philo_routine(void *params)
{
	t_params	*thread_params = (t_params *) params;
	t_philo 	*philo = thread_params->philo_list;
	printf("thread id : %d\n",thread_params->number);

	pthread_mutex_lock(&(philo->mutex));
	printf("Philo %d started eating\n", philo->number);
	usleep(2000000);
	printf("Philo %d finished eating\n", philo->number);
	pthread_mutex_unlock(&(philo->mutex));

	return NULL;
}

int main(void)
{
	pthread_t		*thread_list;
	t_philo			*philo_list;
	pthread_mutex_t	*mutex_list;
	t_params		thread_params;
	int 			i;
	int				philo_number;

	philo_number = 2;

	mutex_list = malloc(philo_number * sizeof(pthread_mutex_t));
	philo_list = malloc(philo_number * sizeof(t_philo));
	thread_list = malloc(philo_number * sizeof(pthread_t));
	if (!mutex_list || !philo_list || !thread_list)
	{
		printf("malloc error\n");
		return (1);
	}
	i = 0;
	while (i < philo_number)
	{
		pthread_mutex_init(mutex_list + i, NULL);
		philo_list[i].number = i + 1;
		philo_list[i].fork_used = 0; 
		philo_list[i].mutex = mutex_list[i];
		i++;
	}

	thread_params.philo_list = philo_list;

	i = 0;
	while (i < philo_number)
	{
		thread_params.number = i;
		printf("thread number %d\n",thread_params.number);
		if (pthread_create((thread_list + i), NULL, &philo_routine, (void *) &thread_params) != 0)
			return (1);
		i++;
	}

	i = 0;
	while (i < philo_number)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo_number)
	{
		pthread_mutex_destroy((mutex_list + 0));
		i++;
	}
}
