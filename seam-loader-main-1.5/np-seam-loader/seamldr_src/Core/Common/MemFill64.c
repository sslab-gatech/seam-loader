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

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  coreFillMemory
//
//  Input:  Start - start address
//          Len - length to fill in bytes.
//          Val - pattern to store
//
//  Output:  None
//
//  Description:  Initializes "Len" bytes of memory with pattern "Val"
//                starting from "Start" address.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void coreFillMemory(UINT8 *start_addr, UINT32 val, UINT32 len)
{
  UINT32 i = 0;

  for (i = 0; i < len / 4; i++) {
    *((UINT32 *)start_addr) = val;
    start_addr += 4;
  }

  UINT8 *pattern = (UINT8 *)&val;

  for (i = 0; i < (len % 4); i++) {
    *(start_addr + i) = *(pattern + i);
  }
  return;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  fillMemory
//
//  Input:  Start - start address
//          Len - length to fill in bytes.
//          Val - pattern to store
//
//  Output:  None
//
//  Description:  Initializes "Len" bytes of memory with pattern "Val"
//                starting from "Start" address.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void fillMemory(UINT8 *start_addr, UINT32 val, UINT32 len)
{
  coreFillMemory(start_addr, val, len);
}