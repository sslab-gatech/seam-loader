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

#include "common.h"
#include "paging.h"
#include "Header.h"
#include "msr.h"
#include "MemoryOps.h"
#include "common32.h"

UINT32 ChipsetAcmType = MCP_CHIPSET_ACM_TYPE;
UINT32 TxtErrorRegister = TXT_ERROR_REGISTER;

void ProjectAcmEntryPoint()
{
  PT_CTX PtCtx;

  Init64bitComArea();

  EstablishSeamldrPaging(&SeamldrCom64Data, &PtCtx);

  SeamldrCom64Data.PtCtxPtr = (UINT64)(UINTPTR)&PtCtx;

  SeamldrThunk64();

  // No return to here
}
