FROM mstorsjo/llvm-mingw

RUN mkdir -p /try2windbg
ENV HOME=/try2windbg
WORKDIR $HOME