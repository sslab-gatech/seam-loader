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
//  Procedure:  coreCopyMemory
//
//  Input:  to - destination.
//          fr - source
//          len - nength of data in bytes
//
//  Output: Pointer to destination
//
//  Description: Function is similar to memcpy. Replicated and renamed to avoid
//  inclusion of standard library.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static void *coreCopyMemory(void *to, const void *fr, UINT32 len)
{
  char *d = to;
  char *s = (char *) fr;

  while (len / 4) {
    *(UINT32 *) d = *(UINT32 *) s;
    d += 4;
    s += 4;
    len -= 4;
  }

  while (len--) {
    *d++ = *s++;
  }
  return to;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  copyMemory
//
//  Input:  to - destination.
//          fr - source
//          len - nength of data in bytes
//
//  Output: Pointer to destination
//
//  Description: Function is similar to memcpy. Replicated and renamed to avoid
//  inclusion of standard library.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void *copyMemory(void *to, const void *fr, UINT32 len)
{
  INT32 Ret;

  Ret = HOOK(perform_ebp_checks((UINT32)to, (UINT32)len));

  switch (Ret) {
  case  STACK_TARGET:
    break;
  case  NOT_STACK_TARGET:
    break;
  default:
    TRACE("Safe copy operation: Stack target, stack frame error -%c.\n", MAX_DWORD - Ret + 1);
    ERROR_HANDLER_FULL(CLASS_MISC_CONFIG, ERR_STACK_FRAME, Ret);
  }

  return coreCopyMemory(to, fr, len);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  copyDataChkBoundsX
//
//  Input:  to - destination.
//          fr - source
//          len - nength of data in bytes
//          maxBound - maximum length to copy or maximum address to copy untill
//          kind - kind of maxBound - max length or max address. Two values
//          are considered for kind:
//          (kind == 0) -> MAX_LEN_BOUND or (kind != 0) -> MAX_ADDR_BOUND
//
//  Output: copied length or 0 if error
//
// Description: Data are copied from "fr" to "to". One of two bounds
//              selectable via "kind" parameter can be used: max length or max address.
//              Procedure must be used everywhere where copying is from/to
//              external source having data driven nature.
//              Bounds are limited to 32 bits - so far there is no need to copy
//              from/to above 4GB
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

UINT32 copyDataChkBoundsWithFunc(void *_to,
                                 const void *_fr,
                                 UINT32 len,
                                 UINT32 maxBound,
                                 UINT32 kind,
                                 COPY_DATA_FUNC pFunc)
{
  UINT32 maxlen;
  UINT8 *to = (UINT8 *)_to;
  UINT8 *fr = (UINT8 *)_fr;

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

  //
  // cannot wrap around from pointer too.
  //
  maxlen = 0xFFFFFFFF - (UINT32) fr;

  if (len > maxlen) {
    return 0;
  }

  //
  // Cannot overlap to and fr buffers.
  //
  if (((fr < to) && ((fr + len) > to)) ||
      ((to < fr) && ((to + len) > fr)) ||
      (fr == to)) {
    // if (((fr + len) > to) || ((to + len) > fr))
    return 0;
  }

  (*pFunc)(to, fr, len);
  return len;
}
