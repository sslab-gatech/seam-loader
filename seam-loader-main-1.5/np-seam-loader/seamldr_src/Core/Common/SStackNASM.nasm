;**********************************************************************;
;*                                                                    *;
;* Intel Proprietary                                                  *;
;*                                                                    *;
;* Copyright 2021 Intel Corporation All Rights Reserved.              *;
;*                                                                    *;
;* Your use of this software is governed by the TDX Source Code       *;
;* LIMITED USE LICENSE.                                               *;
;*                                                                    *;
;* The Materials are provided "as is," without any express or         *;
;* implied warranty of any kind including warranties of               *;
;* merchantability, non-infringement, title, or fitness for a         *;
;* particular purpose.                                                *;
;*                                                                    *;
;**********************************************************************;

%include "AcmCom_NASM.inc"

section EDATA32 data write PUBLIC USE32 align=16
shadow_stack_vesp: dq 0

section .text code USE32 align=1

global  _penter
_penter:
        push eax ; save tmp
        push ebx

        ; push RA to shadow stack
        mov eax, [esp+12]   ; get RA
        mov ebx, DWORD [shadow_stack_vesp]

        mov [ebx], eax      ; "push" RA
        add DWORD [shadow_stack_vesp], 4

        pop ebx
        pop eax
        ret

global  _pexit
_pexit:
        push eax ; make tmp
        push ebx

        ; pop from shadow stack
        mov ebx, DWORD [shadow_stack_vesp]
        sub ebx, 4
        mov eax, [ebx]
        mov DWORD [shadow_stack_vesp], ebx

        ; compare shadow RA to callee RA
        cmp eax, DWORD [esp + 12]
        jnz error

    skip_check:
        pop ebx ; restore tmp
        pop eax
        ret

    error:

        %ifidni ACM_TYPE,AC_BIOSAC
            %assign SHADOW_STACK_ERROR  ( CRASH_CODE_VALID + CRASH_CODE_SW_GENERATED + AC_BIOSAC + (ERR_SHADOW_STACK << CR_Major_cr_position) + (CLASS_INTERNAL_ERRORS << CR_Class_cr_position) )
        %endif
        %ifidni ACM_TYPE,AC_SINIT
            %assign SHADOW_STACK_ERROR  ( CRASH_CODE_VALID + CRASH_CODE_SW_GENERATED + AC_SINIT + (ERR_SHADOW_STACK << CR_Major_cr_position) + (CLASS_INTERNAL_ERRORS << CR_Class_cr_position) )
        %endif

        update_crash_register:
            mov     esi, LT_PRV_BASE+TXT.LT_CRASH
            mov     [esi], DWORD SHADOW_STACK_ERROR

        ltReset:
            mov   ecx, 1000
            mov   esi, LT_PRV_BASE+TXT.LT_CMD_SYS_RESET

            REPEAT
                    mov   DWORD [esi], 0
                    mov   eax, [esi]              ; Read it back
                    pause
            UNTILCXZ

        deadLoop:
            hlt
            jmp   deadLoop
