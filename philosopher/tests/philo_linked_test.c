#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo {
	int				number;
	int				fork_used;
	pthread_mutex_t	*mutex;
	struct s_philo	*next;
	struct s_philo	*prev;
} t_philo;

// Il doit eat, wait 2 secondes, rendre les couverts
// void	*philo_routine(void *params)
// {
// 	t_philo	*philo = (t_philo *) params;

// 	pthread_mutex_lock(&(philo->mutex));
// 	printf("Philo %d started eating\n", philo->number);
// 	usleep(2000000);
// 	printf("Philo %d finished eating\n", philo->number);
// 	pthread_mutex_unlock(&(philo->mutex));

// 	return NULL;
// }

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
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	new_philo = malloc(sizeof(t_philo));
	if (!mutex || !new_philo)
		return (NULL);
	new_philo->number = number;
	new_philo->mutex = mutex;
	new_philo->fork_used = 0;
	new_philo->next = NULL;
	new_philo->prev = NULL;
	return (new_philo);
}

void printList(t_philo *head) {
    printf("Double Linked List: ");
    while (head != NULL) {
        printf("philo number %d ", head->number);
        head = head->next;
    }
    printf("\n");
}

int main(void)
{
	pthread_t		*thread_list;
	t_philo			*philo_head;
	t_philo			*temp_philo;
	int 			i;
	int				philo_number;

	philo_number = 10;
	philo_head = NULL;

	i = 1;
	while (i <= philo_number)
	{
		add_node_back(&philo_head, new_philo_node(i));
		i++;
	}
	i = 0;
	while (i < philo_number)
	{
		printf("philo nb %d\n", philo_head->number);
		if (philo_head->next)
			philo_head = philo_head->next; 
		i++;
	}
	//ATTENTION A NE PAS ETRE ARRIVE A UN NULL AVANT DE CALL CA
	philo_head = philo_head->prev;
	printf("philo nb %d\n", philo_head->number);
	return (0);






	// thread_list = malloc(philo_number * sizeof(pthread_t));
	// if (!mutex_list || !philo_list || !thread_list)
	// {
	// 	printf("malloc error\n");
	// 	return (1);
	// }
	// i = 0;
	// while (i < philo_number)
	// {
	// 	pthread_mutex_init(mutex_list + i, NULL);
	// 	philo_list[i].number = i + 1;
	// 	philo_list[i].fork_used = 0; 
	// 	philo_list[i].mutex = mutex_list[i];
	// 	i++;
	// }

	// i = 0;
	// while (i < philo_number)
	// {
	// 	thread_params.number = i;
	// 	printf("thread number %d\n",thread_params.number);
	// 	if (pthread_create((thread_list + i), NULL, &philo_routine, (void *) &thread_params) != 0)
	// 		return (1);
	// 	i++;
	// }

	// i = 0;
	// while (i < philo_number)
	// {
	// 	pthread_join(thread_list[i], NULL);
	// 	i++;
	// }
	// i = 0;
	// while (i < philo_number)
	// {
	// 	pthread_mutex_destroy((mutex_list + 0));
	// 	i++;
	// }
}
