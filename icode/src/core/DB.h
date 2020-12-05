/*
 * DB.h
 *
 *  Created on: 12 nov. 2019
 *      Author: azeddine
 */

#ifndef SRC_ICODE_CORE_DB_DB_H_
#define SRC_ICODE_CORE_DB_DB_H_
#include "../icode.h"
typedef unsigned int DBPage;
class DB {
private:
	WFile file;
	WLock lock;
	DBPage end_pos;
	DBPage rm_list;
	DBPage root;
	wint64 file_pos;
	wint64 file_size;
	unsigned short pageSize;
	unsigned short flags;
	void Init();
	int InitFile(int pageSize);
	int CheckFile();
	int WriteEnd(unsigned int sz);
	int NewPagesFromEnd(DBPage *block, int nbpages);
	int FindPagesFromRmList(DBPage *block, int nbpages);
	int NewPages(DBPage *block, wuint nbpages);
	int DeletePages(DBPage blocks, wuint nbpages);
public:
	DB();
	~DB();
	int OpenFile(const char *filename, const char *mode);
	int OpenFile(const char *filename);
	int OpenFileRO(const char *filename);
	int CreateFile(const char *filename, int blockSize = 0);
	bool IsOpened();
	int Alloc(DBPage *pages, wuint size, wuint *size_allocated);
	int Alloc(DBPage *pages, wuint size) {
		return Alloc(pages, size, 0);
	}
	int Free(DBPage pages, wuint size);
	int Realloc(DBPage *pages, wuint newsize, wuint lastsize,
			wuint *size_allocated);
	int Realloc(DBPage *pages, wuint newsize, wuint lastsize) {
		return Realloc(pages, newsize, lastsize, 0);
	}
	int GetRoot(DBPage *root);
	int SetRoot(DBPage root);
	int SeekToPage(DBPage block, int pos);
	int SeekToPage(DBPage block){
		return SeekToPage(block,0);
	}
	int SeekRead(DBPage block, int pos, void *data, wuint size);
	int SeekRead(DBPage block, void *data, wuint size){
		return SeekRead(block,0,data,size);
	}
	int SeekWrite(DBPage block, int pos, const void *data, wuint size);
	int SeekWrite(DBPage block, const void *data, wuint size){
		return SeekWrite(block,0,data,size);
	}
	int Read(void *data, wuint size);
	int Write(const void *data, wuint size);
	void Lock() {
		lock.Lock();
	}
	void UnLock() {
		lock.UnLock();
	}
	void Flush() {
		file.Flush();
	}
};

#endif /* SRC_ICODE_CORE_DB_DB_H_ */
