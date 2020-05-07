#include <stdio.h>
#include <string.h>

#define TITLE       "off2lua v1.0.0\n"
#define ERROR       -999
#define PATH_SIZE   500
#define OFF_LIMIT   1000

struct t_arg{
    char ifpath[PATH_SIZE];
    char ofpath[PATH_SIZE];
};

struct t_off{
    char lines[OFF_LIMIT][3];
};

typedef struct t_arg ARG;
typedef struct t_off OFF;

void show_hlp();
void load_off(char *fpath, OFF *off);
void save_lua(char *fpath, OFF *off);
void copy_arg(char**argv, char *ptr);
void load_arg(int argc, char **argv, ARG *arg);
void vali_arg(ARG *arg, int *stat);

int main(int argc, char**argv)
{
    ARG arg;
    OFF off;
    int stat;

    printf(TITLE);
    
    load_arg(argc, argv, &arg);
    vali_arg(&arg, &stat);

    if (stat == ERROR)
    {
        show_hlp();
        return 0;
    }

    load_off(arg.ifpath, &off);
    save_lua(arg.ofpath, &off);

    return 0;
}

void show_hlp()
{
    printf("\nusage:\n");
    printf("\toff2lua <input file> <ouput file>\n\n");
}

void load_off(char *fpath, OFF *off)
{
    printf("Loading model from %s\n", fpath);
}

void save_lua(char *fpath, OFF *off)
{
    printf("Saving model to %s\n", fpath);
}

void vali_arg(ARG *arg, int *stat)
{
    if (strlen(arg->ifpath) == 0)
        *stat = ERROR;

    if (strlen(arg->ofpath) == 0)
        *stat = ERROR;
}

void copy_arg(char**argv, char *ptr)
{
    if (*argv != NULL)
        strcpy(ptr, *argv);
}

void load_arg(int argc, char **argv, ARG *arg)
{
    argv++;
    copy_arg(argv, arg->ifpath);
    argv++;
    copy_arg(argv, arg->ofpath);
}