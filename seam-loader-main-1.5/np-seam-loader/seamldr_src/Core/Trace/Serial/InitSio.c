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
#include <trace.h>
#include <pch.h>
#include <portio.h>
#include <uart.h>

#define MAX_SIO_NUM 8

typedef UINT32 (*UINT32_NO_ARG) ();

UINT32_NO_ARG SioSupportTab[MAX_SIO_NUM] = {
#if defined (SUPPORT_SMSC1007)
  InitSioSmsc1007,
#endif
  0
};

static UINT8 saveLcr = 0;
static UINT8 saveDll = 0;
static UINT8 saveDlh = 0;

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
UINT32 InitSio()
{
  UINT32 Idx;

  for (Idx = 0; Idx < MAX_SIO_NUM; Idx++) {
    if (SioSupportTab[Idx] == NULL) {
      break;
    }
    if ((*SioSupportTab[Idx])()) {
      return TRUE;
    }
  }

  return FALSE;
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
void InitSioUart()
{
  #ifdef MKF_LPSS_UART_SUPPORT
  saveLcr = ReadMmioByte(UART2_BAR + 4 * LINE_CONTROL);
  WriteMmioByte(UART2_BAR + 4 * LINE_CONTROL, DIVISOR_LATCH_ACCESS);
  // Set Baud rate to 115k in Divisor Latch
  saveDll = ReadMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_LOW);
  WriteMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_LOW, 0x01);
  saveDlh = ReadMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_HIGH);
  WriteMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_HIGH, 0x00);
  WriteMmioByte(UART2_BAR + 4 * LINE_CONTROL, NO_STOP | NO_PARITY | BITS8);
  //Enable FIFOs using the FIFO Control register (FCR)which is at offset 0x2.
  WriteMmioByte(UART2_BAR + 4 * FIFO_CONTROL, 0x01);
  //Put the Modem Control register (MCR)in to reset state.MCR is at offset 0x04
  WriteMmioByte(UART2_BAR + 4 * MODEM_CONTROL, 0x02);
  #else
  //
  // save original UART register values,
  //   to restore later (if needed)
  //
  saveLcr = InPort8(COM_PORT + LINE_CONTROL);
  OutPort8(COM_PORT + LINE_CONTROL, DIVISOR_LATCH_ACCESS);
  // Set Baud rate to 115k in Divisor Latch
  saveDll = InPort8(COM_PORT + DIVISOR_LATCH_LOW);
  OutPort8(COM_PORT + DIVISOR_LATCH_LOW, 0x01);
  saveDlh = InPort8(COM_PORT + DIVISOR_LATCH_HIGH);
  OutPort8(COM_PORT + DIVISOR_LATCH_HIGH, 0x00);
  OutPort8(COM_PORT + LINE_CONTROL, NO_STOP | NO_PARITY | BITS8);
  OutPort8(COM_PORT + INTERRUPT_ENABLE, DISABLE_INTERRUPTS);
  #endif
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
void RestoreSioUart()
{
  //
  // Cleanup before handing off to BIOS
  // Restore original UART register values
  //
  #ifdef MKF_LPSS_UART_SUPPORT
  WriteMmioByte(UART2_BAR + 4 * LINE_CONTROL, DIVISOR_LATCH_ACCESS);
  WriteMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_HIGH, saveDlh);
  WriteMmioByte(UART2_BAR + 4 * DIVISOR_LATCH_LOW, saveDll);
  WriteMmioByte(UART2_BAR + 4 * LINE_CONTROL, saveLcr);
  #else
  OutPort8(COM_PORT + LINE_CONTROL, DIVISOR_LATCH_ACCESS);
  OutPort8(COM_PORT + DIVISOR_LATCH_HIGH, saveDlh);
  OutPort8(COM_PORT + DIVISOR_LATCH_LOW, saveDll);
  OutPort8(COM_PORT + LINE_CONTROL, saveLcr);
  #endif
}
