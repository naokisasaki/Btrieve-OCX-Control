#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <mbstring.h>
#include <mbctype.h>
#include "btrclass.h"

// file informations
#define SPECSIZE    (16 + (16 * 255) + (ACS_SIZE * ACS_NAME_SIZE))

struct {
    BTI_WORD wRecordLength;
    BTI_WORD wPageSize;
    BTI_WORD wIndexCount;
    BTI_ULONG dwRecordCount;
    BTI_WORD wFileFlag;
} btFileSpec;

// Btrieve API prototypesﬂ
BTI_API BTRV(BTI_WORD operation, BTI_VOID_PTR posBlock, BTI_VOID_PTR dataBuffer,
       BTI_WORD_PTR dataLength, BTI_VOID_PTR keyBuffer, BTI_SINT keyNumber );


BTRIEVE::BTRIEVE(const char *btrPath, const char *fifPath)
{
    FILE *fp;
    unsigned int i;
    char readBuf[BUFSIZ + 1];
    char tmpBuf[128];

    // Btrieve file path
    strcpy(szBtrieveFilePath, btrPath);


    // gets the field informations
    if((fp = fopen(fifPath, "r")) == NULL) {
        Status = -1;
        return;
    }

    dataLen = 0;
    fieldCount = 0;

    while(fgets(readBuf, BUFSIZ, fp) != NULL) {
        for(i = 0; i < strlen(readBuf); i++) {
            if(readBuf[i] ==  '#' || readBuf[i] ==  '\n') {
                readBuf[i] = NULL;
                break;
            }
        }

        stroptimize(readBuf);

        if(strlen(readBuf)) {
            strextract(readBuf, 0, tmpBuf, ',');
            stroptimize(tmpBuf);
            field[fieldCount].fieldName = new char[strlen(tmpBuf) + 1];
            strcpy(field[fieldCount].fieldName, tmpBuf);

            strextract(readBuf, 1, tmpBuf, ',');
            field[fieldCount].pos = atoi(tmpBuf);

            strextract(readBuf, 2, tmpBuf, ',');
            field[fieldCount].len = atoi(tmpBuf);

            strextract(readBuf, 3, tmpBuf, ',');
            stroptimize(tmpBuf);
            field[fieldCount].type = GetFieldTypeFromName(tmpBuf);
            //printf("FIELD %d TYPE IS %d\n", fieldCount, field[fieldCount].type);

            dataLen += field[fieldCount].len;
            fieldCount++;
        }
    }

    fclose(fp);

    // Call the Btrieve API

    keyNum = 0;
    dataBuf = new BTI_BYTE[dataLen + 1];
    strcpy((BTI_CHAR *)keyBuf, btrPath);

    Status = BTRV( B_OPEN, posBlock, dataBuf, &dataLen, keyBuf, keyNum );
}

BTRIEVE::~BTRIEVE()
{
    unsigned int i;

    dataLen = 0;
    Status = BTRV( B_CLOSE, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    delete dataBuf;

    for(i = 0; i < fieldCount; i++) {
        delete field[i].fieldName;
    }
}

void BTRIEVE::SetKey(BTI_WORD num)
{
    keyNum = num;
}


//////////////////////////////////////////////////////////////////////////////
// Record Query

BTI_SINT BTRIEVE::GetFirst(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_FIRST, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetLast(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_LAST, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetEqual(const char* lpszFindKey)
{
    strcpy((char *)keyBuf, lpszFindKey);
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_EQUAL, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetGT(const char* lpszFindKey)
{
    strcpy((char *)keyBuf, lpszFindKey);
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_GT, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetGTorEQ(const char* lpszFindKey)
{
    strcpy((char *)keyBuf, lpszFindKey);
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_GE, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetLT(const char* lpszFindKey)
{
    strcpy((char *)keyBuf, lpszFindKey);
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_LT, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetLTorEQ(const char* lpszFindKey)
{
    strcpy((char *)keyBuf, lpszFindKey);
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_LE, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetNext(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_NEXT, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::GetPrev(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_GET_PREVIOUS, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::StepFirst(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_STEP_FIRST, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::StepLast(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_STEP_LAST, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::StepNext(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_STEP_NEXT, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}

BTI_SINT BTRIEVE::StepPrev(void)
{
    memset(dataBuf, 0, dataLen);
    Status = BTRV( B_STEP_PREVIOUS, posBlock, dataBuf, &dataLen, keyBuf, keyNum );

    return Status;
}


//////////////////////////////////////////////////////////////////////////////
// Record Insert, Update, Delete...

BTI_SINT BTRIEVE::Insert(void)
{
    Status = BTRV( B_INSERT, posBlock, dataBuf, &dataLen, keyBuf, keyNum );
    return Status;
}

BTI_SINT BTRIEVE::Update(void)
{
    Status = BTRV( B_UPDATE, posBlock, dataBuf, &dataLen, keyBuf, keyNum );
    return Status;
}

BTI_SINT BTRIEVE::Delete(void)
{
    Status = BTRV( B_DELETE, posBlock, dataBuf, &dataLen, keyBuf, keyNum );
    return Status;
}

BTI_SINT BTRIEVE::AllDelete(void)
{
    BTI_BYTE byteFileSpec[SPECSIZE];
    BTI_WORD bwFileBufLen = BTI_WORD(SPECSIZE);
    char szTemp[256];

    Status = BTRV(B_STAT, posBlock, &byteFileSpec, &bwFileBufLen, szTemp ,0);
    if(Status) {
        return Status;
    }

    Status = BTRV(B_CLOSE, posBlock, dataBuf, &dataLen, keyBuf, keyNum);
    if(Status) {
        return Status;
    }

    Status = BTRV(B_CREATE, posBlock, &byteFileSpec, &bwFileBufLen, szBtrieveFilePath, 0);
    if(Status) {
        return Status;
    }

    return BTRV(B_OPEN, posBlock, dataBuf, &dataLen, keyBuf, keyNum);
}

BTI_ULONG BTRIEVE::GetRecordCount(void)
{
    BTI_BYTE byteFileSpec[SPECSIZE];
    BTI_WORD bwFileBufLen = BTI_WORD(SPECSIZE);
    char szTemp[64];

    Status = BTRV(B_STAT, posBlock, &byteFileSpec, &bwFileBufLen, szTemp ,0);

    if(Status) {
        return 0;
    } else {
        memcpy(&btFileSpec, byteFileSpec, sizeof(btFileSpec));
        return btFileSpec.dwRecordCount;
    }
}

//////////////////////////////////////////////////////////////////////////////
// Field Access

BTI_WORD BTRIEVE::GetRecordBuffer(BTI_BYTE *buf)
{
    memcpy((char *)buf, (char *)dataBuf, dataLen);
    return dataLen;
}

int BTRIEVE::GetFieldCount(void)
{
    return fieldCount;
}

unsigned short BTRIEVE::GetFieldType(unsigned short fieldNo)
{
    if(fieldNo > fieldCount) return BTF_INVALIDTYPE;
    return field[fieldNo].type;
}

unsigned int BTRIEVE::GetFieldLength(unsigned short fieldNo)
{
    if(fieldNo > fieldCount) return 0;
    return field[fieldNo].len;
}

char* BTRIEVE::GetFieldName(unsigned short fieldNo)
{
    if(fieldNo > fieldCount) return NULL;
    return field[fieldNo].fieldName;
}

void BTRIEVE::ClearField(void)
{
    memset(dataBuf, NULL, dataLen);
}

char *BTRIEVE::GetStringField(unsigned short fieldNo, char *str)
{
    if(fieldNo > fieldCount) return NULL;

    strncpy(str, (char *)dataBuf + field[fieldNo].pos - 1, field[fieldNo].len);
    str[field[fieldNo].len] = NULL;

    return str;
}

void BTRIEVE::PutField(unsigned short fieldNo, const char *str)
{
    if(fieldNo > fieldCount) return;

    char* strTemp = new char[strlen(str) + 1];

    memset(dataBuf + field[fieldNo].pos - 1, NULL, field[fieldNo].len);

    switch(field[fieldNo].type) {
    case BTF_STRING:
        strncpy((char *)dataBuf + field[fieldNo].pos - 1, str, field[fieldNo].len);
        break;
    case BTF_STRNUMBER:
        GetNumberFromString(strTemp, str, field[fieldNo].len, ' ');
        strncpy((char *)dataBuf + field[fieldNo].pos - 1, strTemp, field[fieldNo].len);
        break;
    case BTF_CODE:
        GetNumberFromString(strTemp, str, field[fieldNo].len, '0');
        strncpy((char *)dataBuf + field[fieldNo].pos - 1, strTemp, field[fieldNo].len);
        break;
    }

    delete strTemp;
}

void BTRIEVE::PutField(unsigned short fieldNo, long value)
{
    if(fieldNo > fieldCount) return;

    char *tempBuf = new char[field[fieldNo].len + 1];

    if(field[fieldNo].type == BTF_CODE)
        sprintf(tempBuf, "%0*ld", field[fieldNo].len, value);
    else
        sprintf(tempBuf, "%*ld", field[fieldNo].len, value);

    memset(dataBuf + field[fieldNo].pos - 1, NULL, field[fieldNo].len);
    strncpy((char *)dataBuf + field[fieldNo].pos - 1, tempBuf, field[fieldNo].len);

    delete tempBuf;
}





/***********************************************************************/
/*   BTRV                Call Btrieve API                              */
/***********************************************************************/
BTI_API BTRV(BTI_WORD operation, BTI_VOID_PTR posBlock, BTI_VOID_PTR dataBuffer,
           BTI_WORD_PTR dataLength, BTI_VOID_PTR keyBuffer, BTI_SINT keyNumber )
{
   BTI_BYTE keyLength  = MAX_KEY_SIZE;
   BTI_CHAR ckeynum    = (BTI_CHAR)keyNumber;
   BTI_ULONG dataLen32 = 0;
   BTI_SINT status = 0;

   if ( dataLength != NULL )
      dataLen32 = *dataLength;

   status = BTRCALL (
              operation,
              posBlock,
              dataBuffer,
              &dataLen32,
              keyBuffer,
              keyLength,
              ckeynum );

   if ( dataLength != NULL )
      *dataLength = (BTI_WORD)dataLen32;

   return status;
}

/***********************************************************************/
/*   stroptimize         Optimize Strings                              */
/***********************************************************************/
char* BTRIEVE::stroptimize(char *str)
{
    short   len = strlen(str) - 1, i;
    char    tmp[256];


    // delete trailing spaces
    for(i = len; i; i--) {
        if(str[i] == ' ' && _mbsbtype((const unsigned char *)str, i) == _MBC_SINGLE)
            str[i] = 0x00;
        else
            break;
    }


    // delete leading spaces
    strcpy(tmp, str);
    len = strlen(str);

    for(i = 0; i < len; i++) {
        if(str[i] != ' ' || _mbsbtype((const unsigned char *)str, i) != _MBC_SINGLE)
            break;
    }

    strcpy(str, tmp + i);


    return str;
}

//***************************************************************************
//  FUNCTION: strextract
//  PURPOSE:  extract from comma separated string
//***************************************************************************
short BTRIEVE::strextract(const char *str, unsigned short pos, char *buf, char separater)
{
    unsigned short  i, ii = 0, no = 0;


    for(i = 0; i < strlen(str); i++) {
        if(_mbsbtype((const unsigned char*)str, i) <= _MBC_SINGLE && str[i] == separater) {
            no++;
        }

        if(no == pos) {
            if(no) i++;

            while(1) {
                if(_mbsbtype((const unsigned char*)str, i + ii) <= _MBC_SINGLE) {
                    if(str[i + ii] == separater || str[i + ii] == '\0' || str[i + ii] == '\n' || str[i + ii] == '\r') {
                        buf[ii] = 0x00;
                        return 0;
                    }
                }

                buf[ii] = str[i + ii];
                ii++;
            }
        }
    }

    return 1;
}

/***********************************************************************/
/*   GetFieldTypeFromName  get field type from string                  */
/***********************************************************************/
unsigned short BTRIEVE::GetFieldTypeFromName(const char *str)
{
    if(!stricmp("STRING", str)) {
        return BTF_STRING;
    } else if(!stricmp("STRNUMBER", str)) {
        return BTF_STRNUMBER;
    } else if(!stricmp("CODE", str)) {
        return BTF_CODE;
    }

    return BTF_INVALIDTYPE;
}

/***********************************************************************/
/*   GetNumberFromString                                               */
/***********************************************************************/
void BTRIEVE::GetNumberFromString(char *strnum, const char *str, unsigned int len, char sup)
{
    if(!len) return;

    char *strTemp = new char[strlen(str) + 1];
    unsigned int num = 0;

    for(int pos = 0; pos < (int)strlen(str); pos++) {
        if(isdigit(str[pos])) {
            strTemp[num++] = str[pos];
        }
    }

    for(pos = len - 1; pos >= 0; pos--) {
        if(num) {
            strnum[pos] = strTemp[--num];
        } else {
            strnum[pos] = sup;
        }
    }

    strnum[len] = NULL;

    delete strTemp;
}
