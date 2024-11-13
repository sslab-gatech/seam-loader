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

%ifndef SEAMLDRCOM_EQU
%define SEAMLDRCOM_EQU 0

;COM64_DATA STRUCTURE

struc SEAMLDR_COM64_DATA

.OriginalR8:                  resq   1
.OriginalR9:	              resq   1
.OriginalR10:                 resq   1
.OriginalR11:                 resq   1
.OriginalR12:                 resq   1
.OriginalCR3:                 resq   1
.OriginalCR4:                 resd   1
.OriginalES:                  resw   1
.OriginalFS:                  resw   1
.OriginalGS:                  resw   1
.OriginalSS:                  resw   1
.OriginalECX                  resd   1
.OriginalIDTRLimit:           resw   1
.NewIDTR:               	  resb   10
.OriginalGdtr:                resb   10
.ResumeRip:               	  resq   1
.PtCtxPtr:                    resq   1
.RetVal:                      resq   1
.HeaderStart:                 resq   1
.PseamldrSize:                resd   1
.PseamldrOffset:              resq   1
.PseamldrConstsOffset:     	  resq   1
.NewGdtr:     				  resb   10
endstruc


%endif ;SEAMLDRCOM_EQU