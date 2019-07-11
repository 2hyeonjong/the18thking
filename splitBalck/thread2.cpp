#include "header.h"

double print_avail(unsigned int blocks, unsigned int avail)
{
	double t_avail = ((double)avail / (double)blocks)*100;
   printf("\t %u \t %u \t %.2f%% \n",blocks,avail, t_avail);
   return t_avail;
}

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

void* secondThreadRun(void *)
{
	sleep(1);
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
	const char *path =".";
	struct dirent **namelist;
	int count;
	int idx;
	double available;
	char rm[]= "rm -rf ";
	if((count = scandir(path, &namelist, NULL, alphasort))==-1)
	{
		fprintf(stderr, "%s Directory Scan Error\n", path);
		exit(0);
	}
	for(idx = count -1; idx >= 0; idx--)
	{
		printf("%s\n", namelist[idx]->d_name);
	}
   while(1)	
    {
        while(dfget(MP))
        {
			available =print_avail(MP->size.blocks, MP->size.avail);
/*            printf("%s \t %s \t %lu \t %lu \t %f \n", MP->mountdir, MP->devname, 
                                MP->size.blocks,
                                MP->size.avail,
										 ((double)MP->size.avail/(double) MP->size.blocks)*100);						
				// (MP->size.avail /MP->size.blocks)*100.0); */
        }
        printf("=====================================================\n\n");
        sleep(1);
		if(available <20.00)
		{
			strcat(rm, namelist[2]->d_name );
			system(rm);
		}
    }
	
	//data memroy relese
	for(idx = 0; idx <count; idx++)
	{
		free(namelist[idx]);
	}
	free(namelist);
}