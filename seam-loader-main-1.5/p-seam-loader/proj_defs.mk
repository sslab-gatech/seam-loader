# proj_defs.mk - Project related defintions

PROJ_FLAGS = 

ifndef RELEASE
PROJ_FLAGS += -DDEBUG
endif

ifdef SEAM_INST_SUPPORT
PROJ_FLAGS += -DSEAM_INSTRUCTIONS_SUPPORTED_IN_COMPILER
endif

#Versioning
ifndef PSEAMLDR_BUILD_DATE
PROJ_FLAGS += -DPSEAMLDR_BUILD_DATE=$(shell date +%Y%m%d)
endif

ifdef PSEAMLDR_BUILD_NUM
PROJ_FLAGS += -DPSEAMLDR_BUILD_NUM=$(PSEAMLDR_BUILD_NUM)
else
PROJ_FLAGS += -DPSEAMLDR_BUILD_NUM=0
endif

ifdef PSEAMLDR_MINOR_VER
PROJ_FLAGS += -DPSEAMLDR_MINOR_VER=$(PSEAMLDR_MINOR_VER)
else
PROJ_FLAGS += -DPSEAMLDR_MINOR_VER=0
endif

ifdef PSEAMLDR_MAJOR_VER
PROJ_FLAGS += -DPSEAMLDR_MAJOR_VER=$(PSEAMLDR_MAJOR_VER)
else
PROJ_FLAGS += -DPSEAMLDR_MAJOR_VER=1
endif
