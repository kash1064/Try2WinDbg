powershell.exe ./clean.ps1
cl /c ./build/c/base64.c
link /DEBUG /PDB:./build/symbol/base64.pdb ./base64.obj /OUT:./build/bin/base64.exe
powershell.exe ./clean_obj.ps1