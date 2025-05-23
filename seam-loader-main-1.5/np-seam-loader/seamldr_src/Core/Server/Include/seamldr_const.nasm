;**********************************************************************;
;*                                                                    *;
;* Intel Proprietary                                                  *;
;*                                                                    *;
;* Copyright 2021 Intel Corporation All Rights Reserved.              *;
;*                                                                    *;
;* Your use of this software is governed by the TDX Source Code       *;
;* LIMITED USE LICENSE.                                               *;
;*                                                                    *;
;* The Materials are provided "as is," without any express or         *;
;* implied warranty of any kind including warranties of               *;
;* merchantability, non-infringement, title, or fitness for a         *;
;* particular purpose.                                                *;
;*                                                                    *;
;**********************************************************************;

struc P_SEAMLDR_CONST
.CDataStackSize:                        resq 1
.CCodeRgnSize:                          resq 1
.CDataRgnSize:                          resq 1
.CKeyholeRgnSize:                       resq 1
.CKeyholeEditRgnSize:                   resq 1
.CEntryPointOffset:                     resq 1
endstruc