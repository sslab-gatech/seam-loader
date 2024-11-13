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
 * Micrsoft compiler can replacement code sections with internal rotl so
 * we must provide a replacement.
 */
UINT32 _lrotl(UINT32 val, INT32 shift)
{
  UINT32 tmp = val;

  _asm {
    mov eax, tmp
    mov ecx, shift
    rol eax, cl
    mov tmp, eax
  }
  return tmp;
}

UINT32 _rotl(UINT32 val, INT32 shift)
{
  return _lrotl(val, shift);
}

__declspec(naked) void __cdecl _allshl(void)
{
  __asm {
    cmp cl, 1Fh
    jbe L1
    mov edx, eax
    mov eax, 0
    sub ecx, 20h
    shl edx, cl
    jmp L2
L1:
    shld edx, eax, cl
    shl eax, cl
L2:
    ret
  }
}
