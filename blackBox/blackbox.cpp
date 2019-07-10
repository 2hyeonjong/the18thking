#include "header.h"
#define SIZE 1024

using namespace cv;
using namespace std;

void print_avail(unsigned int blocks, unsigned int avail);

const char *MMOUNT = "/proc/mounts";

struct f_size
{
    long blocks;
    long avail; 
};

typedef struct _mountinfo 
{
    FILE *fp;                // 파일 스트림 포인터    
    char devname[80];        // 장치 이름
    char mountdir[80];        // 마운트 디렉토리 이름
    char fstype[12];        // 파일 시스템 타입
    struct f_size size;        // 파일 시스템의 총크기/사용율 
} MOUNTP;

MOUNTP *dfopen()
{
    MOUNTP *MP;

    // /proc/mounts 파일을 연다.
    MP = (MOUNTP *)malloc(sizeof(MOUNTP));
    if(!(MP->fp = fopen(MMOUNT, "r")))
    {
        return NULL;
    }
    else
        return MP;
}

MOUNTP *dfget(MOUNTP *MP)
{
    char buf[256];
    char *bname;
    char null[16];
    struct statfs lstatfs;
    struct stat lstat; 
    int is_root = 0;

    // /proc/mounts로 부터 마운트된 파티션의 정보를 얻어온다.
    while(fgets(buf, 255, MP->fp))
    {
        is_root = 0;
        sscanf(buf, "%s%s%s",MP->devname, MP->mountdir, MP->fstype);
         if (strcmp(MP->mountdir,"/") == 0) is_root=1;
        if (stat(MP->devname, &lstat) == 0 || is_root)
        {
            if (strstr(buf, MP->mountdir) && S_ISBLK(lstat.st_mode) || is_root)
            {
                // 파일시스템의 총 할당된 크기와 사용량을 구한다.        
                statfs(MP->mountdir, &lstatfs);
                MP->size.blocks = lstatfs.f_blocks * (lstatfs.f_bsize/1024); 
                MP->size.avail  = lstatfs.f_bavail * (lstatfs.f_bsize/1024); 
                return MP;
            }
        }
    }
    rewind(MP->fp);
    return NULL;
}

int dfclose(MOUNTP *MP)
{
    fclose(MP->fp);
}

void* firstThreadRun(void *)
{	
    char s[SIZE];
	char c[SIZE];
	char direc[SIZE];
	char s_c[2] ="/";

	Mat img_color;

	//비디오 캡쳐 초기화
    

	VideoCapture cap("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)1280, height=(int)720,format=(string)NV12, framerate=(fraction)24/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink");
	if (!cap.isOpened()) {
		cerr << "에러 - 카메라를 열 수 없습니다.\n";
		exit(0);	
	}
	
	
	while(1)
	{
    	time_t t =time(NULL), start, finish,now;
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
		while(1)
			{// 카메라로부터 캡쳐한 영상을 frame에 저장합니다.			
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
			time_t timer;
			struct tm *tt;
			timer = time(NULL);
			tt = localtime(&timer);

			if(min == tt->tm_min)
				continue;
		}
	}
	

}	

void* secondThreadRun(void *)
{
	/*while(1)
	{
		printf("2");
		sleep(3);
	}*/
	MOUNTP *MP;
    if ((MP=dfopen()) == NULL)
    {
        perror("error");
        exit(0);
    }
 
   while(1)
    {
        while(dfget(MP))
        {
				print_avail(MP->size.blocks, MP->size.avail);
/*            printf("%s \t %s \t %lu \t %lu \t %f \n", MP->mountdir, MP->devname, 
                                MP->size.blocks,
                                MP->size.avail,
										 ((double)MP->size.avail/(double) MP->size.blocks)*100);						
				// (MP->size.avail /MP->size.blocks)*100.0); */
        }
        printf("=========================\n\n");
        sleep(1);
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

void print_avail(unsigned int blocks, unsigned int avail)
{
	double t_avail = ((double)avail / (double)blocks)*100;
   printf("\t %u \t %u \t %f \n",blocks,avail, t_avail);
}