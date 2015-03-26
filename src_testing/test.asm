                IF DEBUG EQ 1
;
; Testprozedur
; durch EinfÅuegen kann man prueÅfen, ob bestimmte Codestellen erreicht
; werden, und mit welchen Werten
;
testproc        PROC NEAR
                PUSH AX
                PUSH DX
                MOV AH,02h
                MOV DL, '<'
                INT 21h

                MOV AH,02h
                MOV DL, BL
                INT 21h

                MOV AH,02h
                MOV DL, CL
                ADD DL,30h
                INT 21h

                MOV AH,02h
                MOV DL, '>'
                INT 21h
                POP DX
                POP AX
                RET

testproc        ENDP
                ENDIF

