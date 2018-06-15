//buf4mseed.c
//Every time one WZPKG ready, call the buf function.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "types.h"

#include "mtypes.h"
#include "buf4mseed.h"

int InitWZPKG(pWZPKG pwzpkg){
	memset(pwzpkg,0,sizeof(WZPKG));
	return 0;
}


int InitRawAll(pRAWALL pRawAll){
//	printf("sizeof RAWALL = %ld\n",sizeof(RAWALL));
	for(int i=0;i<NUM_DEV;i++)
	{
		pRawAll->praw[i] = (pRAW)malloc(sizeof(RAW));	
		memset(pRawAll->praw[i],0,sizeof(RAW));
		pRawAll->praw[i]->len = LEN_RAW;
	}
	return 0;
}


int GenTestWZPKG(pWZPKG pwzpkg,int dev_id){
	int index = pwzpkg->index;
	int start_utc = START_UTC + index * 30;
	int start_ns  = START_NS;
	pwzpkg->lenLoad = 18062;
	pwzpkg->lenTail = 48;
	pwzpkg->head[0] = 0x51;
	pwzpkg->head[1] = (dev_id & 0xff);
	pwzpkg->head[2] = 0x47;
	pwzpkg->head[3] = 0x02;
	pwzpkg->head[4] = ((start_utc & 0xff000000) >> 24);
	pwzpkg->head[5] = ((start_utc & 0xff0000) >> 16);
	pwzpkg->head[6] = ((start_utc & 0xff00) >> 8);
	pwzpkg->head[7] = (start_utc & 0xff);
	pwzpkg->head[8] = ((start_ns & 0xff000000) >> 24);
	pwzpkg->head[9] = ((start_ns & 0xff0000) >> 16);
	pwzpkg->head[10] = ((start_ns & 0xff00) >> 8);
	pwzpkg->head[11] = (start_ns & 0xff);

	int x,y,z;
	for (int i=0;i<2000;i++){
		x = i*10;
		y = i * 15 + 5;
		z = i * 12 - 45;
		pwzpkg->load[i*9] = (x & 0xff0000) >> 16;	
		pwzpkg->load[i*9+1] = (x & 0xff00) >> 8;	
		pwzpkg->load[i*9+2] = (x & 0xff);	
		pwzpkg->load[i*9+3] = (y & 0xff0000) >> 16;	
		pwzpkg->load[i*9+4] = (y & 0xff00) >> 8;	
		pwzpkg->load[i*9+5] = (y & 0xff);	
		pwzpkg->load[i*9+6] = (z & 0xff0000) >> 16;	
		pwzpkg->load[i*9+7] = (z & 0xff00) >> 8;	
		pwzpkg->load[i*9+8] = (z & 0xff);	
	}
	pwzpkg->index++;
	return 0;
}


int ShowWZPKGInfo(pWZPKG pwzpkg){
	printf("WZPKG index = %d\t",pwzpkg->index);
	int utc = (pwzpkg->head[4] << 24 ) | (pwzpkg->head[5] << 16);
	utc += (pwzpkg->head[6] << 8);
	utc += (pwzpkg->head[7]);	
	printf("utc = 0x%08x\n",utc);

	int x,y,z;
	for(int i=0;i<2000;i++){

	}
	return 0;
}


int BufWZPKG2Raw(pRAWALL prawAll,WZPKG wzpkg){
	pWZPKG pwzpkg = &wzpkg;
	int did = wzpkg.head[1];
//	printf("dev_id = %d\t",did);
	int pos = prawAll->praw[did]->pos_buf;
	int x,y,z;
	int finish = 0;

	if(pos == 0){
		int utc = (pwzpkg->head[4] << 24 ) | (pwzpkg->head[5] << 16);
		utc += (pwzpkg->head[6] << 8);
		utc += (pwzpkg->head[7]);	
		int ns = (pwzpkg->head[8] << 24 ) | (pwzpkg->head[9] << 16);
		ns += (pwzpkg->head[10] << 8);
		ns += (pwzpkg->head[11]);	
		prawAll->praw[did]->utc = utc;
		prawAll->praw[did]->ns  = ns;
	}
	for(int i=0;i<2000;i++)
	{
		x = (wzpkg.load[9*i]<<24) | (wzpkg.load[9*i+1]<<16);
		x += wzpkg.load[9*i+2]<<8;
		y = (wzpkg.load[9*i+3]<<24) | (wzpkg.load[9*i+4]<<16);
		y += wzpkg.load[9*i+5]<<8;
		z = (wzpkg.load[9*i+6]<<24) | (wzpkg.load[9*i+7]<<16);
		z += wzpkg.load[9*i+8]<<8;
		x = x >> 8;
		y = y >> 8;
		z = z >> 8;
		prawAll->praw[did]->x[pos+i] = (S32)x;
		prawAll->praw[did]->y[pos+i] = (S32)y;
		prawAll->praw[did]->z[pos+i] = (S32)z;
	}
	prawAll->praw[did]->pos_buf += 2000;
	if(prawAll->praw[did]->pos_buf >= 60000)
	{
		prawAll->praw[did]->pos_buf %= 60000;
		finish = did;
	}
//	printf("pos = %d\n",prawAll->praw[did]->pos);

	return finish;
}



