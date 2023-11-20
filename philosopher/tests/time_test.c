#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

int main(){
	struct timeval now;
	struct timeval later;
	
	gettimeofday(&now,NULL);

	printf("sec since epoch : %ld\n",now.tv_sec);
	printf("current sec us : %ld\n",now.tv_usec);

	printf("---------SLEEP----------\n");

	usleep(1000000);
	gettimeofday(&later,NULL);

	printf("sec since epoch : %ld\n",later.tv_sec);
	printf("current sec us : %ld\n",later.tv_usec);

	printf("sec waited : %ld\n", later.tv_sec - now.tv_sec);
	printf("us waited : %ld\n", later.tv_usec- now.tv_usec);
}