#ifndef __TYPES_H
#define __TYPES_H


typedef unsigned char UCHAR;

typedef struct {
	char * device;// "/dev/spidev0.0"--spi1     "/dev/spidev1.0"--spi2
	UCHAR * mode;//  模式
	UCHAR bits;// bits=8
	int   speed;//  speed=20000000
	int   delay;//  delay
	int   fd;
	UCHAR status;//返回状态  0--成功 1--失败  输出参数
	UCHAR res;//   保留
} SPI, *pSPI;

typedef struct {
	UCHAR devid;// 设备ID 输入参数
	UCHAR rw;//    读写指示 0--读  1--写  输入参数
	UCHAR modid;// 高位地址  输入参数
	UCHAR addr;//  低位地址  输入参数
	UCHAR data;//  写入数据  输入参数
	UCHAR q;//     返回数据  输出参数
	UCHAR status;//返回状态  0--成功 1--失败  输出参数
	UCHAR res;//   保留
} CMD, *pCMD;

 
typedef struct { 
	int lenLoad; // 包长度，传入参数，按字节计算，默认值为：18062
	int lenTail;	//no crc 保卫 参数输入，不含crc 长度 默认值：48
	UCHAR head[12]; // 包头12个字节，填入
	UCHAR load[18000];//数据 填入
	UCHAR tail[1000];//数据 填入
	UCHAR crc[2];// 填入
	int index;// 填入，没收到一个包加一(++) 
	int res;//保留
}	WZPKG,*pWZPKG;


typedef struct {
	int  port;
	char ip[20];
	int  status;
	int  pushOrNot;
} RHOST, *pRHOST;


typedef struct {
	char fNameDef[250];
	char fName[250];
	int fUsedID;
	int saveOrNot;
	int numOfPkgPreFile;
} FDIR, *pFDIR;		

typedef struct {
	char  fNameDef[250];
	char	fNameSeed[250];
	int 	fUsedID;
	FDIR	fileDir;
	RHOST remoteHost;
} CFG, *pCFG;


#endif
