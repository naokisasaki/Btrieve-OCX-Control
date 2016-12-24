#ifndef _BTRCLASS_H_INCLUDED

#include "btrconst.h"
#include "btitypes.h"
#include "btrapi.h"

// FIELD TYPE
#define BTF_STRING      0
#define BTF_STRNUMBER   1
#define BTF_CODE        2
#define BTF_INVALIDTYPE 999

class BTRFIELD {
private:

public:
    char *fieldName;
    unsigned int pos;
    unsigned int len;
    unsigned short type;
};


class BTRIEVE {
private:
    BTI_BYTE posBlock[128];
    BTI_WORD dataLen;
    BTI_BYTE *dataBuf;
    BTI_BYTE keyBuf[256];
    BTI_WORD keyNum;

    unsigned int fieldCount;
    BTRFIELD field[255];

	char szBtrieveFilePath[256];

	// ì‡ïîÕŸ ﬂä÷êî
	char *stroptimize(char *str);
	short strextract(const char *str, unsigned short pos, char *buf, char separater);
	unsigned short GetFieldTypeFromName(const char *str);
	void GetNumberFromString(char *strnum, const char *str, unsigned int len, char sup);

public:
    BTRIEVE(const char *btrPath, const char *fifPath);
    ~BTRIEVE();

	BTI_SINT Status;

    void SetKey(BTI_WORD num);

    // Field Access
    BTI_WORD GetRecordBuffer(BTI_BYTE *buf);
    char *GetStringField(unsigned short fieldNo, char *str);
    void PutField(unsigned short fieldNo, const char *str);
    void PutField(unsigned short fieldNo, long value);
    void ClearField(void);
    int GetFieldCount(void);
    unsigned short GetFieldType(unsigned short fieldNo);
    unsigned int GetFieldLength(unsigned short fieldNo);
    char *GetFieldName(unsigned short fieldNo);
	BTI_ULONG GetRecordCount(void);

    // Query
    BTI_SINT GetFirst(void);
    BTI_SINT GetLast(void);
    BTI_SINT GetNext(void);
    BTI_SINT GetPrev(void);
    BTI_SINT GetEqual(const char* lpszFindkey);
	BTI_SINT GetGT(const char* lpszFindKey);
	BTI_SINT GetGTorEQ(const char *lpszFindkey);
	BTI_SINT GetLT(const char* lpszFindKey);
	BTI_SINT GetLTorEQ(const char *lpszFindkey);
    BTI_SINT StepFirst(void);
    BTI_SINT StepLast(void);
    BTI_SINT StepNext(void);
    BTI_SINT StepPrev(void);

    // Insert Etc...
    BTI_SINT Insert(void);
    BTI_SINT Update(void);
    BTI_SINT Delete(void);
    BTI_SINT AllDelete(void);

};

#define _BTRCLASS_H_INCLUDED
#endif