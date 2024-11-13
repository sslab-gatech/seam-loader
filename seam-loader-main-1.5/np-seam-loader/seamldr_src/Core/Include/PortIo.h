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

#ifndef __IO_H__
#define __IO_H__

#include <Trace.h>

extern UINT8 __InPort8(UINT16 addr);
extern void __OutPort8(UINT16 addr, UINT8);
extern UINT16 __InPort16(UINT16 addr);
extern void __OutPort16(UINT16 addr, UINT16);
extern UINT32 __InPort32(UINT16 addr);
extern void __OutPort32(UINT16 addr, UINT32);

#if TRACE_WITH_FUNCTIONS & TRACE_IO

extern UINT8 InPort8Tr(UINT16 addr, const char *Name, UINT32 LineNumber);
extern void OutPort8Tr(UINT16 addr, UINT8, const char *Name, UINT32 LineNumber);
extern UINT16 InPort16Tr(UINT16 addr, const char *Name, UINT32 LineNumber);
extern void OutPort16Tr(UINT16 addr, UINT16, const char *Name, UINT32 LineNumber);
extern UINT32 InPort32Tr(UINT16 addr, const char *Name, UINT32 LineNumber);
extern void OutPort32Tr(UINT16 addr, UINT32, const char *Name, UINT32 LineNumber);

#define InPort8(P)      InPort8Tr(P, __FUNCTION__, __LINE__)
#define InPort16(P)     InPort16Tr(P, __FUNCTION__, __LINE__)
#define InPort32(P)     InPort32Tr(P, __FUNCTION__, __LINE__)
#define OutPort8(P, D)  OutPort8Tr(P, D, __FUNCTION__, __LINE__)
#define OutPort16(P, D) OutPort16Tr(P, D, __FUNCTION__, __LINE__)
#define OutPort32(P, D) OutPort32Tr(P, D, __FUNCTION__, __LINE__)

#else

#define InPort8(P)      __InPort8(P)
#define InPort16(P)     __InPort16(P)
#define InPort32(P)     __InPort32(P)
#define OutPort8(P, D)  __OutPort8(P, D)
#define OutPort16(P, D) __OutPort16(P, D)
#define OutPort32(P, D) __OutPort32(P, D)

#endif

#endif
