#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std; 

int main() 
{

        char *path = "/tmp";
 
	// ftok to generate unique key 
	key_t key = ftok(path,60); 

	printf("\n key=%d", key);
	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 


	// shmat to attach to shared memory 
	char *str = (char*) shmat(shmid,(void*)0,0); 

	printf("Data read from memory: %s\n",str);

	 
	
	//detach from shared memory 
	shmdt(str); 
	
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
} 

