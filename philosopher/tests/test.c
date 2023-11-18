#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>

void	*hello(void *param)
{
	printf("Hello %s\n", (char *) param);
}

int main()
{

	// go faire des fichier test pour chaque categories par pitie
	

	pthread_t thread1;
	char message[] = "Thread";

	pthread_create(&thread1, NULL, hello, (void *) &message);

	
	pthread_join(thread1, NULL);

	struct timeval now;

	gettimeofday(&now,NULL);

	printf("sec since epoch : %ld\n",now.tv_sec);
	printf("current sec us : %ld\n",now.tv_usec);

	usleep(1000000);
	gettimeofday(&now,NULL);

	printf("time sec : %ld\n",now.tv_sec);
	printf("time us : %ld\n",now.tv_usec);
	return (0);
}