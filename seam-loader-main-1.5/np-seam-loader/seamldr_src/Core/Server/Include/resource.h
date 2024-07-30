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

#ifndef __acm_resource__
#define __acm_resource__

#include "AcmLock.h"
#include "Spad.h"

extern volatile UINT32 FairnessCount;

typedef enum  {
	RESOURCE_BUSY = 0,
	RESOURCE_FREE,
} AcmResourceStatus;

/*
 * Checks to see if resource is free
 */
extern AcmResourceStatus IsResourceAvailable(UINT8 resource);


/*
 * lock a resources that has already been determined to be free
 * Inputs:
 *       Resource is a bit indicating which resource is being queried
 */
extern void __AcquireResource(UINT8 resource);

extern AcmResourceStatus GetResourceStatus(UINT8 resource);

extern AcmResourceStatus AcquireResource(UINT8 resource, UINT8 retry);
extern void __ReleaseResource(UINT8 resource, UINT8 force);
#define ReleaseResource(RES)  __ReleaseResource((RES), 0)

#if MKF_TRACE == 1
extern void TraceLock();
extern void TraceUnLock();
#endif

#endif
