#include "pch.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef COCOS2D_DEBUG
	#include "cocos2d.h"
	USING_NS_CC;
#endif
time_t getNow() {
	return time(0);
}

string getRomeNumber(int n) {
	string sz[] = { "0", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"
		, "X", "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX" 
		, "XX", "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX"
		, "XXX", "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX"
	};
	return sz[n];
}

void sleepThisThread(size_t msec) {
	std::this_thread::sleep_for(std::chrono::milliseconds(msec));
}
int getRandValueOverZero(int max) {
	int n = getRandValue(max);
	if (n == 0)
		n = 1;
	return n;
}

int getRandValueMinMax(int min, int max) {
    int val = max - min;
    int ran = getRandValue(val);
    return min + ran;
}

int getRandValue(int max) {
	if (max == 0)
		return 0;
	return rand() % max;
}

int rounding(float f) {
	return (int)round(f);
}

string loadJsonString(const char *path) {
	ifstream fileopen;
	string szPath = "resource/";
	szPath += path;
	fileopen.open(szPath.c_str(), ios::in | ios::binary);
	string str((std::istreambuf_iterator<char>(fileopen)), std::istreambuf_iterator<char>());
	fileopen.close();

	return str;
}

void saveFile(const char* path, string sz) {
#if defined(_WIN32) && !defined(COCOS2D_DEBUG)
	std::ofstream out(path);
	out << sz;
	out.close();
#else
    /*
    string fullPath = FileUtils::getInstance()->getWritablePath() + path;

	bool ret = FileUtils::getInstance()->writeStringToFile(sz
            , fullPath
    );
	if(!ret)
		CCLOG("failure save Actor");
*/
#endif
}

time_t getTime(int hour, int min, int sec) {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	ltm->tm_hour = hour;
	ltm->tm_min = min;
	ltm->tm_sec = sec;

	return mktime(ltm);

}
tm * getLocalTm(time_t t) {
	return localtime(&t);
}

string wstring_to_utf8(const wstring& str) {
	return wstring_to_utf8(str, false);
}
string wstring_to_utf8(const wstring& str, bool isLabel)
{
#if defined _WIN32 && defined(COCOS2D_DEBUG)
	UINT type = CP_UTF8;
	if (isLabel)
		type = CP_UTF8;

	int len = WideCharToMultiByte(type, 0, &str[0], -1, NULL, 0, NULL, NULL);
	string strMulti(len, 0); 
	WideCharToMultiByte(type, 0, &str[0], -1, &strMulti[0], len, NULL, NULL);

	return strMulti;

#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(str);
#endif
}

wstring utf8_to_utf16(const string& str){
#if defined _WIN32 && defined(COCOS2D_DEBUG)
	int nLen = MultiByteToWideChar(CP_UTF8, 0, &str[0], str.size(), NULL, NULL);
	wstring strUnicode(nLen, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], str.size(), &strUnicode[0], nLen);
	return strUnicode;

#else
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.from_bytes(str);
#endif
}

float getTouchRatio(float sec, int cnt){
	const float max = 35.0f; //초당 최대
	/*
	1:max = sec: X
	X = max * sec
	return cnt/X
	*/
	return min(1.f, ((float)cnt / (max * sec)));
}
wstring sprint(const wstring format, int val) {
    wstring str = format;
    wstring str2 = L"%d";
    str.replace(str.find(str2),str2.length(),to_wstring(val));
	return str;
}

string sprint(const char * format, ...) {
	char buffer[512] = { 0, };
	va_list args;
	va_start(args, format);
	//int len =
    vsnprintf(buffer, 512, format, args);
	//fputws(buffer, stdout);
	va_end(args);
	string sz = buffer;
	return sz;
}

string numberFormat(int n) {
    string sz = "";
    bool isInit = true;
    while(true){
        if(n == 0)
            break;
        
        int r = n % 1000;
        n = n / 1000;
        
        if(!isInit) {
            if(r == 0 && n > 0)
                sz = "000," + sz;
            else if(r < 10 && n > 0)
                sz = "00" + to_string(r) + "," + sz;
            else if(r < 100 && n > 0)
                sz = "0" + to_string(r) + "," + sz;
            else {
                sz = to_string(r) + "," + sz;
            }
        }
        else {
            if(r == 0 && n > 0)
                sz = "000";
            else if(r < 10 && n > 0)
                sz = "00" + to_string(r);
            else if(r < 100 && n > 0)
                sz = "0" + to_string(r);
            else
                sz = to_string(r);
            isInit = false;
        }
    }
    return sz;
}

string getRankString(int rank) {
    string postfix;
    switch(rank) {
        case 1: postfix = "st";
            break;
        case 2: postfix = "nd";
            break;
        case 3: postfix = "rd";
            break;
        default: postfix = "th";
            break;
    }
    const string sz = to_string(rank) + postfix;
    return sz;
}
/*
char* intToChar(int n) {
	char *buf = new char[10];
	return ::itoa(n, buf, 10);
	
}
 */
/*
wstring utf8_to_utf16(const string& utf8)
{
	std::vector<unsigned long> unicode;
	size_t i = 0;
	while (i < utf8.size())
	{
		unsigned long uni;
		size_t todo;
		//bool error = false;
		unsigned char ch = utf8[i++];
		if (ch <= 0x7F)
		{
			uni = ch;
			todo = 0;
		}
		else if (ch <= 0xBF)
		{
			throw std::logic_error("not a UTF-8 string");
		}
		else if (ch <= 0xDF)
		{
			uni = ch & 0x1F;
			todo = 1;
		}
		else if (ch <= 0xEF)
		{
			uni = ch & 0x0F;
			todo = 2;
		}
		else if (ch <= 0xF7)
		{
			uni = ch & 0x07;
			todo = 3;
		}
		else
		{
			throw std::logic_error("not a UTF-8 string");
		}
		for (size_t j = 0; j < todo; ++j)
		{
			if (i == utf8.size())
				throw std::logic_error("not a UTF-8 string");
			unsigned char ch = utf8[i++];
			if (ch < 0x80 || ch > 0xBF)
				throw std::logic_error("not a UTF-8 string");
			uni <<= 6;
			uni += ch & 0x3F;
		}
		if (uni >= 0xD800 && uni <= 0xDFFF)
			throw std::logic_error("not a UTF-8 string");
		if (uni > 0x10FFFF)
			throw std::logic_error("not a UTF-8 string");
		unicode.push_back(uni);
	}
	std::wstring utf16;
	for (size_t i = 0; i < unicode.size(); ++i)
	{
		unsigned long uni = unicode[i];
		if (uni <= 0xFFFF)
		{
			utf16 += (wchar_t)uni;
		}
		else
		{
			uni -= 0x10000;
			utf16 += (wchar_t)((uni >> 10) + 0xD800);
			utf16 += (wchar_t)((uni & 0x3FF) + 0xDC00);
		}
	}
	return utf16;
}
*/
