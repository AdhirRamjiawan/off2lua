#include <stdio.h>
#include <string.h>

#define TITLE       "\toff2lua v1.0.0\n"
#define UNDERLINE    "===============================\n"

#define ERROR       -999

#define CLASS_NAME 100
#define PATH_SIZE   500
#define OFF_LINE_SIZE 50
#define OFF_FILE_SIZE 5000

struct t_arg{
    char ifpath[PATH_SIZE];
    char ofpath[PATH_SIZE];
    char class[CLASS_NAME];
};

struct t_off{
    char lines[OFF_FILE_SIZE][OFF_LINE_SIZE];
    int lcount;
};

struct t_lua{
    char class[CLASS_NAME];
    char lines[OFF_FILE_SIZE][OFF_LINE_SIZE];
    int lcount;
};

typedef struct t_arg ARG;
typedef struct t_off OFF;
typedef struct t_lua LUA;

void show_hlp();
void load_off(char *fpath, OFF *off, int *stat);
void save_lua(char *fpath, LUA *lua, int *stat);
void off2_lua(OFF *off, LUA *lua, ARG *arg);
void copy_arg(char**argv, char *ptr);
void load_arg(int argc, char **argv, ARG *arg);
void vali_arg(ARG *arg, int *stat);

int main(int argc, char**argv)
{
    LUA lua;
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

    off2_lua(&off, &lua, &arg);
    save_lua(arg.ofpath, &lua, &stat);

    return 0;
}

void show_hlp()
{
    printf("\nusage:\n");
    printf("\toff2lua <input file> <ouput file> <class name>\n\n");
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

void off2_lua(OFF *off, LUA *lua, ARG *arg)
{
    int lcount = off->lcount;
    char *tok;

    for (int l = 0; l < lcount; l++)
    {
        tok = strtok(off->lines[l], " ");

        while (tok != NULL)    
        {
            sprintf(lua->lines[l], ",%s", tok);
            tok = strtok(NULL, " ");
        }
        sprintf(lua->lines[l], "\n");
    }

    lua->lcount = lcount;
    strcpy(lua->class, arg->class);
}

void save_lua(char *fpath, LUA *lua, int *stat)
{
    FILE *file;
    int lcount = lua->lcount;
    printf("Saving model to %s, %ld\n", fpath, strlen(fpath));

    file = fopen(fpath, "w");

    if (file == NULL)
    {
        *stat = ERROR;
        return;
    }

    // printf("%d\n", off->lcount);

    fprintf(file, "%s = {}\n", lua->class);
    fprintf(file, "function %s:new(o)\n", lua->class);
    fprintf(file, "\to = o or {}\n");
    fprintf(file, "\tsetmetatable(0, self)\n");
    fprintf(file, "\tself.__index = self\n");
    fprintf(file, "\tself.data1 = {\n");

    for (int i = 0; i < lcount; i++)
    {
        fprintf(file, ",%s", lua->lines[i]);
        //printf("%s\n", &off->lines[i]);
    }

    fprintf(file, "\t}\n");
    fprintf(file, "\treturn 0\n");
    fprintf(file, "end\n");

    fclose(file);
}

void vali_arg(ARG *arg, int *stat)
{
    if (strlen(arg->ifpath) == 0)
        *stat = ERROR;

    if (strlen(arg->ofpath) == 0)
        *stat = ERROR;

    if (strlen(arg->class) == 0)
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
    argv++;
    copy_arg(argv, arg->class);
}