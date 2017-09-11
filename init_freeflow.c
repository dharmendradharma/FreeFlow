#include<stdio.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"freeflow_globals.h"
int config_populator();
int main()
{
int i=1,j,arg_counter=0,shmid;
struct user_input_s *user_input_t;
char user_input_string[40],*user_input_array_pointer;
user_input_array_pointer=user_input_string;
pthread_t config_populator_threadId;
/* Creating a Configuration populator thread */
if(pthread_create(&config_populator_threadId,NULL,config_populator,"NULL")!=0)
	printf(" Failed to create config_populator thread");
/* Creating a Shared Memory segment */
if((shmid=shmget(SHM_KEY,sizeof(struct user_input_s),IPC_CREAT|0666))==-1)
	printf(" Failed to create shared memory : %p ",shmid);
/* Attaching the shared memory segment to main thread's data segment
and assigning memory for the user commands stucture from that space */
if((user_input_t=(struct user_input_s*)shmat(shmid,NULL,0))==-1)
	printf(" Failed to attach the shared memory to main thread");
printf ("user_input_t from main address is : %p ", user_input_t);
while(1)
{
printf(" FreeFlow: > ");
fgets(user_input_string,sizeof(user_input_string),stdin);
while(*user_input_array_pointer!='\0')
{
j=0;
arg_counter++;
while((*user_input_array_pointer!=' ')&&(*user_input_array_pointer!='\0'))
{
if(arg_counter==1)
*(int)user_input_t->argument_1[j]=*user_input_array_pointer;
if(arg_counter==2)
*user_input_t->argument_2[j]=*user_input_array_pointer;
if(arg_counter==3)
*user_input_t->argument_3[j]=*user_input_array_pointer;
j++;
user_input_array_pointer++;
}
i++;
user_input_array_pointer++;
}
printf("\n The first argument is : %s ",*(&(user_input_t->argument_1)));
printf("\n The second argument is : %s ",*(&(user_input_t->argument_2)));
printf("\n The third argument is : %s ",*(&(user_input_t->argument_3)));
}
}

