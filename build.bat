powershell.exe ./clean.ps1
cl /c ./build/c/helloworld.c
link /DEBUG /PDB:./build/symbol/helloworld.pdb ./helloworld.obj /OUT:./build/bin/helloworld.exe
powershell.exe ./clean_obj.ps1