#ifdef WIN32
#include<winsock2.h>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#define  INET_ADDRSTRLEN 32
#pragma comment (lib,"Ws2_32.lib")
#else
#include<sys/socket.h>
//for the header file of perror
#include<stdio.h>
#include<errno.h>
// for the header files of atoi
// for header file of inet_top
#include<arpa/inet.h>
// for header file of memset
#include<string.h>
//void set_sockaddr(struct sockaddr_in *modification,int sin_family, const char* local_port, long   )
//#include"socket.h"
#include<pthread.h>
#endif
// for header file of close
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#define check(a,b) if(-1 == a)												   \
    {																		   \
        perror(b);															   \
        return a;															   \
    }
// ./server local_port
int main(int N, char *COMMAND[])
{
#ifdef WIN32 
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(1,1), &wsaData) != 0) {
		fprintf(stderr, "WSAStartup failed.\n");
		 exit(1);
	 }
#endif
	if ( 3!= N)
	{
		printf("%s local_host_port index.html \n",COMMAND[0]);
		return 0;
	}
	if(access(COMMAND[2], R_OK))
	{
		perror(COMMAND[2]);
		return 1;
	}
	int f=open(COMMAND[2], O_RDONLY, 0600);
	if(-1==f)
	{
		perror(COMMAND[2]);
		return 3;
	}

	char ipstr[INET_ADDRSTRLEN];
	int s=socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == s)
	{
		perror("socket:");
		return s;
	}
	struct sockaddr_in hi;
	hi.sin_family=AF_INET;
	hi.sin_port=htons(atoi(COMMAND[1]));
	hi.sin_addr.s_addr=htonl(INADDR_ANY);
	memset(hi.sin_zero,0, sizeof hi.sin_zero);
	setsockopt(s, SOL_SOCKET,SO_REUSEADDR, NULL,sizeof(int));
	int status=bind(s,(struct sockaddr*)&hi,sizeof hi);
	if (-1 == status)
	{
		perror("bind:");
		return -1;
	}
	status=listen(s, (unsigned int)-1);
	check(status, "listen:")
	struct sockaddr_in client;
	int size_client=sizeof client;
	int c;
	char recv_space[1024], send_space[1024];
	int dd=0;
	dd=sprintf(send_space,"HTTP/1.1 200 OK\n\n");
	struct stat fs;
	fstat(f,&fs);
	char *t;
	t=(char *)malloc(fs.st_size);
	read(f, t, fs.st_size); 
	close(f);
	while(1)
	{
		c=accept(s,(struct sockaddr *) &client, &size_client);
		check(c,"accept:")
#ifdef WIN32
/*
#endif
		inet_ntop(client.sin_family,&(client.sin_addr), ipstr, sizeof ipstr);
		printf("Connected %s:%d \n",ipstr, ntohs(client.sin_port));
#ifdef WIN32
*/
#endif
		int de=recv(c,recv_space,sizeof(recv_space),0);
		recv_space[de]='\0';
		puts(recv_space);
		send(c,send_space, dd,0);
		send(c, t,fs.st_size,0);
#ifdef WIN32
/*
#endif
		shutdown(c, SHUT_RDWR);
#ifdef WIN32
*/
#endif
		close(c);
	}
	close(s);
	puts("Socket close");
#ifdef WIN32
	WSACleanup();
#endif
	return 0;
	
}
