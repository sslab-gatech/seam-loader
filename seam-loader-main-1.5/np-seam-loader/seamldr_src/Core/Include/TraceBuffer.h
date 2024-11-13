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

#ifndef TRACEBUFFER_H_
#define TRACEBUFFER_H_

#if MKF_TRACE == 1
#include <Common.h>
#include <Trace.h>

typedef struct _traceBuffer {
  UINT8 *buffer;
  UINT32 len;
  UINT32 bufferCount;
  UINT32 maxCount; // Might be useful to see how full we ever get
  UINT32 writeString;
  UINT32 writeChar;
} TRACEBUFFER;

extern TRACEBUFFER traceBuffer;

static UINT32 BufferChar(char c);
extern UINT8 BufferWriteString(unsigned char *str, UINT32 len);
extern void InitializeTraceBuffer(UINT8 *buffer, UINT32 size);
extern void FlushTraceBuffer();
#endif

#endif /* TRACEBUFFER_H_ */
