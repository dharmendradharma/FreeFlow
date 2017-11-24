#include<stdio.h>
#include<pthread.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include"freeflow_globals.h"
pthread_mutex_t user_config_lock;
pthread_cond_t cond_signal_from_thread,cond_signal_from_main;
int *config_populator();
/* Configuration populator thread */
int *config_populator()
{
int shmid_trd;
struct user_input_s *user_input_trd;
shmid_trd=shmget(SHM_KEY,sizeof(struct user_input_s),0666);
//printf ("key is : %d ", SHM_KEY);
//printf(" shm id is: %d ", shmid_trd);
if(user_input_trd=(struct user_input_s *)shmat(shmid_trd,NULL,0));
//printf(" \n \t Shared memory attached succesfully to the thread ");
while(1)
{
//printf( "\t \n in thread and waiting for signal");
pthread_cond_wait(&cond_signal_from_main,&user_config_lock);
/*printf("\t \n received signal and waiting for mutex in thread ");
pthread_mutex_lock(&user_config_lock);
printf("\t \n mutexacquired by thread ");
*/
if(user_input_trd=(struct user_input_s *)shmat(shmid_trd,NULL,0));
/*printf(" \n user_input_t address is : %p ",user_input_trd);
/printf(" In config populator \n ");
printf(" First argument is: %s ",*(&(user_input_trd->argument_1)));*/
printf("\n The first argument is : %s ",*(&(user_input_trd->argument_1)));
printf("\n The second argument is : %s ",*(&(user_input_trd->argument_2)));
printf("\n The third argument is : %s ",*(&(user_input_trd->argument_3)));
//pthread_mutex_unlock(&user_config_lock);
pthread_cond_signal(&cond_signal_from_thread);
//printf(" mutex released by thread and sent signal from thread");
}
}
/* Main Function */
int main()
{
/* Declaration Section */
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
//printf ("user_input_t from main address is : %p ", user_input_t);
while(1)
{
printf(" FreeFlow: > ");
/* Rewriting the user string memeory to NULL */
memset(user_input_t,0,sizeof(struct user_input_s));
fgets(user_input_string,sizeof(user_input_string),stdin);
user_input_array_pointer=user_input_string;
arg_counter=0;
//printf("\t \n main waiting for mutex");
//pthread_mutex_lock(&user_config_lock);
//printf("\t \n main got the for mutex");
while(*user_input_array_pointer!='\0'&&(*user_input_array_pointer!='\r'))
{
j=0;
arg_counter++;
while((*user_input_array_pointer!=' ')&&(*user_input_array_pointer!='\0')&&(*user_input_array_pointer!='\r'))
{
if(arg_counter==1)
user_input_t->argument_1[j]=*user_input_array_pointer;
if(arg_counter==2)
user_input_t->argument_2[j]=*user_input_array_pointer;
if(arg_counter==3)
user_input_t->argument_3[j]=*user_input_array_pointer;
j++;
user_input_array_pointer++;
}
i++;
user_input_array_pointer++;
}
//pthread_mutex_unlock(&user_config_lock);
//printf("\t \n main released the mutex");
pthread_cond_signal(&cond_signal_from_main);
//printf("\t \n main sent the conditional signal and waiting for signal from thread");

pthread_cond_wait(&cond_signal_from_thread,&user_config_lock);
//printf("\t \n main got the conditional signal from thread");

/*printf("\n The first argument is : %s ",user_input_t->argument_1);
printf("\n The second argument is : %s ",user_input_t->argument_2);
printf("\n The third argument is : %s ",user_input_t->argument_3);
*/
}
}

