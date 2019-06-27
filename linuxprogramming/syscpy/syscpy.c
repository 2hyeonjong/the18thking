#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#define BUF_SIZ 30

int main(int argc, char **argv)
{
	int fd1, fd2, len;
	char buf[BUF_SIZ];

	fd1 =open("test.tar.gz", O_RDONLY);
	fd2 =open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC);

	while((len=read(fd1, buf, sizeof(buf)))>0)
		write(fd2, buf, len);
	
	close(fd1);
	close(fd2);
	return 0;
}
