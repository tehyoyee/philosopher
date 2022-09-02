/**********************************************************************
* ex_opt.c                                                            *
* exmple source – using option                                        *
**********************************************************************/

#include <stdio.h>
#include <unistd.h>

extern char *optarg;

void AddProc();
void ListProc();
void Usage(const char *pname);
int main(int argc, char **argv)
{
    int option=0;

    while((option = getopt(argc, argv, "a:l"))!=EOF)
    {
        switch(option)
        {
            case 'a': AddProc(); break;
            case 'l': ListProc(); break;
            default: Usage(argv[0]); break;
        }
    }
    printf("good bye...\n");
    return 0;
}

void AddProc()
{
    printf("=== Add Proc ===\n");
    printf("Add parameter is %s\n", optarg);
}

void ListProc()
{
    printf("=== List Proc ===\n");
}

void Usage(const char *pname)
{
    printf("Usage: %s [options]\n",pname);
    printf("option: [a] | [l] \n");
    printf("a need Add parameter\n");
    printf("ex) %s -a Hello\n", pname);
    printf("ex) %s -l\n", pname);
}