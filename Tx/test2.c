#include <stdio.h>      // printf()
#include <unistd.h>     // sleep()
#include <sys/ipc.h>
#include <sys/shm.h>
//#include <opencv/cv.h>
#define  KEY_NUM     9527
#define  MEM_SIZE   1024

int main( void)
{
   struct check_data{
		int check;
		int flag;
		char data[MEM_SIZE];
	}*shared_data;
   int   shm_id;
   void *shm_addr;
   FILE *in, *out;
   int ch;
   char buffer[1024];
   if (-1 == ( shm_id = shmget( (key_t)KEY_NUM, 1024, IPC_CREAT|0666)))
   {
      printf( "공유 메모리 생성 실패\n");
      return -1;
   }

   if (( void *)-1 == ( shm_addr = shmat( shm_id, ( void *)0, 0)))
   {
      printf( "공유 메모리 첨부 실패\n");
      return -1;
	}
	
	shared_data = (struct check_data *)shm_addr;
    in = fopen("test2.jpg", "wb");
	//shared_data->check=1;
	while(1)
	{
		if(shared_data->check==1)
		{
			ch = fwrite(shared_data->data,1,1024, in);
			//printf("전송중");
			shared_data->check=0;
			if(shared_data->flag ==0) break;
		}

	}
	fclose(in);
	if( -1 == shmctl(shm_id, IPC_RMID, 0))
	{
		printf("delete error()");
		return -1;
	}
   return 0;
}
