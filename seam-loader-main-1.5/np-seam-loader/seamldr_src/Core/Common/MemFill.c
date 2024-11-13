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
  INT32 Ret;

  Ret = HOOK(perform_ebp_checks((UINT32)start_addr, (UINT32)len));

  switch (Ret) {
  case  STACK_TARGET:
    break;
  case  NOT_STACK_TARGET:
    break;
  default:
    TRACE("Safe fill operation: Stack target, stack frame error -%c.\n", MAX_DWORD - Ret + 1);
    ERROR_HANDLER_FULL(CLASS_MISC_CONFIG, ERR_STACK_FRAME, Ret);
  }

  coreFillMemory(start_addr, val, len);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  fillMemoryChkBoundsWithFunc
//
//  Input:  to - destination.
//          val - value to fill memory with
//          len - length of memory to fill in bytes
//          maxBound - maximum length to copy or maximum address to copy untill
//          kind - kind of maxBound - max length or max address. Two values
//          are considered for kind:
//          (kind == 0) -> MAX_LEN_BOUND or (kind != 0) -> MAX_ADDR_BOUND
//
//  Output: filled length or 0 if error
//
// Description: "to" with lemngt "len" is filled wiht "val".
//              One of two bounds selectable via "kind" parameter can
//              be used: max length or max address.
//              Procedure must be used everywhere where filled memory
//              is controlled by external data.
//              Bounds are limited to 32 bits - so far there is no need to copy
//              from/to above 4GB
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

UINT32 fillMemoryChkBoundsWithFunc(void *_to,
                                   UINT32 val,
                                   UINT32 len,
                                   UINT32 maxBound,
                                   UINT32 kind,
                                   MEM_FILL_FUNC pFunc)
{
  UINT32 maxlen;
  UINT8 *to = (UINT8 *)_to;

  if (kind == MAX_ADDR_BOUND) {
    //
    // Destination must be less then bound address
    //
    if ((UINT32) to > maxBound) {
      return 0;
    }
    //
    // maximum len to copy is difference between max address and
    // destination.
    //
    maxlen = maxBound - (UINT32) to;
  } else {
    if (len > maxBound) {
      return 0;
    }
    //
    // If len is set as bound, we cannot wrap around.
    //
    maxlen = 0xFFFFFFFF - (UINT32) to;
  }

  //
  // abort if over length.
  //
  if (len > maxlen) {
    return 0;
  }

  (*pFunc)(to, val, len);
  return len;
}
