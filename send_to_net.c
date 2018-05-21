#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <errno.h>  
  
#include "types.h"
#include "send_to_net.h"

int   MYPORT = 8887 ;
char SERVERIP[20] = "192.168.1.104";
  
  
#define ERR_EXIT(m) \
    do {   \
    perror(m);  \
    exit(EXIT_FAILURE);\
     } while (0) 

int InitSocket(void)
{ 
    int sock;  
    if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0)  
        ERR_EXIT("socket"); 
    return sock; 
}

void echo_cli(int sock,WZPKG wzpkg)  
{  
    struct sockaddr_in servaddr;  
    memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(MYPORT);  
    servaddr.sin_addr.s_addr = inet_addr(SERVERIP);  
          
    int ret;  
    char sendbuf[18062] = {0};  
    char recvbuf[1024] = {0};
    for(ret = 0; ret<12; ret++)
			sendbuf[ret]= wzpkg.head[ret];
    for(ret = 0; ret < 18000; ret++)
			sendbuf[ret+12]= wzpkg.load[ret];
    for(ret = 0; ret < 48; ret++)
			sendbuf[ret+18012]= wzpkg.tail[ret];
    for(ret = 0; ret < 2; ret++)
			sendbuf[ret+18060]= wzpkg.crc[ret];
		
    if(1) //  while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)  
    {  
//       printf("......向 %s:%d 发送 OK ......\n",SERVERIP,MYPORT); 
    sendto(sock, sendbuf, 18062, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));  
        memset(sendbuf, 0, sizeof(sendbuf));  
        memset(recvbuf, 0, sizeof(recvbuf));  
    }  
      
//    close(sock);  
      
      
}  
int SendToNet(const WZPKG wzpkg,FILE * fid)
{
	fwrite(wzpkg.head,1,sizeof(wzpkg.head),fid);
	fwrite(wzpkg.load,1,sizeof(wzpkg.load),fid);
	fwrite(wzpkg.tail,1,wzpkg.lenTail,fid);
	fwrite(wzpkg.crc,1,sizeof(wzpkg.crc),fid);
	return 0;
}


int GetNet(char * fn,const CFG cfg)
{
	return 0;
}


int SendOneWZPKG(CFG cfg,int sock,WZPKG wzpkg)
{

	int port = cfg.remoteHost.port;
	char *ip;
	ip = cfg.remoteHost.ip;
   MYPORT = port;
   strcpy(SERVERIP, ip);

   echo_cli(sock,wzpkg);  
	return 0;
}


int SendSomeWZPKG(const CFG cfg, WZPKG wzpkg, int mount)
{
	printf("......SendSomeWZPKG......\n");
}


