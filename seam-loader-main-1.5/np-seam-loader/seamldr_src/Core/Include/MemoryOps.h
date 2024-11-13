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

#ifndef MEMORY_OPS_H
#define MEMORY_OPS_H

typedef struct {
  UINT32 caller_ebp;
  UINT32 caller_eip;
  UINT8  vars[];
} STACK_METADATA;

#define IN_STACK         1
#define OUT_OF_STACK     -1

#define NOT_STACK_TARGET 0
#define STACK_TARGET     1

#define ERR(n) (-(n))

typedef void * (*COPY_DATA_FUNC)(void *, const void *, UINT32);

typedef void (*MEM_FILL_FUNC) (UINT8 *, UINT32, UINT32);

//*************** Must use methods to perform fast copy **********************************
//
// Fast copy procedure. Uses multi-byte instructions.
//
void *fastCopyData(void *to, const void *from, UINT32 length);

#define copyData(TO, FR, LEN) fastCopyData((TO), (FR), (LEN))

//*************** Must use method to perform slow copy ***********************************
//
// Slow copy procedure. Uses only DWORD and byte stransfers
//
void *copyMemory(void *to, const void *from, UINT32 length);

//*************** Must use method to perform fast copy from/to external sources **********
//
// Fast copy with bounds check
//
UINT32 copyDataChkBoundsWithFunc(void *to, const void *from, UINT32 length, UINT32, UINT32, COPY_DATA_FUNC);

#define copyDataChkBounds(TO, FROM, LEN, MAX, KIND) copyDataChkBoundsWithFunc((TO), (FROM), (LEN), (MAX), (KIND), fastCopyData)

//*************** Must use method to slow copy from/to external sources ******************
//
// Slow copy with bounds check. Note, we can't use multi-byte
// instructions to send/receive data from crb
//
#define copyMemoryChkBounds(TO, FROM, LEN, MAX, KIND) copyDataChkBoundsWithFunc((TO), (FROM), (LEN), (MAX), (KIND), copyMemory)

//*************** Must use method to fill memory with pattern ****************************
//
// Fill memroy with pattern
//
void fillMemory(UINT8 *address, UINT32 pattern, UINT32 length);

//*************** Must use method to fill memory of external sources *********************
//
// Slow memory filling with bounds check.
//
UINT32 fillMemoryChkBoundsWithFunc(void *, UINT32, UINT32, UINT32, UINT32, MEM_FILL_FUNC);

#define fillMemoryChkBounds(TO, VAL, LEN, MAX, KIND) fillMemoryChkBoundsWithFunc((TO), (VAL), (LEN), (MAX), (KIND), fillMemory)

#endif
