#include "../header/printer.h"


bool s_flag_debug_print = true;
bool s_flag_warn_print = true;

int SetPrinter(int num_args, ...) {
    va_list ap;
    va_start(ap, num_args);
    for (int i = 0; i < num_args; i++) {
        printf("%s", va_arg(ap, char*));
    }
    va_end(ap);
    return COMPLETE;
}

int ResetPrinter() {
    printf("%s", RESET);
    return COMPLETE;
}

int DebugDisable() {
    s_flag_debug_print = false;
    return COMPLETE;
}
int DebugEnable() {
    s_flag_debug_print = true;
    return COMPLETE;
}
int DebugPrintf(const char* fmt, ...) {
    if (!s_flag_debug_print) {
        return IMCOMPLETE;
    }
    char buffer[BUFSIZE];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    SetPrinter(2, UNDERLINE, GREEN_F);
    printf("[DEBUG] %s", buffer);
    ResetPrinter();
    va_end(ap);
    return COMPLETE;
}


int WarnDisable() {
    s_flag_warn_print = false;
    return COMPLETE;
}
int WarnEnable() {
    s_flag_warn_print = true;
    return COMPLETE;
}
int WarnPrintf(const char* fmt, ...) {
    if (!s_flag_warn_print) {
        return IMCOMPLETE;
    }
    char buffer[BUFSIZE];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    SetPrinter(2, HIGHLIGHT, RED_F);
    printf("[WARN] %s", buffer);
    ResetPrinter();
    va_end(ap);
    return COMPLETE;
}

void ErrorPrintf(const char* fmt, ...) {
    char buffer[BUFSIZE];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    SetPrinter(3, HIGHLIGHT, RED_F, UNDERLINE);
    printf("[ERROR] %s", buffer);
    ResetPrinter();
    va_end(ap);

    exit(ABNORMAL);
}
