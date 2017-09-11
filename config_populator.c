#include"freeflow_globals.h"
#include<stdio.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int shmid;
struct user_input_s *user_input_t;
int *config_populator()
{
sleep(1);
shmid=shmget(SHM_KEY,sizeof(struct user_input_s),0666);
printf ("key is : %d ", SHM_KEY);
printf(" shm id is: %d ", shmid);
if(user_input_t=(struct user_input_s *)shmat(shmid,NULL,0));
printf(" \n user_input_t address is : %p ",user_input_t);
printf(" In config populator \n ");
printf(" First argument is: %s ",*(&(user_input_t->argument_1))); 
printf("\n The first argument is : %s ",*(&(user_input_t->argument_1)));
return 0;
}

