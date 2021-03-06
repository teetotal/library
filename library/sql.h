
#ifndef PROJ_ANDROID_SQL_H
#define PROJ_ANDROID_SQL_H

#if defined(_WIN32) && !defined(COCOS2D_DEBUG)

#else
	#include "sqlite3/include/sqlite3.h"
#endif

#include "pch.h"

class Sql {
public:
	Sql() {
	};
	~Sql() {
        if (hInst != NULL) {
			delete(hInst);
            hInst = NULL;
        }
	};
	static Sql * inst() {
        if (hInst == NULL) {
            hInst = new Sql;
        }
		return hInst;
	};

	bool init(string path);
	void finalize() {
		sqlite3_close(mDB);
	};
    int exec(const char* query);
	int exec(string query);
	sqlite3_stmt * select(string query);

private:
	static Sql * hInst;
	sqlite3 *mDB;
	mutex mLock;
};

#endif 
