# VMOMO - Momoyon's Virtual Machine


My Custom Virtual Machine with my own Assembly.

*Only Works on Windows!!!*

## OpCodes
- NOP				: Doesn't do anything.
- MOV src dst		: Moves value of src{Immediate} to dst{Registers}.
- MOVR src dst		: Moves values src{Register} to dst{Register}.
- PRINT reg			: prints the value of reg to stdout.
- ADD reg1 reg2		: Add reg1 and reg2 and stores the sum in rax.
- SUB				: Same as ADD but subtracts.
- MULT				: Same as ADD but multiplies.
- DIV				: Same as ADD but divides.
- JMP addr			: Jumps to addr
- XCHG reg1 reg2	: Exchanges the value of reg1 and reg2
- PEND				: stops the execution of the program.


## Quick Start
```console
$ premake5 vs2022
$ msbuild -p:configuration<Debug|Release> build\vsmomo.sln
$ bin\<config>\vsmomo.exe
```
You can also open the VS solution file (.sln) directly and build with Visual Studio<s>(If you want to wait for eternally )</s> and build it (is doing the same thing).

## Dependencies
- [premake5 (version 5.0.0-beta2 and up)](https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip)
- [Visual Studio 17.4.4 (2022)](https://visualstudio.microsoft.com/vs/community/) with (Desktop development with C++ Workload Installed)
