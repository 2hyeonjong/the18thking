#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
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
	IplImage *frame = 0;
    CvVideoWriter *writer = 0;
 
    //cvCaptureFromFile(파일명) : 동영상 파일 불러오기
	CvCapture *capture = cvCaptureFromAVI("D:/study/su.avi");
 
	cvNamedWindow("video", CV_WINDOW_AUTOSIZE);
    
    int fps = 30;    //30프레임
 
  	//첫번째 프레임으로부터 크기 구하기
   	cvGrabFrame(capture);
 	frame = cvRetrieveFrame(capture);
    //cvCreateVideoWriter(경로, 코덱방식, fps, 프레임크기) : 동영상파일 생성
    //CV_FOURCC('D', 'I', 'V', 'X') : MPEG-4 코덱
   	writer = cvCreateVideoWriter("D:/study/opencv_ex1/copy.avi", CV_FOURCC('D', 'I', 'V', 'X'), fps, cvGetSize(frame));
    while (1) 
	{
    	 //cvGrabFrame(동영상) : 하나의 프레임을 잡음
         cvGrabFrame(capture);
         //cvRetrieveFrame(동영상) : 잡은 프레임으로부터 이미지를 구함
      	 frame = cvRetrieveFrame(capture);
         if (!frame || cvWaitKey(10) >= 0) { break; }
 
        
   	     //cvWriteFrame(동영상, 프레임) : 지정한 동영상에 프레임을 쓴다
   		 cvWriteFrame(writer, frame);
 
     	 cvShowImage("video", frame);
    }
 
   	//cvReleaseVideoWriter(동영상) : 메모리에서 해제한다
    cvReleaseVideoWriter(&writer);
 
    cvReleaseCapture(&capture);
    cvDestroyWindow("video");
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
