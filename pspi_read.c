
#include <stdint.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>  
#include <linux/spi/spidev.h> 
#include <time.h>

#include "types.h"
#include "pspi_read.h"
int PspiInit(pSPI pspi){
	int fd;
	int ret;
	int mode = 0;
 	fd = open(pspi->device, O_RDWR);  
    if (fd < 0) 
	{
		printf("can't open device pspi");
		abort();
	}		
          
  
    /* 
     * spi mode 
     */  
  ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);  
    if (ret == -1) 
	{
		printf("can't set pspi mode");
		abort();
	}
          
  
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);  
    if (ret == -1) 
	{
		printf("can't get pspi mode");
		abort();
	}		
  
    /* 
     * bits per word 
     */  
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &pspi->bits);  
    if (ret == -1)  
	{
		printf("can't set pspi bits per word"); 
		abort();
	}	
  
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &pspi->bits);  
    if (ret == -1)  
	{
		printf("can't get pspi bits per word");
		abort();
	}	
    /* 
     * max speed hz 
     */  
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &pspi->speed);  
    if (ret == -1) 
	{
		printf("can't set pspi max speed hz");  
		abort();
	}			
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &pspi->speed);  
    if (ret == -1)  
	{
		printf("can't get pspi max speed hz");
		abort();
	}	
		pspi->fd = fd; 
		printf("pspi mode: %d\n", pspi->mode);  
    printf("pspi bits per word: %d\n", pspi->bits);  
    printf("pspi max speed: %d Hz (%d KHz)\n", pspi->speed, pspi->speed/1000); 
	return 0;
}



int PspiRead(pWZPKG pwzpkg,pSPI pspi){
//  	struct timeval tv;	
		int ret;
		int i;
    int extra_num = pwzpkg->lenLoad % 4096;  
    uint8_t rx[4096] ; 
 
//pkg1
//    gettimeofday(&tv,NULL);
//    printf("before write time:");
//    printf("tv_usec: %d \n",tv.tv_usec);

    memset(rx,0,4096);
    ret = read(pspi->fd,rx,4096);
   // ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr);  
  
    if (ret < 1)  {
        printf("can't send spi message");
			  abort();
		} 
      
		for(i=0;i<12;i++){
			printf("--%02x--",rx[i]);
			pwzpkg->head[i] = rx[i];
		}
		for(i=12;i<4096;i++){
			pwzpkg->load[i-12] = rx[i];
		}


//pkg2
    memset(rx,0,4096);
    ret = read(pspi->fd,rx,4096);
   // ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr);  
    if (ret < 1)  {
        printf("can't send spi message");
			  abort();
		} 
		for(i=0;i<4096 ;i++){
			pwzpkg->load[i+4096-12] = rx[i];
		}  

//pkg3
    memset(rx,0,4096);
    ret = read(pspi->fd,rx,4096);
   // ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr);  
    if (ret < 1)  {
        printf("can't send spi message");
			  abort();
		} 
  
		for(i=0;i<4096;i++){
			pwzpkg->load[i+2*4096-12] = rx[i];
		}  

//pkg4
    memset(rx,0,4096);
    ret = read(pspi->fd,rx,4096);
   // ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr);  
    if (ret < 1)  {
        printf("can't send spi message");
			  abort();
		} 
  
		for(i=0;i<4096;i++){
			pwzpkg->load[i+4096*3-12] = rx[i];
		}  

//pkg5
    memset(rx,0,4096);
    ret = read(pspi->fd,rx,extra_num);
   // ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr);  
    if (ret < 1)  {
        printf("can't send spi message for extra data");
			  abort();
		} 
		int pos_tail = pwzpkg->lenLoad - pwzpkg->lenTail - 2 - 4*4096;
		int pos_crc  = pwzpkg->lenLoad -2 - 4*4096;
//		printf("pos_tail = %d,pos_crc = %d\n",pos_tail,pos_crc);
	  for(i=0;i< pos_tail; i++){
			pwzpkg->load[i+4*4096-12] = rx[i];
		}  
	  for(i=pos_tail;  i<pos_crc;  i++){
			pwzpkg->tail[i-pos_tail] = rx[i];
		}  
	  for(i=pos_crc;  i< pos_crc+2;  i++){
			pwzpkg->crc[i-pos_crc] = rx[i];
		}  
	
		pwzpkg->index++;
    
 //   gettimeofday(&tv,NULL);
 //  printf("\n after write time: ");
 //   printf("tv_usec: %d \n",tv.tv_usec);
	return 0;
}// 实现


int InitWZPKG(pWZPKG pwzpkg){
	pwzpkg->index = 0;
	pwzpkg->res = 0;
	pwzpkg->lenLoad = 18062;
	pwzpkg->lenTail = 48;
	return 0;
}


int MakeWZPKG(pWZPKG pwzpkg){
	int i=0;

	memset(pwzpkg->head,0,sizeof(pwzpkg->head));
	pwzpkg->head[0] = 0x57;
	pwzpkg->head[1] = rand()%10;
	pwzpkg->head[2] = 0x04;
	pwzpkg->head[3] = 0xD0;
	pwzpkg->head[6] = 0x01;
	pwzpkg->head[7] = 0x02;
	pwzpkg->head[8] = rand() & 0xff;
	pwzpkg->head[9] = rand() & 0xff;
	pwzpkg->head[10] = rand() & 0xff;
	pwzpkg->head[11] = rand() & 0xff;

	memset(pwzpkg->load,0,sizeof(pwzpkg->load));
	for(i=0;i<2000;i++){
		pwzpkg->load[i*9] = i & 0xff;	
		pwzpkg->load[i*9+1] = i & 0xff;	
		pwzpkg->load[i*9+2] = i & 0xff;	
		pwzpkg->load[i*9+3] = 0x22;	
		pwzpkg->load[i*9+4] = 0x22;	
		pwzpkg->load[i*9+5] = 0x22;	
		pwzpkg->load[i*9+6] = 0x33;	
		pwzpkg->load[i*9+7] = 0x33;	
		pwzpkg->load[i*9+8] = 0x33;	
	}

	memset(pwzpkg->tail,0,sizeof(pwzpkg->tail));
	for(i=0;i<32;i++)
	{
		pwzpkg->tail[16+i] = i;
	}

	int crc = 0;
	for(i=0;i<12;i++)
		crc += pwzpkg->head[i];
	for(i=0;i<18000;i++)
		crc += pwzpkg->load[i];
	for(i=0;i<pwzpkg->lenTail;i++)
		crc += pwzpkg->tail[i];
	pwzpkg->crc[0] = (crc & 0xff00) >> 8;
	pwzpkg->crc[1] = (crc & 0xff);

	pwzpkg->index ++;
	return 0;
}


int init_rand(){
	time_t now;
	time(&now);
	srand(now);
	return 0;
} 

