/**
  Microsoft Visual Studio 7.1 Function Prototypes for I/O Intrinsics.
**/

#include "common.h"

unsigned __int64 __readmsr (int register);

#pragma intrinsic(__readmsr)

/**
  Read data to MSR.

  @param  Index                Register index of MSR.

  @return Value read from MSR.

**/
UINT64
__readMsr64 (
  IN UINT32  Index
  )
{
  return __readmsr (Index);
}