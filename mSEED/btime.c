#include <stdio.h>
#include <time.h>

#include "types.h"
#include "mtypes.h"
#include "btime.h"
#include "alg_head.h"

#define SEC1  1000000000


int TestTime(){
	printf("TestTime...\n");
	time_t now;
	struct tm * tmNow;
	char  * cNow;
	time(&now);
	printf("sizeof now = %ld\n",sizeof(time_t));
	printf("now = %ld\n",now);
	tmNow = gmtime(&now);
	cNow = ctime(&now);
	printf("cNow = %s",cNow);

	time_t mod1;
	char * cMod1;
	mod1 = now - 86400;
	cMod1 = ctime(&mod1);
	printf("cMod1 = %s",cMod1);

	time_t mod2;
	mod2 = 17532 * 86400 - 3600 * 8;
	char * cMod2;
	cMod2 = ctime(&mod2);
	printf("cMod2 = %s",cMod2);
	return 0;
}


int CovWZ2BTIME(pBTIME pbtime,WZPKG wzpkg){
	time_t tt;
	time(&tt);
	struct tm *tm_tt;
	tm_tt = gmtime(&tt);
	pbtime->year = tm_tt->tm_year + 1900;
	pbtime->day = TT2Day(tm_tt);
	pbtime->hour = tm_tt->tm_hour;
	pbtime->min  = tm_tt->tm_min;
	pbtime->sec  = tm_tt->tm_sec;
	pbtime->us100 = 0; 

	return 0;
}



int CovU2BTIME(pBTIME pbtime,U32 utc,U32 uns,int pos,S16 rate){
	time_t base;
	int SEC1_us = SEC1 / 1000;
	//base = 17532 * 86400 - 3600 * 8;
	base = 17532 * 86400;
	ChangeEndianS16(&rate);
	U32 period_sample_us = SEC1_us / rate ;
	U32 uus = uns /1000;

	long usStart = uus + pos * period_sample_us;	
	int  utc_mod = usStart / (SEC1_us);
	long usStart_mod = usStart % SEC1_us;
	time_t tStart;
	tStart = base + utc + utc_mod;


	struct tm *tm_tt;
	tm_tt = gmtime(&tStart);
	pbtime->year = tm_tt->tm_year + 1900;
	pbtime->day = TT2Day(tm_tt);
	pbtime->hour = tm_tt->tm_hour;
	pbtime->min  = tm_tt->tm_min;
	pbtime->sec  = tm_tt->tm_sec;
	pbtime->us100 = usStart_mod / 100; 


	char * cStart;
	cStart = ctime(&tStart);
//	printf("ConvU2Btime:pos=%d,usStart_mod=%ld,cStart=%s",pos,usStart_mod,cStart);
//	printf("utc_mod=%d,us100=%d\n",utc_mod,pbtime->us100);

//	pbtime->hour = 12;
//	pbtime->min  = 15;
//	pbtime->sec  = 18;
//	pbtime->us100 = 3700; 

	ChangeEndianU16(&(pbtime->year));
	ChangeEndianU16(&(pbtime->day));
	ChangeEndianU16(&(pbtime->us100));

	return 0;
}


int TT2Day(struct tm *tm_tt){
	int yday = tm_tt->tm_yday;
	yday++;
//	printf("TT2Day: ydat = %d\n",yday);
	return yday;
}




