#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>

#include "key_read.h"
#include "types.h"

int KeyInit(pKEY pkey)
{
	int keys_fd;
	
  keys_fd = open("/dev/input/event0", O_RDWR|O_NONBLOCK);
	
  printf("keys_fd id %d device !\n",keys_fd);

  pkey->fd = keys_fd;
	pkey->value = 0;
	pkey->status = 0;
	pkey->res = 0;
  return pkey->fd;  
}


int KeyRead(pKEY pkey)
{
//	printf("......KeyRead......");
	int keys_fd;
  keys_fd = pkey->fd; 
  int ret =0;	
	struct input_event t;
	while(1){
		ret = read(keys_fd,&t,sizeof(t));
		if((ret <0) || (t.type != 1)){
			usleep(20000);
//			printf("t.value = %d\n",t.value);
			continue;
		}
	//	printf("ret = %d\tt.type=%d\n",ret,t.type);
		break;
	}
  //  if((ret ==sizeof(t)) && (t.type==1))
		{
			//		printf("size of t is %d \n",sizeof(t));
      //    printf("t.type is %d \n",t.type);
//          printf("t.code is %d \n",t.code);
          printf("t.value is %d \n",t.value);
          pkey->value = t.value;			  //	printf("key114 %s\n",(t.value)?"Pressed":"Released");
    }
		
    	return t.value;
}

int KeyClose(pKEY pkey)
{
	close(pkey->fd);
}

	

int ShowKey(pKEY pkey){
	printf("fd = %d\tvalue=%d\tstatus = %d\tres=%d\n",pkey->fd,\
					pkey->value,pkey->status,pkey->res);
	return 0;
}
