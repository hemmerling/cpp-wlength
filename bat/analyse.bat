@echo off
rem * 
rem * @package   wlength
rem * @file      analyse.bat
rem * @brief     Auswertung der in einem Text 
rem *            auftretenden Wortlängen und ihrer Häufigkeit 
rem * @author    Rolf Hemmerling <hemmerling@gmx.net>
rem * @version   1.00, 
rem *            Programmiersprache "COMMAND.COM Batch-Datei",
rem *            Zielplattform: IBM-PC mit MS-DOS Betriebssystem
rem * @date      2015-01-01
rem * @copyright Apache License, Version 2.0
rem * 
rem * analyse.bat - Auswertung der in einem Text 
rem *               auftretenden Wortlängen und ihrer Häufigkeit 
rem * 
rem * Copyright 1988-2015 Rolf Hemmerling
rem * 
rem * Licensed under the Apache License, Version 2.0 (the "License");
rem * you may not use this file except in compliance with the License.
rem * You may obtain a copy of the License at
rem * 
rem * http://www.apache.org/licenses/LICENSE-2.0
rem * 
rem * Unless required by applicable law or agreed to in writing,
rem * software distributed under the License is distributed on an
rem * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
rem * either express or implied.
rem * See the License for the specific language governing permissions
rem * and limitations under the License.
rem * 
rem *  Haupt-Entwicklungszeiten
rem *    1998-09 - 1998-12-14
rem *    2001-01-24, 2004-07-20 ( Umstellung auf C++ )
rem * 
rem *  Zu dem Projekt gehoeren die Dateien
rem *   - WLENGTH.C
rem *   - WLENASM.ASM
rem *   - WLENASM.EXE
rem *   - ANALYSE.BAT
rem *
if "%1"=="" goto XX02
del ausgabe.txt >nul
del kontrol.txt >nul
rem *  Benutzung einer C-Routine zur Kontrolle
wlength -k <%1 >kontrol.txt
if errorlevel 2 goto XX12
if errorlevel 1 goto XX11
goto XX01
:XX12
echo Fehler 2
goto XX01
:XX11
echo Fehler 1
goto XX01

:XX01
rem *  Benutzung der ASM-Routine
wlength <%1 >ausgabe.txt
if errorlevel 2 goto XX22
if errorlevel 1 goto XX21
goto XX03
:XX22
echo Fehler 2
goto XX03
:XX21
echo Fehler 1
goto XX03

:XX02
echo ANALYSE.BAT
echo Auswertung der in einem Text auftretende
echo Wortlaengen und ihre Haeufigkeit
echo Copyright 1998-2015 Rolf Hemmerling
echo Licensed under the Apache License, Version 2.0
echo Verwendet: WLENGTH.EXE, SORT.EXE, COMP.EXE, TYPE
echo Format:    ANALYSE datei.txt
echo Beispiel:  "ANALYSE datei.txt | MORE"
goto XX00

:XX03
echo Wortlaenge (ansteigend) - ihre Haeufigkeit
type ausgabe.txt
goto XX04
pause
echo Wortlaenge (abfallend) - ihre Haeufigkeit
type ausgabe.txt | sort /R
pause
echo Haeufigkeit (ansteigend) - dazugehoerige Wortlaenge
type ausgabe.txt | sort /+6
pause
echo Haeufigkeit (abfallend) - dazugehoerige Wortlaenge
type ausgabe.txt | sort /+6 /R
:XX04
comp ausgabe.txt kontrol.txt
:XX00
rem *  ENDE

