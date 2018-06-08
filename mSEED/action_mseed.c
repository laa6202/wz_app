//action_mseed.c
//ACtion the module when buf ready,example 30sec one file.

#include <stdio.h>

#include "mtypes.h"

int TestStruct(){
	printf("Test struct size only.\n");
	HEAD head;
	FRAME frame;
	PACK pack;
	printf("SIZE of head = %ld\n",sizeof(HEAD));
	printf("SIZE of frame = %ld\n",sizeof(FRAME));
	printf("SIZE of pack = %ld\n",sizeof(PACK));

	return 0;
}
