/**
  Microsoft Visual Studio 7.1 Function Prototypes for I/O Intrinsics.
**/
#include "common.h"

void __writemsr (unsigned long Register, unsigned __int64 Value);

#pragma intrinsic(__writemsr)

/**
  Write data to MSR.

  @param  Index                The register index of MSR.
  @param  Value                Data wants to be written.

  @return Value written to MSR.

**/
void
__writeMsr64 (
  IN UINT32  Index,
  IN UINT64  Value
  )
{
  __writemsr (Index, Value);
}
