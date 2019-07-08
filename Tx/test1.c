#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#define  KEY_NUM     9527
#define  MEM_SIZE    1024
//#define  BUFSIZE	 1024

int main( void)
{
	struct check_data{
		int check;
		int flag;
		char data[MEM_SIZE];
	} *shared_data;

   int   shm_id;
   void *shm_addr;
   FILE *in;
  int ch; 
   //char buffer[BUFSIZ];
   if ((in = fopen("test.jpg", "rb"))==NULL)
	{
		fputs("file open error()",stderr);
		exit(1);
	}
   if ( -1 == ( shm_id = shmget( (key_t)KEY_NUM, 1024, 0666|IPC_CREAT)))
   {
      printf( "공유 메모리 생성 실패\n");
      return -1;
   }

   if ( ( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
   {
      printf( "공유 메모리 첨부 실패\n");
      return -1;
   }
	shared_data = (struct check_data *)shm_addr;

	shared_data->check =0;
	shared_data->flag =1;
	while(1)
	{	
		if(shared_data->check ==0)
			{
		/*if(flag==1)*/ch =fread(shared_data->data,1, 1024, in);
				//sleep(1);
				shared_data->check=1;
				if(ch ==0) 
					{
						shared_data->flag =0;
						break;
					}
			}
	}
 
   
   return 0;
}

