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
//#include <intrin.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  readMsr
//
//  Input:  msr - MSR number to read
//
//  Output:  pHiDword and pLoDword - pointers to high and low return values
//
//  Description: Parts of MSR value are returned if pointers are not NULL
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void __readMsr(UINT32 msr_register, UINT32 *pHiDword, UINT32 *pLoDword)
{
  UINT64 msr_value = 0;

  msr_value = __readMsr64(msr_register);
  if (pHiDword != 0) {
    *pHiDword = (UINT32)(msr_value >> 32);
  }
  if (pLoDword != 0) {
    *pLoDword = (UINT32)((msr_value & (UINT64)0xFFFFFFFF));
  }
  return;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  readMsr64
//
//  Input:  msr - MSR number to read
//
//  Output:  Return 64 bits MSR register contents
//
//  Description: MSR value is returned as 64-bit value.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

UINT64 __readMsr64(UINT32 msr_register)
{
  return __readmsr(msr_register);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  writeMsr
//
//  Input:  msr - MSR number to read
//
//  Output:  None
//
//  Description: MSR is written with passed-in values.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void __writeMsr(UINT32 msr_register, UINT32 hiDword, UINT32 loDword)
{
  UINT64 value = ((UINT64)hiDword << 32) | (UINT64)loDword;

  __writemsr(msr_register, value);
  return;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  readTsc64
//
//  Input:  None
//
//  Output:  Return rdtsc value
//
//  Description: TSC value is returned as 64-bit value.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

UINT64 readTsc64(void)
{
  return __rdtsc();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:  calibrateTsc64
//
//  Input:  None
//
//  Output:  TSC Clk/Msec is returned as 64-bit value
//
//  Description: TSC Clk/Msec is returned as 64-bit value.
//               MSR_PLATFORM_INFO[15:8] * 133.33 MHz is frequency of TSC
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

UINT64 calibrateTsc64(void)
{
  UINT64 msr_value = 0;
  UINT64 result = 0;

  msr_value = __readMsr64(MSR_PLATFORM_INFO);
  result = ((msr_value & (UINT64)0xFF00) >> 8) * 133330;
  return result;
}
