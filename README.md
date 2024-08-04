# Keyboard Hooking and Shellcode Execution

## Description

This project demonstrates how to create a dynamic link library (DLL) that implements a keyboard hook to log keystrokes and execute shellcode. The code is intended for educational purposes, illustrating techniques used in both debugging and cybersecurity research.

## How It Works

1. **Keyboard Hook Setup:**
   - The DLL sets a global keyboard hook using the `SetWindowsHookEx` function.
   - It intercepts `WM_KEYDOWN` messages, which indicate key presses.

2. **Logging Keystrokes:**
   - Each intercepted key press is logged to a file located at `C:\Users\IEUser\Desktop\log.txt`.
   - The virtual key code is mapped to a character using `MapVirtualKeyA`.

3. **Shellcode Execution:**
   - Upon each key press, a block of shellcode is executed.
   - The shellcode is copied to an executable memory region using `VirtualAlloc`, and then executed by casting the memory location to a function pointer.

4. **DLL Lifecycle Management:**
   - The `DllMain` function handles actions on `DLL_PROCESS_ATTACH` and `DLL_PROCESS_DETACH`.
   - On attachment, it initializes the log file, and on detachment, it ensures the keyboard hook is removed.

5. **Error Handling:**
   - The code uses message boxes to display the status of operations, such as successful DLL loading, hook setting, and errors.

## Key Functions

- `KeyboardProc`: Callback function that processes keyboard events, logs keys, and executes shellcode.
- `CreateLogFile`: Initializes the log file to store keystroke data.
- `DllMain`: Manages the DLL's initialization and cleanup tasks.

## Usage

- Compile the code into a DLL using a C++ compiler.
- Inject the compiled DLL into a target process using a tool like Process Explorer.
- Monitor the log file and observe message boxes for feedback on key logging and shellcode execution.

## Disclaimer

This code is for educational purposes only. Unauthorized use of keyboard hooking and shellcode execution techniques can violate privacy and security policies. Always ensure compliance with legal and ethical standards when using this code.

