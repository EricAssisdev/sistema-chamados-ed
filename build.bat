@echo off
gcc -Wall -Wextra -std=c99 src\fila_fifo.c src\lista_ord.c src\heap_max.c src\main.c -o sistema_chamados.exe
if %ERRORLEVEL% EQU 0 (
    echo Compilado com sucesso: sistema_chamados.exe
) else (
    echo Erro na compilacao.
)
