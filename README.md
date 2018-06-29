# ATTiny13-emulator
Project for JIMP2 course - attiny13 emulator

Ważne pliki:

plik               | opis:
:------------------|:------------------
Documentation.md   |zawiera ustalenia odnośnie projektu
src/instruction    |zawiera zaimplementowane instrukcje
src/hexfile        |ładowanieplików Intel hex
src/ATTinyMemory   |model pamięci attiny13
src/emulationEnv   |środowisko uruchomieniowe emulatora
Utils.h            |zbór funkcji pomocniczych
main.cpp           |zawiera funkcję main()




opcje programu:
==========================================
opcja| opis:
:---|:------------------
'-h' | wyświetlenie informacji pomocniczych
'-l' | wyśwetlenie listy instrukcji
'-v' | wyświetlenie wercji programu 

opcje emulatora
============================================================
opcja| opis:
:-----------|:------------------
'-i'        |wyświetlenie wczytanego stanu procesora
'-m'        |wyciśzenie wyświetlania wykonywanych instrukcji
'-t N'      |wykonanie N kroków programu
'-c N'      |ustawienie PC na N
'-o <path-prefix>'| ustawienie prefixu dla plików wyjściowych
'-p <path>' | ścieżka do pliku programu *wymagane*
'-s <path>' | ścieżka do pliku SRAM


