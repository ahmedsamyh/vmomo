@echo off
msbuild -p:configuration=%1 -warnAsMessage:LNK4217,LNK4286 -verbosity:m -m D:\programming\C++\vm\build\VM.sln
