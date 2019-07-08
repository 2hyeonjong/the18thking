#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include "/opencv/opencv-3.4.2/include/opencv2/opencv.hpp"
#define SIZE 1024
/*void *t_function(void *data)
{
	pid_t pid;
	pthread_t tid;
	pid=getpid();
	tid=pthred_self();

	char* thread_name=(char*)data;
	int i= 0;
}*/
void* firstThreadRun()
{	
	Mat img_color;

	//비디오 캡쳐 초기화
	VideoCapture cap("res.avi");
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}


	while(1)
	{
		// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "빈 영상이 캡쳐되었습니다.\n";
			break;
		}

		// 영상을 화면에 보여줍니다. 
		imshow("Color", img_color);


            // ESC 키를 입력하면 루프가 종료됩니다. 

		if (waitKey(25) >= 0)
			break;
	}

}	
}
void* secondThreadRun()
{
		while(1)
		{
			sleep(3);
			printf("start Second Thread\n");			
		}
}

int main()
{
	pthread_t firstThread, secondThread;
	int threadErr;
    time_t t =time(NULL);
    struct tm tm = *localtime(&t);
    int year = tm.tm_year+1900, mon = tm.tm_mon+1, day=tm.tm_mday, hour=tm.tm_hour;
    int min=tm.tm_min;
    char s[SIZE];

    sprintf(s, "%d%d%d_%d%d",year,mon,day,hour,min);
    if(mkdir(s, 0776)==-1){
        printf("error()\n");
    }

	if(threadErr = pthread_create(&firstThread, NULL, firstThreadRun, NULL))
	{
		printf("Thread Err = %d", threadErr);
	}


	if(threadErr = pthread_create(&secondThread, NULL, secondThreadRun, NULL))
	{
		printf("Thread Err = %d", threadErr);
	}

	while(1);
    
}
