#include <myterm.h>

#define DEF_EXE_ID(name) CONCAT(exe_id_, name), 
enum{ MAP(EXE_LIST, DEF_EXE_ID) nr_exe};

#define DEF_EXE_ARR(name) \
        [CONCAT(exe_id_, name)] = { \
            .exe_name = #name, \
            .exe_func = CONCAT(exe_, name) \
        },

EXE exe_arr[nr_exe] = { MAP(EXE_LIST, DEF_EXE_ARR) };

char *argv[NR_TOKEN];
inline int tokenlize(char *line);

int main(){
    ioe_init();
    welcome();
    while(1){
        printf(ASNI_FMT("[byy&krr@fpga]$ ", ASNI_FG_GREEN));
        char *line = readline();
        int argc = tokenlize(line);
        if(argc == 0) continue;
        exe_func_type exe_func = unknown_cmd;
        for(int i = 0; i < nr_exe; i++){
            if(strcmp(argv[0], exe_arr[i].exe_name) == 0){
                exe_func = exe_arr[i].exe_func;
            }
        }
        exe_func(argc, argv);
    }
    return 0;
}


int exe_help(int argc, char *argv[]) {
    for(int i = 0; i < nr_exe; i++){
        printf(ASNI_FMT("%-16s", ASNI_FG_CYAN), exe_arr[i].exe_name);
        if(i % 4 == 3)putch('\n');
    }
    if(nr_exe % 4 != 0) putch('\n');
    return 0;
}

int exe_ls(int argc, char *argv[]) {
    return exe_help(argc, argv);
}

int unknown_cmd(int argc, char *argv[]) {
    printf(
            ASNI_FG_YELLOW
            "Command \""
            ASNI_FG_RED "%s"
            ASNI_FG_YELLOW
            "\" is unknown.\nType \"help\" to list all the commands.\n"
            ASNI_NONE
        ,
        argv[0]
    );
    return 255;
}

int tokenlize(char *line){
    size_t pos = 0;
    int argc = 0;
    while(line[pos] != '\0') {
        if(line[pos] != ' ') {
            argv[argc] = line + pos;
            argc++;
            while(line[pos] != ' ' && line[pos] != '\0'){
                pos++;
            }
            if(line[pos] == ' ') line[pos] = '\0', pos++;
        } else {
            pos++;
        }
    }
    return argc;
}

