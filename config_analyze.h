#ifndef __CONFIG_ANALYZE_H
#define __CONFIG_ANALYZE_H


int GetConfig(pCFG pcfg);
int CheckCfgFileExist(char * fn);
int SetDefaultCfg(pCFG pcfg);
int SetConfig(pCFG pcfg,char* fn);
int SeperateKey(char * key,char * value,const char * txtLine);
int SetKeyValue(pCFG pcfg,const char * key,const char * value);

#endif
