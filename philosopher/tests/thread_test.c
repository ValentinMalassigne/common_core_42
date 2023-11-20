#include <stdio.h>
#include <pthread.h>


void	*detached_hello(void *param)
{
	while(1)
		printf("Detached Hello\n");
}

void	*hello(void *param)
{
	printf("Hello %s\n", (char *) param);
	return(0);
}

int main(void)
{
	pthread_t thread1;
	pthread_t thread2;
	char message[] = "Thread";

	pthread_create(&thread1, NULL, hello, (void *) &message);
	pthread_create(&thread2, NULL, detached_hello, NULL);
	pthread_detach(thread2);

	//pthread_join(thread1, NULL);
	printf("End of main\n");
	return (0);
}
