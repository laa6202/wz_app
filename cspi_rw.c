#include <stdint.h>  
#include <unistd.h>  
#include <stdio.h>  
#include <string.h>
#include <time.h>
#include <stdlib.h>  
#include <getopt.h>  
#include <fcntl.h>  
#include <sys/ioctl.h>  
#include <linux/types.h>  
#include <linux/spi/spidev.h> 
#include "types.h"


int CspiInit(pSPI pspi){
	int fd;
	int ret;
	static uint8_t mode;
	fd = open(pspi->device, O_RDWR);  
    if (fd < 0) 
	{
		printf("can't open device cspi"); 
		abort();
	}		
         
  
    /* 
     * spi mode 
     */  
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);  
    if (ret == -1)  
	{
		printf("can't set cspi mode");
		abort();
	}	
     
  
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);  
    if (ret == -1)
    {
		printf("can't get cspi mode");
		abort();
	}			
   
    /* 
     * bits per word 
     */  
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &pspi->bits);  
    if (ret == -1) 
    {
		printf("can't set cspi bits per word"); 
		abort();
	}			
  
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &pspi->bits);  
    if (ret == -1) 
    {
		printf("can't get cspi bits per word"); 
		abort();
	}			
 
    /* 
     * max speed hz 
     */  
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &pspi->speed);  
    if (ret == -1) 
	{
		printf("can't set cspi max speed hz");
		abort();
	}			
  
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &pspi->speed);  
    if (ret == -1) 
	{
		printf("can't get cspi max speed hz");
		abort();
	}			

	pspi->fd = fd;
	
    printf("cspi mode: %d\n", mode);  
    printf("cspi bits per word: %d\n", pspi->bits);  
    printf("cspi max speed: %d Hz (%d KHz)\n", pspi->speed, pspi->speed/1000); 

}

//read FPGA register using CMD struct
int CspiRead(pCMD pcmd,pSPI pspi){
    int ret;  
    uint8_t tx5[5] = {pcmd->devid,pcmd->rw,pcmd->modid,pcmd->addr,pcmd->data};
 
    uint8_t rx5[5] = {0, };  
    struct spi_ioc_transfer tr5 = {  
        .tx_buf = (unsigned long)tx5,  
        .rx_buf = (unsigned long)rx5,  
        .len = 5,  
        .delay_usecs = pspi->delay,  
        .speed_hz = pspi->speed,  
        .bits_per_word = pspi->bits,  
	};
   	ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr5);  
    if (ret < 1)  {
		pcmd->status = -1;

		printf("can't send cspi message");
		abort();
	}		
    else {
	  pcmd->status = 0;
	  pcmd->q = rx5[4];
      printf("cspi transfer ok return value is %d \n", ret); 
    }	  

	return pcmd->status;
}


int CspiWrite(pCMD pcmd,pSPI pspi){
    int ret;  
    uint8_t tx5[5] = {pcmd->devid,pcmd->rw,pcmd->modid,pcmd->addr,pcmd->data};
 
    uint8_t rx5[5] = {0, };  
    struct spi_ioc_transfer tr5 = {  
        .tx_buf = (unsigned long)tx5,  
        .rx_buf = (unsigned long)rx5,  
        .len = 5,  
        .delay_usecs = pspi->delay,  
        .speed_hz = pspi->speed,  
        .bits_per_word = pspi->bits,  
	};
   	ret = ioctl(pspi->fd, SPI_IOC_MESSAGE(1), &tr5);  
    if (ret < 1)  {
		pcmd->status = -1;

		printf("can't send cspi message");
		abort();
	}		
    else {
	  pcmd->status = 0;
	  pcmd->q = rx5[4];
      printf("cspi transfer ok return value is %d \n", ret); 
    }	  

	return pcmd->status;
}
