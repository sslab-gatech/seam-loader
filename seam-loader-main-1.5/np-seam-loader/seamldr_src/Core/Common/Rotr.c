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
 * Micrsoft compiler can replacement code sections with internal rotr so
 * we must provide a replacement.
 */
UINT32 _lrotr(UINT32 val, INT32 shift)
{
  UINT32 tmp = val;

  _asm {
    mov eax, tmp
    mov ecx, shift
    ror eax, cl
    mov tmp, eax
  }
  return tmp;
}

UINT32 _rotr(UINT32 val, INT32 shift)
{
  return _lrotr(val, shift);
}

__declspec(naked) void __cdecl _aullshr(void)
{
  __asm {
    cmp cl, 1Fh
    jbe L1
    mov eax, edx
    mov edx, 0
    sub ecx, 20h
    shr eax, cl
    jmp L2
L1:
    shrd eax, edx, cl
    shr edx, cl
L2:
    ret
  }
}
