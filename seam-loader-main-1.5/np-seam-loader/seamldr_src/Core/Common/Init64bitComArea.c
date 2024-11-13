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
#include <Server/Include/common64.h>
#include <Header.h>
#include <common32.h>

#include <PSeamldrSize.h>

P_SEAMLDR_CONSTS_t PSeamldrConstAsm;
UINT32 PSeamldrSizeAsm = PSEAMLDR_SIZE;
UINT8 PSeamldrAsm[PSEAMLDR_SIZE] = { 0 };

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  Init64bitComArea
//
//  Input:      None
//
//  Output:     None
//
//  Description: All fields of Init64bitComArea communication area with
//  64-bit code are initialized.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Init64bitComArea()
{
  //
  // Initialize 32-64 bit communication data
  //

  fillMemory(SeamldrCom64Data.OriginalGdtr, 0, sizeof(SeamldrCom64Data.OriginalGdtr));
  *(UINT16 *)SeamldrCom64Data.OriginalGdtr = (UINT16)(OriginalECX >> 16);

  SeamldrCom64Data.OriginalCR4 = OriginalCR4;
  SeamldrCom64Data.HeaderStart = (UINT64)(UINTPTR)&HeaderStart;
  SeamldrCom64Data.PseamldrOffset = (UINT64)(UINTPTR)&PSeamldrAsm;
  SeamldrCom64Data.PseamldrSize = PSeamldrSizeAsm;
  SeamldrCom64Data.PseamldrConstsOffset = (UINT64)(UINTPTR)&PSeamldrConstAsm;
  SeamldrCom64Data.OriginalES = OriginalES & 0x0FF8;
  SeamldrCom64Data.OriginalFS = OriginalFS & 0x0FF8;
  SeamldrCom64Data.OriginalGS = OriginalGS & 0x0FF8;
  SeamldrCom64Data.OriginalSS = OriginalSS & 0x0FF8;
  SeamldrCom64Data.OriginalECX = OriginalECX & 0x0FF8;
  SeamldrCom64Data.OriginalIDTRLimit = (OriginalIDTR & MAX_WORD);
  TRACE("OriginalIDTR Limit: 0x%x\n", SeamldrCom64Data.OriginalIDTRLimit);
}
