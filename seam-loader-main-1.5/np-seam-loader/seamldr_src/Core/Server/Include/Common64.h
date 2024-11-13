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

#ifndef COMMON64_H
#define COMMON64_H
#pragma pack (1)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//                          USAGE REQUIREMENTS
// Only general-purpose definitions can be placed in this file,
// free from chipset etc. dependencies.
//
// All definitions must be self-contained, not dependant on information from
// other include files.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef _SEAMLDR_VALIDATION_

#pragma data_seg("EDATA32")
#pragma bss_seg("EDATA32")
#pragma const_seg("EDATA32")

#define UINT8  unsigned __int8          // char
#define UINT16 unsigned __int16         // short int
#define UINT32 unsigned __int32         // long
#define UINT64 unsigned __int64         // long long

#endif //_SEAMLDR_VALIDATION_

#include "SeamldrCom64Data.h"

//-----------------------------------------------------------------------------
// Leaf value (in eax) calling GETSEC
//-----------------------------------------------------------------------------
#define CAPABILITIES		0
#define ENTERACCS				2
#define EXITAC				  3
#define SENTER				  4
#define SEXIT				    5
#define PARAMETERS			6
#define SMCTRL					7
#define WAKEUP					8



#define ZMM_REG_QWORDS 8
#define YMM_REG_QWORDS 4

#define LT_SINIT_BASE 0xFED20270
#define LT_SINIT_SIZE 0xFED20278

#define REQ_CSE_WAKE  1

// Return status
#define CSE_ACTIVE    0
#define REQ_SUCCESS   1



#define LT_SINIT_BASE 0xFED20270
#define LT_SINIT_SIZE 0xFED20278


extern  SEAMLDR_COM64_DATA SeamldrCom64Data;

void  Entry64 ();  
void  SeamldrCom64(SEAMLDR_COM64_DATA *);
void Init64bitComArea();

#define TXT_SHUTDOWN()             __ud2();
void PauseCpu(void);


#pragma pack ()
#endif


