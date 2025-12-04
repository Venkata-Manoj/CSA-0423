#include <stdio.h>
#include <string.h>
#include <windows.h>

int main() {
    HANDLE hSlot, hFile;
    char msg[256], buffer[256];
    DWORD bytesRead, bytesWritten;

    hSlot = CreateMailslot(
        "\\\\.\\mailslot\\MyQueue",
        0,
        MAILSLOT_WAIT_FOREVER,
        NULL
    );

    if (hSlot == INVALID_HANDLE_VALUE) {
        printf("Message Queue Creation Failed\n");
        return 1;
    }

    printf("Enter message to send: ");
    gets(msg);

    hFile = CreateFile(
        "\\\\.\\mailslot\\MyQueue",
        GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hFile == INVALID_HANDLE_VALUE) {
        printf("Message Queue Open Failed\n");
        CloseHandle(hSlot);
        return 1;
    }

    WriteFile(hFile, msg, strlen(msg), &bytesWritten, NULL);
    printf("Message Sent\n");

    printf("\nWaiting to receive message...\n");

    if (ReadFile(hSlot, buffer, sizeof(buffer), &bytesRead, NULL)) {
        buffer[bytesRead] = '\0';
        printf("Received Message: %s\n", buffer);
    }

    CloseHandle(hFile);
    CloseHandle(hSlot);

    return 0;
}

