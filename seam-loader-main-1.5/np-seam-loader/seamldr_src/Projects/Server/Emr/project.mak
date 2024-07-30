#;**********************************************************************;
#;*                                                                    *;
#;* Intel Proprietary                                                  *;
#;*                                                                    *;
#;* Copyright 2021 Intel Corporation All Rights Reserved.              *;
#;*                                                                    *;
#;* Your use of this software is governed by the TDX Source Code       *;
#;* LIMITED USE LICENSE.                                               *;
#;*                                                                    *;
#;* The Materials are provided "as is," without any express or         *;
#;* implied warranty of any kind including warranties of               *;
#;* merchantability, non-infringement, title, or fitness for a         *;
#;* particular purpose.                                                *;
#;*                                                                    *;
#;**********************************************************************;
# Project-specific variables here
#
PROJECT      := EMR
PROJECT_DIR  := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))
ACM_ROOT_DIR := $(realpath $(PROJECT_DIR)/../../..)

# TODO: Add additional project-specific vars here

# Include the main makefile that does all the actual making
#
include $(ACM_ROOT_DIR)/Projects/GnuMakefile
