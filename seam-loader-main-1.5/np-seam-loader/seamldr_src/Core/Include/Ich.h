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

#ifndef ICH_H
#define ICH_H

#define  ICH_BUS                0

#define  ICH_DEV_31             31
#define  ICH_FUNC_0             0
#define  ICH_FUNC_3             3

#define  ICH_PM1_CNT            0x004
#define  ICH_PMBASE_OFFSET      0x040 // R40h
#define  ICH_PMEN_OFFSET        0x044 // R44h

#define  ICH_PMBASE_ADDR        0x400
#define  ICH_TCOBASE_OFFSET     0x60

#define  ICH_TCO_RLD_OFFSET     (0)
#define  ICH_TCO1_STS_OFFSET    (0x4)
#define  ICH_TCO2_STS_OFFSET    (0x6)
#define  ICH_TCO1_CNT_OFFSET    (0x8)
#define     TCO_TMR_HALT        (BIT11)

#define  ICH_TCO_RLD            (ICH_TCOBASE_OFFSET + ICH_TCO_RLD_OFFSET)
#define  ICH_TCO1_STS           (ICH_TCOBASE_OFFSET + ICH_TCO1_STS_OFFSET)
#define  ICH_TCO2_STS           (ICH_TCOBASE_OFFSET + ICH_TCO2_STS_OFFSET)
#define  ICH_TCO1_CNT           (ICH_TCOBASE_OFFSET + ICH_TCO1_CNT_OFFSET)

#define  B_ICH_LPC_ENABLES_ME2  0x02000
#define  B_ICH_LPC_ENABLES_SE   0x01000
#define  B_ICH_LPC_ENABLES_ME1  0x00800
#define  B_ICH_LPC_ENABLES_KE   0x00400
#define  B_ICH_LPC_ENABLES_HGE  0x00200
#define  B_ICH_LPC_ENABLES_LGE  0x00100
#define  B_ICH_LPC_ENABLES_FDE  0x00008
#define  B_ICH_LPC_ENABLES_PPE  0x00004
#define  B_ICH_LPC_ENABLES_CBE  0x00002
#define  B_ICH_LPC_ENABLES_CAE  0x00001
#define  R_ICH_IOPORT_PCI_INDEX 0x0CF8
#define  R_ICH_IOPORT_PCI_DATA  0x0CFC

#define  R_ICH_LPC_IO_DEC       0x080

#define ICH_PMBASE              PCIEX_ADDR(ICH_BUS, ICH_DEV_31, ICH_FUNC_0, ICH_PMBASE_OFFSET)
#define ICH_PMEN                PCIEX_ADDR(ICH_BUS, ICH_DEV_31, ICH_FUNC_0, ICH_PMEN_OFFSET)
#define IR20_DEV_FUN_OFFSET     PCIEX_ADDR(0, 20, 1, 0x190)
#define SR20_DEV_FUN_OFFSET     PCIEX_ADDR(0, 20, 1, 0xcc)

#define ICH_LPC_PCI_ADDR(REG) PCI_ADDR(ICH_BUS, ICH_DEV_31, ICH_FUNC_0, (REG))

#endif
