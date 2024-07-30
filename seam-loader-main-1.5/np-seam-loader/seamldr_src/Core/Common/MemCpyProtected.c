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
#include <common.h>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	get_stack_base
//
//  Input:  None
//
//  Output: stack base
//
//  Description: Returns uppermost esp value assigned when ACM starts.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

static UINT32 get_stack_base(void)
{
  return CodeSegmentStart - MCP_STACK_GAP;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	get_esp
//
//  Input:  None
//
//  Output: esp value
//
//  Description: retrieves current esp value
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
__declspec(naked) UINT32 __cdecl get_esp(void)
{
  __asm {
    mov eax, esp
        ret
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	get_ebp
//
//  Input:  None
//
//  Output: ebp value
//
//  Description: retrieves current ebp value
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static __declspec(naked) UINT32 __cdecl get_ebp(void)
{
  __asm {
    mov eax, ebp
        ret
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	get_previous_ebp
//
//  Input:  current ebp
//
//  Output: ebp of a caller
//
//  Description: retrieves ebp of a caller one level up
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static UINT32 get_previous_ebp(UINT32 ebp)
{
  return *((UINT32 *)ebp);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	is_addr_in_stack
//
//  Input:  address to check
//
//  Output: "1" - address is on stack; "0" - reached stack top; "-1" - out of stack
//
//  Description: Checks whether address belongs to stack.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static INT32 is_addr_in_stack(UINT32 addr)
{
  if ((addr < get_stack_base()) && (addr >= get_esp())) {
    return IN_STACK;
  } else {
    return OUT_OF_STACK;
  }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//  Procedure:	perform_ebp_checks
//
//  Input:  target adrdess and size to copy
//
//  Output:  none
//
//  Description: If target is on stack and overrides ebp or esp of any of the nested callers
//  error is generated, otherwise simply returns.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
INT32 perform_ebp_checks(UINT32 dest, UINT32 size)
{
  UINT32 ebp, previous_ebp;

  if (is_addr_in_stack(dest) == OUT_OF_STACK) {
    return NOT_STACK_TARGET;
  }

  ebp = get_ebp();
  if (is_addr_in_stack(ebp) == OUT_OF_STACK) {
    return ERR(1);
  }

  while (1) {
    previous_ebp = get_previous_ebp(ebp);

    //
    // This is break of infinite loop.
    // If the following check does not bring IN_STACK indicator, we either reached top of stack or stack is corrupted.
    //
    if (is_addr_in_stack(previous_ebp) != IN_STACK) {
      return ERR(2);
    }

    if ((dest >= ebp) && (dest < previous_ebp)) {
      break; // Found EBPs around dest
    }

    ebp = previous_ebp;
  }

  //
  // Changed aproach to break when stack reaches base. For testing environment this might cause infinite loop
  // but we do not have broken EBP chaine in this test environment.
  //

  //
  // Check for integer overflow before expressions are used in stack corruption detection
  //
  if ((ebp + sizeof(STACK_METADATA)) <= ebp) {
    return ERR(3); // Integer overflow detected
  }

  if ((dest + size) < dest) {
    return ERR(4); // Integer overflow detected
  }

  //
  // Stack corruption detection
  //
  if ((dest >= (ebp + sizeof(STACK_METADATA))) && ((dest + size) <= previous_ebp)) {
    return STACK_TARGET; // Copy is safe
  }

  return ERR(5);
}
