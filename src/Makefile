EXE := hlt.exe switch_task.exe
SOURCE_DIR := c
MINGW_GCC := x86_64-w64-mingw32-g++

%.exe: ${SOURCE_DIR}/%.c
	${MINGW_GCC} $< -o $@

all: ${EXE}