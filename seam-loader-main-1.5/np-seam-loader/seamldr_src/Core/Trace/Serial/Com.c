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
#include <Tpm.h>

static const UINT32 ComAddr = 0x3f8; // COM1=3F8h, COM2=2F8h, COM3=3E8h, COM4=2E8h
static const UINT32 LineStat = 0x3f8 + 5;
static UINT8 Once = 0;

void static InitializeComPort(void)
{
  if (InitSio()) {
    __outbyte(ComAddr + 3, 0x87); // DLAB bit
    __outbyte(ComAddr + 1, 0);    // Point to MSB of baud rate divisor
    __outbyte(ComAddr, 1);        // Point to LSB of baud rate divisor
    __outbyte(ComAddr + 3, 3);    // 8 data bits, 1 stop bit, no parity
    Wait1ms();
  }
  return;
}

void ComSerialOut(unsigned char *str)
{
    #if MCP_CHIPSET_ACM_TYPE == AC_BIOSAC
  if (Once == 0) {
    Once = 1;
    InitializeComPort();
  }
    #endif

  while (*str) {
    while (0 == (_inp(LineStat) & 0x20)) {
      ;
    }
    if ((*str) == 0xa) {
      _outp(ComAddr, 0xd);
      while (0 == (_inp(LineStat) & 0x20)) {
        ;
      }
    }
    _outp(ComAddr, *str++);
  }
}
