FROM gcc:10

WORKDIR /app/

COPY ./* ./

RUN gcc compiler.c -o compiler

RUN chmod +x compiler
