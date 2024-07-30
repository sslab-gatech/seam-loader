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

#ifndef __SPAD_H__
#define __SPAD_H__

#define LT_SPAD_SERVER_RESERVE_1           BIT0 - BIT22
#define LT_SPAD_MSEG_COHERENCY             BIT23
#define LT_SPAD_SERVER_RESERVE_2           BIT24 - BIT29

#define LT_SPAD_BPT_TXT_PASSED             BIT30
#define LT_SPAD_BPT_BTG_PASSED             BIT31
#define LT_SPAD_BPT_BLOCK_BOOT             BIT32
#define LT_SPAD_PFR_SCRTM_SUCCESS          BIT33

#define LT_SPAD_S3_TPM_STARTUP_FAILED      BIT46
#define LT_SPAD_POWER_DOWN_EXECUTED        BIT47
#define LT_SPAD_BTG_FAILED                 BIT48
#define LT_SPAD_SERIAL_ENABLED             BIT49
#define LT_SPAD_READY_TO_EXIT              BIT50
#define LT_SPAD_COIN_BATTERY_REMOVED       BIT51
#define LT_SPAD_COIN_BATTERY_REMOVED_VALID BIT52
#define LT_SPAD_TXT_POLICY                 BIT53
#define LT_SPAD_TXT_POLICY_VALID           BIT54
#define LT_SPAD_NON_LEGACY_SOCKET          BIT55
#define LT_SPAD_SBSP_CODE_ENTERED          BIT56

#define LT_SPAD_UNLOCK_NEEDED              BIT58
#define LT_SPAD_BIOS_TRUSTED               BIT59
#define LT_SPAD_TXT_DISABLED               BIT60
#define LT_SPAD_CPU_HOT_PLUG               BIT61
#define LT_SPAD_CPU_ERROR                  BIT62
#define LT_SPAD_SACM_SUCCESS               BIT63

#define SPAD_STATE(X) LT_SPAD_ ## X

extern UINT8 __IsAcmGlobalStateSet(UINT64 sts);
extern void __AcmGlobalStateClear(UINT64 sts);
extern void __AcmGlobalStateSet(UINT64 sts);

#if TRACE_WITH_FUNCTIONS & TRACE_GSTATE

extern UINT8 _IsAcmGlobalStateSet(UINT64 sts, const char *, char *, UINT32);
#define IsAcmGlobalStateSet(X) _IsAcmGlobalStateSet(SPAD_STATE(X), STRINGIFY(X), __FUNCTION__, __LINE__)

extern void _AcmGlobalStateClear(UINT64 sts, const char *, char *, UINT32);
#define AcmGlobalStateClear(X) _AcmGlobalStateClear(SPAD_STATE(X), STRINGIFY(X), __FUNCTION__, __LINE__)

extern void _AcmGlobalStateSet(UINT64 sts, const char *, char *, UINT32);
#define AcmGlobalStateSet(X)   _AcmGlobalStateSet(SPAD_STATE(X), STRINGIFY(X), __FUNCTION__, __LINE__)
#else
#define IsAcmGlobalStateSet(X) __IsAcmGlobalStateSet(SPAD_STATE(X))
#define AcmGlobalStateClear(X) __AcmGlobalStateClear(SPAD_STATE(X))
#define AcmGlobalStateSet(X)   __AcmGlobalStateSet(SPAD_STATE(X))
#endif

#endif
