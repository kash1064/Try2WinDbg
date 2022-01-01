powershell.exe ./clean.ps1
cl /c ./build/c/base64.c
link /DEBUG /PDB:./build/symbol/base64.pdb ./base64.obj /OUT:./build/bin/base64.exe

cl /c ./build/c/win_tcp_udp.c
link /DEBUG /PDB:./build/symbol/win_tcp_udp.pdb ./win_tcp_udp.obj /OUT:./build/bin/win_tcp_udp.exe

cl /c ./build/c/rc4_encrypt.c
link /DEBUG /PDB:./build/symbol/rc4_encrypt.pdb ./rc4_encrypt.obj /OUT:./build/bin/rc4_encrypt.exe

powershell.exe ./clean_obj.ps1