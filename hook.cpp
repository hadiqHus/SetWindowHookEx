#include <iostream>
#include <Windows.h>

int main() {
    MessageBoxA(NULL, "You will need process hacker", "Hint", MB_OK);
    MessageBoxA(NULL, "Open up Notepad.exe", "Hint", MB_OK);

    // Path of DLL
    const char* dllPath = "C:\\Users\\IEUser\\source\\repos\\dllhook\\x64\\Debug\\dllhook.dll";
    HMODULE library = LoadLibraryA(dllPath);
    if (!library) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load DLL. Error code: " << error << std::endl;
        MessageBoxA(NULL, "Failed to load DLL", "Error", MB_OK);
        return 1;
    }
    else {
        MessageBoxA(NULL, "DLL loaded successfully", "Info", MB_OK);
    }

    HOOKPROC hookProc = (HOOKPROC)GetProcAddress(library, "KeyboardProc");
    if (!hookProc) {
        DWORD error = GetLastError();
        std::cerr << "Failed to get hook procedure address. Error code: " << error << std::endl;
        MessageBoxA(NULL, "Failed to get hook procedure address", "Error", MB_OK);
        FreeLibrary(library);
        return 1;
    }
    else {
        MessageBoxA(NULL, "Hook procedure address obtained", "Info", MB_OK);
    }

    std::cout << "Memory location: " << hookProc << std::endl;

    // Set the hook
    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, hookProc, library, 0);
    if (!hook) {
        DWORD error = GetLastError();
        std::cerr << "Failed to set hook. Error code: " << error << std::endl;
        MessageBoxA(NULL, "Failed to set hook", "Error", MB_OK);
        FreeLibrary(library);
        return 1;
    }
    else {
        MessageBoxA(NULL, "Hook set successfully", "Info", MB_OK);
    }

    // Keep the hook active
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up
    UnhookWindowsHookEx(hook);
    FreeLibrary(library);

    return 0;
}
