#include<stdio.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#define SIZE 1024

using namespace cv;
using namespace std;

void* firstThreadRun(void *)
{	
    char s[SIZE];
	char c[SIZE];
	char direc[SIZE];
	char s_c[2] ="/";
	Mat img_color;

	//비디오 캡쳐 초기화
    

	VideoCapture cap("res.avi");
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		exit(0);	
	}
	
	
	while(1)
	{
    	time_t t =time(NULL), start, finish;
		struct tm tm = *localtime(&t);

		int min=tm.tm_min;
    	int year = tm.tm_year+1900, mon = tm.tm_mon+1, day=tm.tm_mday, hour=tm.tm_hour;
		sprintf(s, "%d%d%d%d",year,mon,day,hour);
   		mkdir(s, 0776);

		printf("process\n");
		sleep(1);
		//동영상 파일 저장준비
		sprintf(c, "%d%d.avi", hour,min);
		Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
			(int)cap.get(CAP_PROP_FRAME_HEIGHT));
		VideoWriter writer;
		double fps =30.0;
		sprintf(direc, "%s%s%s",s, s_c,c);
		writer.open(direc, VideoWriter::fourcc('M','J','P','G'),fps,size,true);
	
		if (!writer.isOpened())
		{	
		printf("error init_video");
		exit(0);
		}

		// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "빈 영상이 캡쳐되었습니다.\n";
			break;
		}
		writer.write(img_color);			
		// 영상을 화면에 보여줍니다. 
		//imshow("Color", img_color);

            // ESC 키를 입력하면 루프가 종료됩니다. 
		//sleep(60);
		if (waitKey(25) >= 0)
			break;
	}

}	

void* secondThreadRun(void *)
{
	while(1)
	{
		printf("2");
		sleep(3);
	}
}


int main()
{
	pthread_t firstThread, secondThread;
	int threadErr;


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

