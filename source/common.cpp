#include "../header/common.h"


bool s_flag_debug_print = true;
bool s_flag_warn_print = true;

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
    printf("[DEBUG]%s", buffer);
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
    printf("[WARN]%s", buffer);
    va_end(ap);
    return COMPLETE;
}

void ErrorPrintf(const char* fmt, ...) {
    char buffer[BUFSIZE];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    printf("[ERROR]%s", buffer);
    va_end(ap);

    exit(0);
}