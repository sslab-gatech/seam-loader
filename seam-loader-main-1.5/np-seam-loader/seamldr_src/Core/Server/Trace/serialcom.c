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
#if MKF_TRACE == 1

#include <Common.h>
#include <uart.h>
#include <PortIo.h>
#include <Tpm.h>

extern UINT32 comport;
extern UINT8 accessType;
#define SERIAL_IO 0

/*
 * Procedure: XmitReadStatus
 * Input: None
 * Output:  1 if status is met
 * Description: Check for transmit buffer empty
 */
static
_serialReadStatus()
{
  UINT8 sts;
  if (accessType == SERIAL_IO)
    sts = __InPort8(comport + LINE_STATUS);
  else
    sts = __ReadMmioByte(comport + LINE_STATUS);
  return ((sts & TRANS_HOLDING_REG_EMPTY)? 1 : 0);
}

/*
 *
 * Procedure:   XmitChar
 * Input: char to send
 * Output:  None
 * Description: Send char to UART
 */
static void
__serialWriteChar(char c)
{
  while (!_serialReadStatus()) {
    ;
  }
  if (accessType == SERIAL_IO)
    __OutPort8(comport + TRANSMIT_HOLDING, (UINT8)c);
  else
    __WriteMmioByte(comport + TRANSMIT_HOLDING, (UINT8)c);
}


static void
_serialWriteChar(char c)
{
  if ( c == CHAR_LF ) {
    // Make LF into CR LF
    __serialWriteChar(CHAR_CR);
  }
  __serialWriteChar(c);
}


static UINT8
_serialPortReady(UINT8 maxRetries)
{
	UINT16 retries = maxRetries;

	if(!IS_TRACE_ENABLED) {
		return 0;
	}
	do {
	  Wait1ms();
	  if (_serialReadStatus()) {
	    break;
	  }
	} while (--retries);

	if (!retries) {
	  SET_NO_TRACE;
	  return (0);
	}
	return 1;
}

UINT8
SerialWriteString(char *str, UINT32 len)
{
  if (!_serialPortReady(traceRoutines.maxTimeout)) {
    return -1;
  }
  if (len) {
    while (len--) {
      _serialWriteChar(*str++);
    }
    return 0;
  }
  while (*str != '\0') {
    _serialWriteChar(*str++);
  }
  return 0;
}

#endif
