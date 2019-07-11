#include "header.h"

void* firstThreadRun(void *)
{	
    char s[SIZE];
	char c[SIZE];
	char direc[SIZE];
	char s_c[2] ="/";

	Mat img_color;

	//비디오 캡쳐 초기화
    
	//VideoCapture cap("res.avi");
	VideoCapture cap("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)NV12, framerate=(fraction)30/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		exit(0);	
	}
	
	
	
	while(1)
	{
		
    	time_t t =time(NULL);
		struct tm tm = *localtime(&t);
		double duration;

		int min=tm.tm_min;
    	int year = tm.tm_year+1900, mon = tm.tm_mon+1, day=tm.tm_mday, hour=tm.tm_hour;
		sprintf(s, "%d%d%d%d",year,mon,day,hour);
   		mkdir(s, 0776);

		printf("process\n");
		sleep(1);
		//동영상 파일 저장준비
		sprintf(c, "%d%d.avi", hour,min);
		
		Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH ),
			(int)cap.get(CAP_PROP_FRAME_HEIGHT));
		VideoWriter writer;
		double fps =15.0;
		sprintf(direc, "%s%s%s",s, s_c,c);
		writer.open(direc, VideoWriter::fourcc('D','I','V','X'),fps,size,true);
	
		if (!writer.isOpened())
		{	
			printf("error init_video");
			exit(0);
		}
		while(1)
			{// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.			
			cap.read(img_color);
			cv::flip(img_color, img_color, -1);
			cv::flip(img_color, img_color, 1);

			if (img_color.empty()) {
				cerr << "빈 영상이 캡쳐되었습니다.\n";
				break;
			}
			writer.write(img_color);			
			// 영상을 화면에 보여줍니다. 
			//imshow("Color", img_color);

				// ESC 키를 입력하면 루프가 종료됩니다. 
			//sleep(60);
			if (waitKey(33) >= 0)
				break;
			time_t timer;
			struct tm *tt;
			timer = time(NULL);
			tt = localtime(&timer);

			if(min != tt->tm_min)
				break;
		}
	}
	

}	
