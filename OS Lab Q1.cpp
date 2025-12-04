#include <stdio.h>
#include <windows.h>

int main(int argc, char *argv[]) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    if (argc == 2 && strcmp(argv[1], "child") == 0) {
        printf("Child Process Running\n");
        printf("Child PID: %lu\n", GetCurrentProcessId());
        system("pause");
        return 0;
    }

    printf("Parent Process Running\n");
    printf("Parent PID: %lu\n", GetCurrentProcessId());

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char cmd[200];
    GetModuleFileName(NULL, cmd, 200);
    strcat(cmd, " child");

    if (CreateProcessA(
            NULL,
            cmd,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        printf("Child Process Created Successfully\n");
        printf("Child PID: %lu\n", pi.dwProcessId);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } 
    else {
        printf("Process Creation Failed\n");
    }

    system("pause");
    return 0;
}

