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
//  Procedure:  GetCpuFms
//
//  Input:      None
//
//  Output:     CPU FMS.
//
//  Description: Uses CPUID function in order to retrieve CPU FMS
//  value
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
UINT32 GetCpuFms()
{
  UINT32 CpuInfo[4]; // 0-eax, 1-ebx, 2-ecx, 3-edx

  //
  // Obtain FMS
  //
  __cpuid(CpuInfo, 1);

  return CpuInfo[0] & CPUID_FMS_MASK;
}
