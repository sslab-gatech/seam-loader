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

/**
 * Retrieves CPUID information using an extended leaf identifier.
 *
 * Executes the CPUID instruction with EAX set to the value specified by Index
 * and ECX set to the value specified by SubIndex. This function always returns
 * Index. This function is only available on IA-32 and x64.
 *
 * If Eax is not NULL, then the value of EAX after CPUID is returned in Eax.
 * If Ebx is not NULL, then the value of EBX after CPUID is returned in Ebx.
 * If Ecx is not NULL, then the value of ECX after CPUID is returned in Ecx.
 * If Edx is not NULL, then the value of EDX after CPUID is returned in Edx.
 *
 * @param  Index     The 32-bit value to load into EAX prior to invoking the
 * CPUID instruction.
 * @param  SubIndex  The 32-bit value to load into ECX prior to invoking the
 * CPUID instruction.
 * @param  Eax       The pointer to the 32-bit EAX value returned by the CPUID
 * instruction. This is an optional parameter that may be
 * NULL.
 * @param  Ebx       The pointer to the 32-bit EBX value returned by the CPUID
 * instruction. This is an optional parameter that may be
 * NULL.
 * @param  Ecx       The pointer to the 32-bit ECX value returned by the CPUID
 * instruction. This is an optional parameter that may be
 * NULL.
 * @param  Edx       The pointer to the 32-bit EDX value returned by the CPUID
 * instruction. This is an optional parameter that may be
 * NULL.
 *
 * @return Index.
 *
 **/
UINT32 CpuidEx(IN UINT32 Index,
           IN UINT32 SubIndex,
           OPTIONAL OUT UINT32* Eax,
           OPTIONAL OUT UINT32* Ebx,
           OPTIONAL OUT UINT32* Ecx,
           OPTIONAL OUT UINT32* Edx)
		   {
    
    UINT32 CpuInfo[4] = {0};
	
    (void)__cpuidex(CpuInfo, Index, SubIndex);

    if (Eax != NULL) {
        *Eax = CpuInfo[0];
    }
    if (Ebx != NULL) {
        *Ebx = CpuInfo[1];
    }
    if (Ecx != NULL) {
        *Ecx = CpuInfo[2];
    }
    if (Edx != NULL) {
        *Edx = CpuInfo[3];
    }
	
	return Index;
}