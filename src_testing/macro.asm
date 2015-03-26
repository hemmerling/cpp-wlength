DEBUG           EQU     0     ; 1 = Debug-Ausgaben

                IF DEBUG EQ 1
; Macro zum Debuggen
TEST1_MACRO       MACRO Zeichen
                PUSH BX
                MOV BL, Zeichen
                CALL testproc
                POP BX
                ENDM
                ENDIF

TEST2_MACRO     MACRO
                PUSH AX
                PUSH DX
                MOV AH,02h
                MOV DL, '#'
                INT 21h

                MOV AH,02h
                MOV DL, BL
                ADD DL, 30h
                INT 21h

                MOV AH,02h
                MOV DL, '#'
                INT 21h
                POP DX
                POP AX
                ENDM
