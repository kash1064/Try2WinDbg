EXE := hlt.exe switch_task.exe ttd_tutorial.exe
CPP_SOURCE_DIR := cpp
MINGW_GPP := x86_64-w64-mingw32-g++
MINGW_OPT := 

%.exe: ${CPP_SOURCE_DIR}/%.cpp
	${MINGW_GPP} ${MINGW_OPT} $< -o $@

all: ${EXE}