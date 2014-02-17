// program my_cp

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>  

const int NBYTE=1000;

int openFile(char* fileName, int mask)
{
	int fd = open(fileName, mask, 0600);
	if (fd<0)
	{
		perror("open_file_error");
		_exit(1);
	}
	return fd;
}

void copyFile(int fd1, int fd2)
{
	void* buff= malloc(NBYTE);
	int temp_n=0;
	
	while( ( temp_n=read(fd1, buff, NBYTE) ) != 0 )
	{	
		if (temp_n<0)
		{
			perror("copy_error");
			_exit(1);
		}
		
		write(fd2, buff, temp_n);
	}
	
	free(buff);
}

int main(int argc, char **argv)
{
	if (argc!=3)
	{
		write(2,"error: wrong number of argument\n", 30);
		_exit(1);
	}
	
	int fd1 = openFile(argv[1], O_RDONLY);
	int fd2 = openFile(argv[2], O_CREAT|O_TRUNC|O_WRONLY );
	
	copyFile(fd1, fd2);
	
	close(fd1);
	close(fd2);
	
	_exit(0);
}

