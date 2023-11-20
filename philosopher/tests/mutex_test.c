#include <stdio.h>
#include <pthread.h>

typedef struct s_struct
{
	int				count;
	pthread_mutex_t	mutex;
}	t_struct;

//la safe routine protege l'acces memoire avec le mutex
void	*safe_routine(void *params)
{
	t_struct *struct_params = (t_struct *) params;
	int i = 0;
	while (i++ < 100000)
	{
		pthread_mutex_lock(&(struct_params->mutex));
		struct_params->count++;
		pthread_mutex_unlock(&(struct_params->mutex));
	}
	return NULL;
}

//On peut voir que la protection marche meme si utilise dans une autre fonction
void	*safe_routine2(void *params)
{
	t_struct *struct_params = (t_struct *) params;
	int i = 0;
	while (i++ < 100000)
	{
		pthread_mutex_lock(&(struct_params->mutex));
		struct_params->count++;
		pthread_mutex_unlock(&(struct_params->mutex));
	}
	return NULL;
}

//data race generator
void	*routine_with_data_race(void *params)
{
	int i = 0;
	t_struct *params_struct = (t_struct *) params; 
	while (i++ < 100000)
		params_struct->count++;
	return NULL;
}

int main()
{
	pthread_t		p1;
	pthread_t		p2;
	pthread_t		p3;
	t_struct		params;
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);

	params.count = 0;
	params.mutex = mutex;

	if(pthread_create(&p1, NULL, &safe_routine, (void *) &params) != 0)
		return (1);
	if(pthread_create(&p2, NULL, &safe_routine, (void *) &params) != 0)
		return (1);
	if(pthread_create(&p3, NULL, &safe_routine2, (void *) &params) != 0)
		return (1);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_mutex_destroy(&mutex);
	printf("count : %d\n", params.count);
}
