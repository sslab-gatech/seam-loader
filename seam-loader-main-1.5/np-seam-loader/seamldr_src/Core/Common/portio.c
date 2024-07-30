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
#include "portio.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
UINT8 __InPort8(UINT16 ioAddress)
{
  UINT8 alReg;

  _asm {
    mov dx, ioAddress
    in al, dx
    mov alReg, al
  }

  return alReg;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
UINT16 __InPort16(UINT16 ioAddress)
{
  UINT16 axReg;

  _asm {
    mov dx, ioAddress
    in ax, dx
    mov axReg, ax
  }

  return axReg;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
UINT32 __InPort32(UINT16 ioAddress)
{
  UINT32 eaxReg;

  _asm {
    mov dx, ioAddress
    in eax, dx
    mov eaxReg, eax
  }

  return eaxReg;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __OutPort8(UINT16 ioAddress, UINT8 data)
{
  _asm {
    mov dx, ioAddress
    mov al, data
    out dx, al
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __OutPort16(UINT16 ioAddress, UINT16 data)
{
  _asm {
    mov dx, ioAddress
    mov ax, data
    out dx, ax
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:
//
//  Input:	None
//
//  Output:	None
//
//  Description:
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __OutPort32(UINT16 ioAddress, UINT32 data)
{
  _asm {
    mov dx, ioAddress
    mov eax, data
    out dx, eax
  }
}

#if TRACE_WITH_FUNCTIONS & TRACE_IO

UINT8
InPort8Tr(UINT16 addr, const char *name, UINT32 line)
{
  UINT8 data = __InPort8(addr);

  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x>%02x\n", name, line, addr, data);
  return data;
}

void
OutPort8Tr(UINT16 addr, UINT8 data, const char *name, UINT32 line)
{
  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x<%02x\n", name, line, addr, data);
  __OutPort8(addr, data);
}

UINT16
InPort16Tr(UINT16 addr, const char *name, UINT32 line)
{
  UINT16 data = __InPort16(addr);

  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x>%04x\n", name, line, addr, data);
  return data;
}

void
OutPort16Tr(UINT16 addr, UINT16 data, const char *name, UINT32 line)
{
  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x<%04x\n", name, line, addr, data);
  __OutPort16(addr, data);
}

UINT32
InPort32Tr(UINT16 addr, const char *name, UINT32 line)
{
  UINT32 data = __InPort32(addr);

  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x>%08x\n", name, line, addr, data);
  return data;
}

void
OutPort32Tr(UINT16 addr, UINT32 data, const char *name, UINT32 line)
{
  TRACEFUNCTION(TRACE_IO, "%s#%d IO:%04x<%08x\n", name, line, addr, data);
  __OutPort32(addr, data);
}

#endif
