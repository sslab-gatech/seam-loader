//**********************************************************************;
//*                                                                    *;
//* Intel Proprietary                                                  *;
//*                                                                    *;
//* Copyright 2021 Intel Corporation All Rights Reserved.              *;
//*                                                                    *;
//* Your use of this software is governed by the TDX Source Code       *;
//* LIMITED USE LICENSE.                                               *;
//*                                                                    *;
//* The Materials are provided "as is," without any express or         *;
//* implied warranty of any kind including warranties of               *;
//* merchantability, non-infringement, title, or fitness for a         *;
//* particular purpose.                                                *;
//*                                                                    *;
//**********************************************************************;
#include <common.h>

/*
 * Micrsoft compiler can replacement code sections with internal allmul so
 * we must provide a replacement.
 * per api
 * Purpose:
 *        Does a unsigned long divide of the arguments.  Arguments are
 *        not changed.
 *
 * Entry:
 *        Arguments are passed on the stack:
 *                1st pushed: X (QWORD)
 *                2nd pushed: Y (QWORD)
 *
 * Exit:
 *        EDX:EAX contains the product of X * Y
 *        NOTE: this routine removes the parameters from the stack.
 *
 * Uses:
 *        ECX
 *
 * Exceptions:
 *
 *  NOTE, this must follow same usage as microsoft runtime. This routine removes arguments from stack
 *
 *
 *    XL = X[31.0] XH = X[63.32] YL = Y[31.0] YH = Y[63.0]
 *
 *    XL_YH = XL * YH
 *    XH_YL = XH * YL
 *    EAX = XL * YL
 *    EDX = ((XL * YL) >> 32) + XL_YH + XH_YL
 */

__declspec(naked) void __cdecl _allmul(void)
{
  _asm {
    push ebx
    mov ebx, [esp + 08h]; X_L
    mov eax, [esp + 10h]; Y_L
    mov edx, [esp + 0Ch]; X_H
    mov ecx, [esp + 14h]; Y_H
    imul ecx, ebx; Y_H *X_L
    imul edx, eax; X_H *Y_L
    add ecx, edx; XL_YH + XH_YL
    mul ebx; XL *YL
    add edx, ecx; ((XL * YL) >> 32) + XL_YH + XH_YL
    pop ebx
    ret     16; we have to pop arguments off stack
  }
}
