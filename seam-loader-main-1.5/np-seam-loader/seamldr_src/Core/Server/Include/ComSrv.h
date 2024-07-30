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

#ifndef COMSRV_H
#define COMSRV_H
          
//-----------------------------------------------------------------------------
//
//                            WARNING!      
// 
// Only unique offsets must be defined here. Offsets common for all
// platforms shall be defined in RootComplex.h or Pch.h files. 
//
//-----------------------------------------------------------------------------

//
// MCHBAR
//

#define MCH_REGBAR_OFFSET                                    0x5420
#define MCH_LOCK_OFFSET                                      0x50FC
#define MCH_UMAGFXBASE_OFFSET                                0x6010
#define MCH_UMAGFXLIMIT_OFFSET                               0x6018
#define MCH_UMAGFXCTL_OFFSET                                 0x6020

#define MCH_REGBAR_OFFSET                                    0x5420
#define MCH_IPUVTDLBAR_OFFSET                                0x7880
#define MCH_IPUVTDHBAR_OFFSET                                0x7884

#define MCHBAR_CH0_CR_MC_INIT_STATE_0_0_0_MCHBAR             0x4254 // Channel 0 rank occupancy in bits [7:0]
  #define MAX_RC_BITS                                          0xFF // Max Rank Occupancy bits
#define MCHBAR_CH1_CR_MC_INIT_STATE_0_0_0_MCHBAR             0x4654 // Channel 1 rank occupancy in bits [7:0]
#define MCDECS_CR_MAD_INTER_CHANNEL_0_0_0_MCHBAR_MCMAIN      0x5000 // Channel assignment
#define MCDECS_CR_MAD_INTRA_CH0_0_0_0_MCHBAR_MCMAIN          0x5004 // Address decoder intra channel cfg reg
#define MCDECS_CR_MAD_INTRA_CH1_0_0_0_MCHBAR_MCMAIN          0x5008 // Address decoder intra channel cfg reg
#define MCDECS_CR_MAD_DIMM_CH0_0_0_0_MCHBAR_MCMAIN           0x500C // Address decode DIMM parameters
#define MCDECS_CR_MAD_DIMM_CH1_0_0_0_MCHBAR_MCMAIN           0x5010 // Address decode DIMM parameters
#define MCDECS_CR_CHANNEL_HASH_0_0_0_MCHBAR_MCMAIN           0x5024 // Channel Selection Hash Register
#define MCDECS_CR_MC_INIT_STATE_G_0_0_0_MCHBAR_MCMAIN        0x5030 // Init register
#define MCDECS_CR_MRC_REVISION_0_0_0_MCHBAR_MCMAIN           0x5034 // BIOS MRC Revision ???
#define MCDECS_CR_MC_LOCK_0_0_0_MCHBAR_MCMAIN                0x50FC // Lock register

#endif
