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

#ifndef SEAMLDR_COM_64_DATA_H
#define SEAMLDR_COM_64_DATA_H
#pragma pack (1)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                          USAGE REQUIREMENTS
// Only general-purpose definitions can be placed in this file,
// free from chipset etc. dependencies.
//
// All definitions must be self-contained, not dependant on information from
// other include files.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

typedef struct {
    UINT16  Limit;
    UINT64  Base;
} IDTR;

typedef struct {
    UINT64 OriginalR8;
    UINT64 OriginalR9;
    UINT64 OriginalR10;
    UINT64 OriginalR11;
    UINT64 OriginalR12;
    UINT64 OriginalCR3;
    UINT32 OriginalCR4;
    UINT16 OriginalES;
    UINT16 OriginalFS;
    UINT16 OriginalGS;
    UINT16 OriginalSS;
    UINT32 OriginalECX;
    UINT16 OriginalIDTRLimit;
    IDTR   NewIDTR;
    UINT8  OriginalGdtr[10];
    UINT64 ResumeRip;
    UINT64 PtCtxPtr;
    UINT64 RetVal;
    UINT64 HeaderStart;
    UINT32 PseamldrSize;
    UINT64 PseamldrOffset;
    UINT64 PseamldrConstsOffset;
    UINT8  NewGdtr[10];
} SEAMLDR_COM64_DATA;

// whenever the structure changes, don't forget to update the ASM!
C_ASSERT(sizeof(SEAMLDR_COM64_DATA) == 0x94);




#pragma pack ()
#endif // SEAMLDR_COM_64_DATA_H


