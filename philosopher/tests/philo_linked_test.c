#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_philo {
	int				number;
	pthread_mutex_t	*fork;
	struct s_philo	*next;
	struct s_philo	*prev;
} t_philo;

void printList(t_philo *head) {
    printf("Double Linked List: ");
    while (head != NULL) {
        printf("philo number %d ", head->number);
        head = head->next;
    }
    printf("\n");
}

t_philo	*last_philo(t_philo *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	add_node_back(t_philo **head, t_philo *new_philo)
{
	t_philo *temp;

	if (*head == NULL)
		*head = new_philo;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_philo;
		new_philo->prev = temp;
	}
}

t_philo	*new_philo_node(int number)
{
	t_philo			*new_philo;
	pthread_mutex_t	*fork;

	fork = malloc(sizeof(pthread_mutex_t));
	new_philo = malloc(sizeof(t_philo));
	if (!fork || !new_philo)
		return (NULL);
	pthread_mutex_init(fork, NULL);
	new_philo->number = number;
	new_philo->fork = fork;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	return (new_philo);
}


t_philo	*set_up_philo_list(t_philo *philo_head, int philo_count)
{
	t_philo			*temp_philo;

	int	i;
	i = 1;
	while (i <= philo_count)
	{
		temp_philo = new_philo_node(i);
		if (!temp_philo)
			return (NULL);
		add_node_back(&philo_head, temp_philo);
		i++;
	}
	temp_philo = last_philo(philo_head);
	temp_philo->next = philo_head;
	philo_head->prev = temp_philo;
	return (philo_head);
}

long	get_ms_since_epoch(void)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

// Il doit eat, wait 2 secondes, rendre les couverts
void	*philo_routine(void *params)
{
	t_philo	*philo = (t_philo *) params;
	t_philo	*right_philo = philo->next;

	pthread_mutex_lock(philo->fork);
	printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);
	pthread_mutex_lock(right_philo->fork);	
	printf("%ld %d has taken a fork\n", get_ms_since_epoch(), philo->number);

	printf("%ld %d is eating\n", get_ms_since_epoch(), philo->number);
	usleep(1000000);
	printf("%ld %d finished eating\n", get_ms_since_epoch(), philo->number);
	
	pthread_mutex_unlock(philo->fork);
	pthread_mutex_unlock(right_philo->fork);
	return NULL;
}

int main(void)
{
	pthread_t		*thread_list;
	t_philo			*philo_head;
	int 			i;
	int				philo_count;

	philo_count = 10;
	philo_head = NULL;

	philo_head = set_up_philo_list(philo_head, philo_count);

	thread_list = malloc(philo_count * sizeof(pthread_t));
	if (!philo_head || !thread_list)
	{
		printf("malloc error\n");
		return (1);
	}

	i = 0;
	while (i < philo_count)
	{
		if (pthread_create((thread_list + i), NULL, &philo_routine, (void *) philo_head) != 0)
			return (1);
		philo_head = philo_head->next;
		i++;
	}

	i = 0;
	while (i < philo_count)
	{
		pthread_join(thread_list[i], NULL);
		i++;
	}

	i = 0;
	while (i < philo_count)
	{
		pthread_mutex_destroy(philo_head->fork);
		philo_head = philo_head->next;
		i++;
	}
	return (0);
}
