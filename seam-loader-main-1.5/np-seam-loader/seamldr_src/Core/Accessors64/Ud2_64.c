/**
  Microsoft Visual Studio 7.1 Function Prototypes for I/O Intrinsics.
**/
#include "common.h"

#pragma intrinsic(__ud2)

/**
  Generates an undefined instruction.
**/
void
_ud2 (
  void
  )
{
  __ud2 ();
}
