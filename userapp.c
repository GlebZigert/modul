#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define DEVICE "/dev/chrdrv"

int main()
{
int i,fd;
char ch, write_buf[100],read_buf[100];
printf("[01]\n");
fd=open(DEVICE,O_RDWR);


if(fd == -1)
{
printf("[FAIL DUD!!!!!!!!]\n");
exit(-1);
}
printf("r = read from divice\n w = write from device\nenter command:");

scanf("%c",&ch);


switch(ch)
{
case 'w':
printf("enter data:");
scanf("%[^\n]",write_buf);
write(fd,write_buf,sizeof(write_buf));
break;

case 'r':
read(fd,read_buf,sizeof(read_buf));
printf("[device:%s\n]\n",read_buf);
break;

defualt:
printf("[command not recognized]\n");
break;

}


return 0;
}