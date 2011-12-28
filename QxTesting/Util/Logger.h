/************************************************************************/
/* �g�Jlog����ɮסA�~���復���ާ@�D�n�z�L3��macro MDebug MTrace MAssert                                                                     
/************************************************************************/
#ifndef _HISTORY_LOGGER_H_
#define _HISTORY_LOGGER_H_

#include <cassert>
#include <iostream>

#include <boost/date_time.hpp>
#include <boost/thread.hpp>

using namespace std;

class Logger{
public:
	~Logger();
	static Logger* getInstance();

	void log(string fileName,string funcName,int lineNumber);
	void log(string text,string fileName,string funcName,int lineNumber);
	void debug(string text,string fileName,string funcName,int lineNumber);
protected:
	Logger();
	static Logger* singleton;

	ofstream* afs;
	ofstream* dfs;
	boost::mutex fmtx;

	const static string ASSERTS;
	const static string MESSAGE;
	const static string EXCEPTS;
};

/** MAssert , �p�G�bdebug�Ҧ��U�A����assert �A�p�G�brelease�Ҧ��U�A�h�N���T���g�Jlog�� */ 
#ifdef _DEBUG
#define MASSERT(x) if(!(x)){ assert(x);}
#else
#define MASSERT(x) if(!(x)){ Logger::getInstance()->log(__FILE__,__FUNCTION__,__LINE__);}
#endif

/** MTrack , �N���w�T�������g�Jlog��(shell.txt)*/
#define MTRACK(x) Logger::getInstance()->log(x,__FILE__,__FUNCTION__,__LINE__);
/** MDebug , �N���w�T�������g�Jlog��(debug.txt)�A�|�M�H�W���Ϥ��O�]�� shell.txt�t�����e
    �]�s�]�����A���ɫ�u�O�Q�ݳ�@�T���N�z�Lmdebug�Ӭ�*/
#define MDEBUG(x) Logger::getInstance()->debug(x,__FILE__,__FUNCTION__,__LINE__);

#endif
