#include <stdio.h>
#include <string.h>

#define TITLE       "\toff2lua v1.0.0\n"
#define UNDERLINE    "===============================\n"

#define ERROR       -999

#define PATH_SIZE   500
#define OFF_LINE_SIZE 50
#define OFF_FILE_SIZE 5000

struct t_arg{
    char ifpath[PATH_SIZE];
    char ofpath[PATH_SIZE];
};

struct t_off{
    char lines[OFF_FILE_SIZE][OFF_LINE_SIZE];
    int lcount;
};

struct t_lua{
    char cname[100];
    char lines[OFF_FILE_SIZE][OFF_LINE_SIZE];
};

typedef struct t_arg ARG;
typedef struct t_off OFF;

void show_hlp();
void load_off(char *fpath, OFF *off, int *stat);
void save_lua(char *fpath, OFF *off, int *stat);
void copy_arg(char**argv, char *ptr);
void load_arg(int argc, char **argv, ARG *arg);
void vali_arg(ARG *arg, int *stat);

int main(int argc, char**argv)
{
    OFF off;
    ARG arg;
    int stat;

    printf(UNDERLINE);
    printf(TITLE);
    printf(UNDERLINE);

    load_arg(argc, argv, &arg);
    vali_arg(&arg, &stat);

    if (stat == ERROR)
    {
        show_hlp();
        return 0;
    }
    
    load_off(arg.ifpath, &off, &stat);
    
    if (stat == ERROR)
        return 0;

    save_lua(arg.ofpath, &off, &stat);

    return 0;
}

void show_hlp()
{
    printf("\nusage:\n");
    printf("\toff2lua <input file> <ouput file>\n\n");
}

void load_off(char *fpath, OFF *off, int *stat)
{
    FILE *file;
    char line[OFF_LINE_SIZE] = "\0";
    void *res = NULL;
    int lcount = 0;

    printf("Loading model from %s\n", fpath);

    file = fopen(fpath, "r");

    if (file == NULL)
    {
        printf("ERROR: Could not open file: %s\n", fpath);
        *stat = ERROR;
        return;
    }

    while(fgets(line, OFF_LINE_SIZE, file) != NULL)
    {
        //printf("%ld, %s\n", strlen(line), line);
        char *tmp = off->lines[lcount];
        strcpy(tmp, line);
        lcount++;
    }

    off->lcount = lcount;
    printf("lcount %d\n", off->lcount);

    fclose(file);
}

void save_lua(char *fpath, OFF *off, int *stat)
{
    FILE *file;
    int lcount = off->lcount;
    printf("Saving model to %s, %ld\n", fpath, strlen(fpath));

    file = fopen(fpath, "w");

    if (file == NULL)
    {
        *stat = ERROR;
        return;
    }

    printf("%d\n", off->lcount);
    
    for (int i = 0; i < lcount; i++)
    {
        fprintf(file, "%s", off->lines[i]);
        //printf("%s\n", &off->lines[i]);
    }

    fclose(file);
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