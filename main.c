#include <stdio.h>
#include <string.h>

#define TITLE       "\toff2lua v1.0.0\n"
#define UNDERLINE    "===============================\n"

#define ERROR       -999

#define PATH_SIZE   500
#define OFF_LIMIT   1000
#define OFF_LINE_SIZE 100

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
void load_off(char *fpath, OFF *off, int *stat);
void save_lua(char *fpath, OFF *off, int *stat);
void copy_arg(char**argv, char *ptr);
void load_arg(int argc, char **argv, ARG *arg);
void vali_arg(ARG *arg, int *stat);

int main(int argc, char**argv)
{
    ARG arg;
    OFF off;
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
    char line[OFF_LINE_SIZE];
    void *res = NULL;

    printf("Loading model from %s\n", fpath);

    file = fopen(fpath, "r");

    if (file == NULL)
    {
        printf("ERROR: Could not open file: %s\n", fpath);
        *stat = ERROR;
        return;
    }

    do
    {
        res = fgets(line, OFF_LINE_SIZE, file);
        printf("%s\n", line);
    } while(res != NULL);

    fclose(file);
}

void save_lua(char *fpath, OFF *off, int *stat)
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