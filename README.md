# VMOMO - Momoyon's Virtual Machine


My Custom Virtual Machine with my own Assembly.

*Only Works on Windows!!!*

## OpCodes
- NOP
- MOV src dst : Moves value of src to dst{Registers only}.
- ADD         : Add rax and rbx and stores the sum in rax.
- PRINT reg   : prints the value of reg to stdout.
- PEND        : stops the execution of the program.

## Dependencies
- [premake5 (version 5.0.0-beta2 and up)](https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip)
- [Visual Studio 17.4.4 (2022)](https://visualstudio.microsoft.com/vs/community/) with (Desktop development with C++ Workload Installed)
