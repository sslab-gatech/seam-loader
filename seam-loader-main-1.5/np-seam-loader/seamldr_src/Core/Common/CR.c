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
//  Procedure:   Update_CRx
//
//  Input:  None
//
//  Output:  None
//
//  Description:  set CR0 and CR4. This procedure destroys registers
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void Update_CRx(void)
{
  UINT32 value_eax = 0;

  //Make sure osxsave and osfxsr are set

  value_eax = __readcr4();
  value_eax = value_eax | (CR4_PAE + CR4_SMXE);

  __writecr4(value_eax);

  // SEAMLDR should follow the spec and initialize CR0 explicitly to the value 0x21 (PE + NE bit set, all others are cleared)

  value_eax = CR0_PE + CR0_NE;
  __writecr0(value_eax);

  return;
}
