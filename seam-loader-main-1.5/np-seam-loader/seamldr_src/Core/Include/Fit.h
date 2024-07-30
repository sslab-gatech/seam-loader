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

#ifndef FIT_H
#define FIT_H

typedef struct _FIRMWARE_INTERFACE_TABLE_ENTRY {
  UINT64 Address;
  UINT32 Size32;
  UINT16 Version;
  UINT8  Type : 7;
  UINT8  C_V  : 1;
  UINT8  Checksum;
} FIRMWARE_INTERFACE_TABLE_ENTRY;

typedef FIRMWARE_INTERFACE_TABLE_ENTRY FitRecord;

#define FIT_TABLE_MIN_ENTRIES         3
#define FIT_TABLE_MAX_ENTRIES         0x30
#define FIT_TABLE_TYPE_HEADER         0
#define FIT_TABLE_TYPE_MICROCODE      1
#define FIT_TABLE_TYPE_STARTUP_ACM    2
#define FIT_TABLE_TYPE_BIOS_MODULE    7
//#define FIT_TABLE_TYPE_TPM_POLICY     8
#define FIT_TABLE_TYPE_BIOS_POLICY    9
#define FIT_TABLE_TYPE_TXT_POLICY     10
#define FIT_TABLE_TYPE_ANC_MANIFEST   11

#define FIT_TABLE_TYPE_FEATURE_POLICY 0x2d
// Following used to set debug policy.  This policy is slightly different--all bits are used
// and have a meaning.

#define FIT_TABLE_TYPE_TEST_VALIDATION 0x2c
#define FIT_TABLE_TYPE_ERROR_SCRTM     0x2e
#define FIT_TABLE_TYPE_JMP_DOLLAR      0x2f

#define FIT_POINTER                    0xFFFFFFC0

// These appear to be fixed so change carefully

#define DEBUG_POLICY_DISABLE_TIMEOUTS_BIT       BIT3
#define DEBUG_POLICY_TRAP_RENDEZVOUS_ERRORS_BIT BIT4
#define DEBUG_POLICY_TRACE_RENDEZVOUS_BIT       BIT5
#define DEBUG_POLICY_NO_DEBUG_PORT_BIT          BIT6
#define DEBUG_POLICY_TRAP_ERROR_BIT             BIT7

#define DEBUG_POLICY_REBOOT_TEST_MASK           0x7

#define FEATURE_POLICY_DISABLE_SMB_WRT_CHECK    BIT0
#define FEATURE_POLICY_USE_TPM2_PCREVENT        BIT1

#define BIOSAC_VALID_FEATURE_POLICY_MASK        (FEATURE_POLICY_DISABLE_SMB_WRT_CHECK | FEATURE_POLICY_USE_TPM2_PCREVENT)

//
// Externs
//
extern FIRMWARE_INTERFACE_TABLE_ENTRY *pStartupModuleEntry;
extern FIRMWARE_INTERFACE_TABLE_ENTRY *pManifestEntry;
extern FIRMWARE_INTERFACE_TABLE_ENTRY *pFirstBiosModuleEntry;

extern UINT32 EntryPointAddr;
extern UINT32 NemMemSize;
extern UINT32 BiosModuleEntryCount;
extern UINT32 LowestBiosModuleBase;

//
// Interface
//
void GetBiosEntryPoint();
void HOOK(GetFitData());
extern FitRecord *FindFitRecord(UINT8 type, UINT8 *index);

#define FIT_POLICY_USE_CACHED_TXTENABLE_FLG 0x00000001
#define FIT_POLICY_NO_IO_FLG                0x00000002

extern UINT8 GetFitPolicy(FIRMWARE_INTERFACE_TABLE_ENTRY *entry, UINT32 flags, UINT32 *policyData);
#ifdef MKF_REGRESSION
extern void SetFitIoPolicy(FIRMWARE_INTERFACE_TABLE_ENTRY *entry, UINT16 data);
#endif

#if MKF_ENGINEERING == 1
#define FIT_JUMP_DOLLAR(X) do { \
    FitRecord *_jmpFit = NULL; \
    _jmpFit = FindFitRecord(FIT_TABLE_TYPE_JMP_DOLLAR, NULL); \
    if (_jmpFit && ServerGetFitRecordData(_jmpFit, 0, NULL)) \
    TRAPLOOP((X)); \
} while (0)
#else
#define FIT_JUMP_DOLLAR(X)
#endif

#endif
