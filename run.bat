@echo off
echo Starting server...
start "" "out/build/x64-debug/server_test.exe"
echo Server started.
ping -n 5 127.0.0.1 > nul

echo Starting clients...
start "" "out/build/x64-debug/client1.exe"
start "" "out/build/x64-debug/client2.exe"
start "" "out/build/x64-debug/client3.exe"
start "" "out/build/x64-debug/client4.exe"
start "" "out/build/x64-debug/client5.exe"

echo All clients started.
pause