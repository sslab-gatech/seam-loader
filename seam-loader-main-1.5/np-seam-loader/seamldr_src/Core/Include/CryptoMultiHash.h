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

#ifndef CRYPTO_MULTI_H
#define CRYPTO_MULTI_H

typedef struct _MultiHashState {
  TPML_DIGEST_VALUES_MAX Digests;
  UINT8                  HashControl;
} MultiHashState;

UINT8 GetDefaultHashControl();
void MultiHashStart(MultiHashState *pMultiHashState);
void MultiHashFinal(MultiHashState *pMultiHashState);
void MultiHashUpdate(UINT8 *pMsg, UINT32 MsgLen, MultiHashState *pMultiHashState);
void MultiHashTarget(UINT8 *pMsg, UINT32 MsgLen, MultiHashState *pMultiHashState);
void CumulativeMultiHashTarget(GET_DATA pFunc, MultiHashState *pMultiHashState);
void MultiHashPrint(MultiHashState *pMultiHashState, const char *fmt);

#endif
