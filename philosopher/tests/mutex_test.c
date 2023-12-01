#include <stdio.h>
#include <pthread.h>

typedef struct s_struct
{
	int				count;
	pthread_mutex_t	fork;
}	t_struct;

//la safe routine protege l'acces memoire avec le fork
void	*safe_routine(void *params)
{
	t_struct *struct_params = (t_struct *) params;
	int i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(&(struct_params->fork));
		struct_params->count++;
		pthread_mutex_unlock(&(struct_params->fork));
	}
	return NULL;
}

//On peut voir que la protection marche meme si utilise dans une autre fonction
void	*safe_routine2(void *params)
{
	t_struct *struct_params = (t_struct *) params;
	int i = 0;
	while (i++ < 1000000)
	{
		pthread_mutex_lock(&(struct_params->fork));
		struct_params->count++;
		pthread_mutex_unlock(&(struct_params->fork));
	}
	return NULL;
}

//data race generator
void	*routine_with_data_race(void *params)
{
	int i = 0;
	t_struct *params_struct = (t_struct *) params; 
	while (i++ < 1000000)
		params_struct->count++;
	return NULL;
}

int main()
{
	pthread_t		p1;
	pthread_t		p2;
	pthread_t		p3;
	t_struct		params;
	pthread_mutex_t	fork;

	pthread_mutex_init(&fork, NULL);

	params.count = 0;
	params.fork = fork;

	if(pthread_create(&p1, NULL, &safe_routine, (void *) &params) != 0)
		return (1);
	if(pthread_create(&p2, NULL, &safe_routine, (void *) &params) != 0)
		return (1);
	pthread_mutex_destroy(&fork);
	if(pthread_create(&p3, NULL, &safe_routine2, (void *) &params) != 0)
		return (1);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_mutex_destroy(&fork);
	printf("count : %d\n", params.count);
}
