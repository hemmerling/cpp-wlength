;
; @package   wlength
; @file      wlenasm.asm
; @brief     WLength - Auswertung der in einem Text 
;            auftretenden Wortlängen und ihrer Häufigkeit 
; @author    Rolf Hemmerling <hemmerling@gmx.net>
; @version   1.00, 
;            Programmiersprache "C++",
;            Entwicklungswerkzeug "Microsoft Visual C++ 1.52" / VC++ 8.00c
;            ( Large Model ) und "Microsoft 8086 Assembler",
;            Zielplattform: IBM-PC mit MS-DOS Betriebssystem
; @date      2015-01-01
; @copyright Apache License, Version 2.0
;
; wlenasm.asm - Assembler-Unterprogramm in 16-bit 8086 Assembler
;               fuer WLength - Auswertung der in einem Text
;               auftretenden Wortlängen und ihrer Häufigkeit 
;
; Copyright 1998-2015 Rolf Hemmerling
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
; http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing,
; software distributed under the License is distributed on an
; "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
; either express or implied.
; See the License for the specific language governing permissions
; and limitations under the License.
;
; Haupt-Entwicklungszeiten
;   1998-09 - 1998-12-14
;   2001-01-24, 2004-07-20 ( Umstellung auf C++ )   
;
; MASM 5.x:
;   masm /Mx %1
; MASM 6.x, 7.x,
;   keine "_" vor den Globals:
;     ml /omf /c /Cx /Gd /Fl%1.lst %1.asm %2
;   mit "_" vor den Globals:
;     ml /omf /c /Cx /Fl%1.lst %1.asm %2
;

         ;INCLUDE MACRO.ASM

;
; extern int GP_wlength1(
;  unsigned int *IV_anzeige,   <-- PARM1
;  char *IV_puffer,            <-- PARM2
;  unsigned int VV_laenge);    <-- PARM3
;
PARM1    EQU    6
PARM1O   EQU    6  ; Offset
PARM1S   EQU    8  ; Segment
PARM2    EQU    10
PARM2O   EQU    10 ; Offset
PARM2S   EQU    12 ; Segment
PARM3    EQU    14

; Leerzeichen
SPACE    EQU    20h

                .8086
                .MODEL LARGE
                .DATA
                .CODE
                PUBLIC _GP_wlength1

_GP_wlength1    PROC FAR
; Stack des Aufrufers retten, neuen Stack-Frame aufbauen
                PUSH BP
                MOV  BP,SP
; hier eventuell Platz fuer lokalen Variable alloziieren
                PUSH DS
                PUSH ES
                PUSH DI
                PUSH SI
                PUSH DX
                PUSH CX
                PUSH BX
                PUSH AX
                PUSHF
; DS:SI = Tabelle
                LDS  SI, DWORD PTR [BP + PARM1O]
; ES:DI = Dateizeilenpuffer
                LES  DI, DWORD PTR [BP + PARM2O]
; CX = Laufvariable
                MOV  CX, WORD PTR [BP + PARM3]
; String-Befehl Richtung "aufwaerts" einstellen
                CLD
; Initalisierung der Suchmaske
                MOV  AL, SPACE
;
; Schleife, bis Dateizeilenende erreicht ist
;
schleife:
; Dateizeilenende erreicht ?
                CMP  CX,0
                JZ   ende1

; Suche Muster, das sich von SPACE unterscheidet

                REPZ SCASB

                JZ nokorr1
; Korrektur notwendig, CX und ES:DI ein Zeichen zurueck gehen lassen
; Also Restzeichenzahl = CX erhoehen, Zeiger verringern
                INC CX
                DEC DI
nokorr1:
; BX = Anfang
                MOV BX, CX
; Test ob Ende der Zeichenkette erreicht
                CMP CX, 0h
                JZ ende1
; Suche Muster SPACE
                REPNZ SCASB
                JNZ nokorr2
; Korrektur notwendig, CX und ES:DI ein Zeichen zurueck gehen lassen
; Also Restzeichenzahl = CX erhoehen, Zeiger verringern
                INC CX
                DEC DI
nokorr2:
; CX = Ende
; Wortlaenge = Anfang-Ende
; Tabellenindex = Anfang-Ende-1
; BX = BX - CX - 1
                SUB BX, CX
                DEC BX

; Tabellenindex zu gross ? Wenn ja, Erhoehung
; der Haeufigkeit von "aller Wortlaengen >255"
                CMP BX, 255
                JLE index_ok
                MOV BX, 255
index_ok:
; Tabelle besteht aus Worten -> Offset = 2 * Index
                SHL BX,1
; Haeufigkeit zu gross ? Kein weiteres Inkrement, sondern
; Zaehler bleibt auf Maximalstand
                MOV DX, WORD PTR DS:[SI+BX]
                CMP DX, 0FFFFh
                JLE haeufigkeit_max
                INC DX
haeufigkeit_max:MOV  WORD PTR DS:[SI+BX], DX
                JMP schleife
;
; Schleifenende
;
ende1:
;
; Rueckgabewert (int) in AX Register
; Zur Zeit immer "0"
                MOV AX, 0
; Register zurueckladen
                POPF
; "POP BX" statt "POP AX"
; AX wird ja zur Funktionswert-Rueckgabe genutzt
                POP BX  
                POP BX
                POP CX
                POP DX
                POP SI
                POP DI
                POP ES
                POP DS
; Stack wiederherstellen
                MOV SP, BP
                POP BP
                RET
_GP_wlength1    ENDP

                ;INCLUDE TEST.ASM
; Ende
                END
