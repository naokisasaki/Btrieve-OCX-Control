#include <stdio.h>
#include <stdlib.h>
#include <mbstring.h>
#include <mbctype.h>
#include "..\btrclass.h"


void usage(void)
{
    fprintf(stderr, "Usage: btrconv [are] [-hf] [Btrieve file name] [CSV file name]\n\n");
    fprintf(stderr, "[Btrieve filen name] is not be specified file extension. to be '*.DAT' or '*.FIF' automatically.\n");
    fprintf(stderr, "[CSV file name ] is specify with file extension. CSV formats are not supported with surrounding \"\".\n\n");
    fprintf(stderr, "    command: a  append CSV file to Btrieve file.\n");
    fprintf(stderr, "             r  before remove on Btrieve records, after append from CSV file.\n");
    fprintf(stderr, "             e  write all Btrieve file records to CSV file.\n\n");
    fprintf(stderr, "    option: -h  first line in the CSV file be the title.\n");
    fprintf(stderr, "            -f  output the field analysis information.\n");
    exit(1);
 }

char* stroptimize(char *str)
{
    short   len = strlen(str) - 1, i;
    char    tmp[256];


    // delete trailing space
    for(i = len; i; i--) {
        if(str[i] == ' ' && _mbsbtype((const unsigned char *)str, i) == _MBC_SINGLE)
            str[i] = 0x00;
        else
            break;
    }

    // delete leadeing space
    strcpy(tmp, str);
    len = strlen(str);

    for(i = 0; i < len; i++) {
        if(str[i] != ' ' || _mbsbtype((const unsigned char *)str, i) != _MBC_SINGLE)
            break;
    }

    strcpy(str, tmp + i);

    return str;
}

short extract(const char *str, unsigned short pos, char *buf)
{
    unsigned short  i, ii = 0, no = 0;


    for(i = 0; i < strlen(str); i++) {
        if(_mbsbtype((const unsigned char*)str, i) <= _MBC_SINGLE && str[i] == ',') {
            no++;
        }

        if(no == pos) {
            if(no) i++;

            while(1) {
                if(_mbsbtype((const unsigned char*)str, i + ii) <= _MBC_SINGLE) {
                    if(str[i + ii] == ',' || str[i + ii] == '\0' || str[i + ii] == '\n' || str[i + ii] == '\r') {
                        buf[ii] = NULL;
                        return TRUE;
                    }
                }

                buf[ii] = str[i + ii];
                ii++;
            }
        }
    }

    buf = NULL;

    return FALSE;
}

#define MODE_INVALID 0
#define MODE_APPEND  1
#define MODE_REPLACE 2
#define MODE_EXTRACT 3


int main(int argc, char **argv)
{
    int iCommand = MODE_INVALID;
    int bHeader = FALSE;
    int bFieldView = FALSE;
    int i;

    fprintf(stderr, "Btrieve File Converter    Jul.1997 by N.Sasaki\n\n");

    if(argc < 4) {
        usage();
    }

    // analyze command line
    switch(tolower(*argv[1])) {
    case 'a':
        iCommand = MODE_APPEND;
        break;
    case 'r':
        iCommand = MODE_REPLACE;
        break;
    case 'e':
        iCommand = MODE_EXTRACT;
        break;
    default:
        usage();
        break;
    }

    // analyze option paramaters
    int procargc = 2;
    while(procargc < argc) {
        if(argv[procargc][0] == '-') {
            switch(tolower(argv[procargc][1])) {
            case 'h':
                bHeader = TRUE;
                break;
            case 'f':
                bFieldView = TRUE;
                break;
            }
            procargc++;

        } else {
            break;
        }
    }


    char datName[256], fifName[256];
    sprintf(datName, "%s.DAT", argv[procargc]);
    sprintf(fifName, "%s.FIF", argv[procargc]);

    BTRIEVE bt(datName, fifName);

    if(bt.Status) {
        fprintf(stderr, "%s and /or %s is not exists or broken.\n", datName, fifName);
        exit(1);
    }
    procargc++;


    FILE *fp;

    if(iCommand == MODE_EXTRACT) {
        if((fp = fopen(argv[procargc], "wt")) == NULL) {
            fprintf(stderr, "doesn't access %s.\n", argv[procargc]);
            exit(1);
        }
    } else {
        if((fp = fopen(argv[procargc], "rt")) == NULL) {
            fprintf(stderr, "%s is not exists or broken.\n", argv[procargc]);
            exit(1);
        }
    }


    // Replaceｺﾏﾝﾄﾞの場合Btrieveﾌｧｲﾙから削除
    if(iCommand == MODE_REPLACE) {
        fprintf(stdout, "currently exists %ld records.\n", bt.GetRecordCount());
        if(bt.AllDelete()) {
            fprintf(stdout, "error has occurred in remove all records from Btrieve file (%d).\n", bt.Status);
            fprintf(stdout, "exitted with ignored error\n");
            fclose(fp);
            exit(1);
        } else {
            fprintf(stdout, "all records has removed.\n");
        }
    }



    char buffer[BUFSIZ];
    char field[BUFSIZ];
    int fld;
    int lineCount = 0, badCount = 0, goodCount = 0;


    // -h: header option
    if(bHeader) {
        if(iCommand == MODE_EXTRACT) {
            for(i = 0; i < bt.GetFieldCount(); i++) {
                fprintf(fp, "%s", bt.GetFieldName(i));
                if(i != bt.GetFieldCount() - 1) {
                    fprintf(fp, ",");
                }
            }
            fprintf(fp, "\n");
        } else {
            fgets(buffer, BUFSIZ, fp);
        }
        
        lineCount++;
    }


    if(iCommand == MODE_EXTRACT) {
        bt.GetFirst();

        while(!bt.Status) {
            for(i = 0; i < bt.GetFieldCount(); i++) {
                strcpy(field, bt.GetStringField(i, field));
                fprintf(fp, "%s", stroptimize(field));
                if(i != bt.GetFieldCount() - 1) {
                    fprintf(fp, ",");
                }
            }
            fprintf(fp, "\n");
            lineCount++;

            if(!(lineCount % 20))
                fprintf(stderr, "%d records\r", lineCount);

            bt.GetNext();
        }

        fprintf(stdout, "successfully processed. (writed %d records)\n", lineCount);

    } else {

        while(fgets(buffer, BUFSIZ, fp) != NULL) {
            if(*buffer == '\n')
                continue;

            if(bFieldView) {
                fprintf(stdout, "[%5ld]-------------------\n", lineCount + 1);
            }

            bt.ClearField();

            for(fld = 0; fld < bt.GetFieldCount(); fld++) {
                extract(buffer, fld, field);
                bt.PutField(fld, field);

                if(bFieldView) {
                    fprintf(stdout, "%02d[%s]\n", fld + 1, field);
                }
            }

            bt.Insert();

            if(bt.Status) {
                fprintf(stdout, "doesn't insert %d line in CSV file.\n", lineCount + 1);
                badCount++;
            } else {
                goodCount++;
            }

            lineCount++;

            if(!(lineCount % 20))
                fprintf(stderr, "%d records\r", lineCount);
        }

        fprintf(stdout, "successfully processed.  (readed %d lines, inserted %d lines, errro occurred %d lines)\n",
            lineCount, goodCount, badCount);
    }

    fclose(fp);


    return 0;
}
