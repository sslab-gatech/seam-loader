; Copyright (C) 2023 Intel Corporation                                          
;                                                                               
; Permission is hereby granted, free of charge, to any person obtaining a copy  
; of this software and associated documentation files (the "Software"),         
; to deal in the Software without restriction, including without limitation     
; the rights to use, copy, modify, merge, publish, distribute, sublicense,      
; and/or sell copies of the Software, and to permit persons to whom             
; the Software is furnished to do so, subject to the following conditions:      
;                                                                               
; The above copyright notice and this permission notice shall be included       
; in all copies or substantial portions of the Software.                        
;                                                                               
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS       
; OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL      
; THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES             
; OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,      
; ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE            
; OR OTHER DEALINGS IN THE SOFTWARE.                                            
;                                                                               
; SPDX-License-Identifier: MIT

;---------------------------------------------------------------------------

%include "AcmCom_NASM.inc"


segment .data  align=16
    movdir64b_supported    db 0xff    ; 0xff = uninitialized, 0 = not supported, 1 = supported

segment .text  align=16

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:	check_movdir64b_support
; 
;  Input:	None
; 
;  Output:	AL = 1 if MOVDIR64B is supported, 0 if not
; 
;  Description:  Check if MOVDIR64B instruction is supported using CPUID
;                MOVDIR64B is indicated by bit 28 in ECX when CPUID(EAX=7, ECX=0)
; 
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
check_movdir64b_support:
    push       rbx
    push       rcx
    push       rdx
    
    ; Check if we already determined support
    mov        al, [movdir64b_supported]
    cmp        al, 0xff
    jne        .done
    
    ; First check if CPUID supports leaf 7
    mov        eax, 0
    cpuid
    cmp        eax, 7
    jl         .not_supported
    
    ; Check MOVDIR64B support (bit 28 in ECX from CPUID leaf 7, subleaf 0)
    mov        eax, 7
    mov        ecx, 0
    cpuid
    
    ; Test bit 28 in ECX
    test       ecx, (1 << 28)
    jz         .not_supported
    
    ; MOVDIR64B is supported
    mov        byte [movdir64b_supported], 1
    mov        al, 1
    jmp        .done
    
.not_supported:
    mov        byte [movdir64b_supported], 0
    mov        al, 0
    
.done:
    pop        rdx
    pop        rcx
    pop        rbx
    ret

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:	movdir64b_native
; 
;  Input:	Source (RSI)
;           Destination (RDI)
; 
;  Output:	None
; 
;  Description:  Native MOVDIR64B implementation
; 
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
movdir64b_native:
    ; MOVDIR64B instruction using direct encoding
    DB 066h
    DB 0Fh
    DB 038h
    DB 0F8h
    DB 037h    ; ModRM = RDI->RSI
    ret

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:	movdir64b_fallback
; 
;  Input:	Source (RSI)
;           Destination (RDI)
; 
;  Output:	None
; 
;  Description:  Fallback implementation using regular moves
; 
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
movdir64b_fallback:
    push       rax
    
    ; Move 64 bytes using 8 x 8-byte moves
    mov        rax, [rsi]
    mov        [rdi], rax
    
    mov        rax, [rsi + 8]
    mov        [rdi + 8], rax
    
    mov        rax, [rsi + 16]
    mov        [rdi + 16], rax
    
    mov        rax, [rsi + 24]
    mov        [rdi + 24], rax
    
    mov        rax, [rsi + 32]
    mov        [rdi + 32], rax
    
    mov        rax, [rsi + 40]
    mov        [rdi + 40], rax
    
    mov        rax, [rsi + 48]
    mov        [rdi + 48], rax
    
    mov        rax, [rsi + 56]
    mov        [rdi + 56], rax
    
    pop        rax
    ret

;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
;  Procedure:	Movdir64B
; 
;  Input:	Source (RCX)
;           Destination (RDX)
; 
;  Output:	None
; 
;  Description:  Wrapper that automatically chooses between native MOVDIR64B
;                and fallback implementation based on CPU support
; 
;-----------------------------------------------------------------------------
;-----------------------------------------------------------------------------
global Movdir64B
Movdir64B :
    push       rdi
    push       rsi
    
    mov        rsi, rcx    ; Source address
    mov        rdi, rdx    ; Destination address
    
    ; Check if MOVDIR64B is supported
    call       check_movdir64b_support
    test       al, al
    jz         .use_fallback
    
    ; Use native MOVDIR64B
    call       movdir64b_native
    jmp        .done
    
.use_fallback:
    ; Use fallback implementation
    call       movdir64b_fallback
    
.done:
    pop        rsi
    pop        rdi
    ret
