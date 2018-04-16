#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#include "key_read.h"
#include "types.h"

int KeyInit(pKEY pkey)
{
	int keys_fd;
	
  keys_fd = open("/dev/input/event0", O_RDWR|O_NONBLOCK);
	
  printf("keys_fd id %d device !\n",keys_fd);

  pkey->fd = keys_fd;
  return pkey->fd;  
}

int KeyRead(pKEY pkey)
{
	int keys_fd;
  keys_fd = pkey->fd; 
  int ret =0;	
	struct input_event t;
    if((read(keys_fd,&t,sizeof(t))==sizeof(t))&&(t.type==1))
		{
			//		printf("size of t is %d \n",sizeof(t));
      //    printf("t.type is %d \n",t.type);
          printf("t.code is %d \n",t.code);
          printf("t.value is %d \n",t.value);
          pkey->value = t.value;			  //	printf("key114 %s\n",(t.value)?"Pressed":"Released");
    }
		
    	return t.value;
}

int KeyClose(pKEY pkey)
{
	close(pkey->fd);
}

	

