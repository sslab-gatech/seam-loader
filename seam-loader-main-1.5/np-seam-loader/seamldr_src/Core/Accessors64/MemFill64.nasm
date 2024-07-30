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

;---------------------------------------------------------------------------

%include "AcmCom_NASM.inc"


segment .data  align=16

segment .text  align=16

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:	Movdir64B
; 
;  Input:	Source
;           Destination
; 
;  Output:	None
; 
;  Description:  Wrapper for a MOVDIR64B instruction
; 
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global Movdir64B
Movdir64B :
    push       rdi
    push       rsi
    
    mov        rdi, rcx
    mov        rsi, rdx
;/*movdir64b op*/
    DB 066h
    DB 0Fh
    DB 038h
    DB 0F8h
;/*ModRM = RDI->RSI*/
    DB 037h
    
    pop        rsi
    pop        rdi
    
    ret


        

 