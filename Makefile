###############################################################################
################### MOOSE Application Standard Makefile #######################
###############################################################################
#
# Optional Environment variables
# MOOSE_DIR        - Root directory of the MOOSE project
#
###############################################################################
# Use the MOOSE submodule if it exists and MOOSE_DIR is not set
MOOSE_SUBMODULE    := $(CURDIR)/moose
ifneq ($(wildcard $(MOOSE_SUBMODULE)/framework/Makefile),)
  MOOSE_DIR        ?= $(MOOSE_SUBMODULE)
else
  MOOSE_DIR        ?= $(shell dirname `pwd`)/moose
endif

# framework
FRAMEWORK_DIR      := $(MOOSE_DIR)/framework
include $(FRAMEWORK_DIR)/build.mk
include $(FRAMEWORK_DIR)/moose.mk

################################## MODULES ####################################
# To use certain physics included with MOOSE, set variables below to
# yes as needed.  Or set ALL_MODULES to yes to turn on everything (overrides
# other set variables).

ALL_MODULES                 := no

CHEMICAL_REACTIONS          := no
CONTACT                     := no
EXTERNAL_PETSC_SOLVER       := no
FLUID_PROPERTIES            := no
FSI                         := no
FUNCTIONAL_EXPANSION_TOOLS  := no
GEOCHEMISTRY                := no
HEAT_CONDUCTION             := no
LEVEL_SET                   := no
MISC                        := no
NAVIER_STOKES               := yes
PERIDYNAMICS                := no
PHASE_FIELD                 := no
POROUS_FLOW                 := no
RAY_TRACING                 := no
REACTOR                     := no
RDG                         := no
RICHARDS                    := no
STOCHASTIC_TOOLS            := no
TENSOR_MECHANICS            := no
XFEM                        := no

include $(MOOSE_DIR)/modules/modules.mk
###############################################################################

# dep apps
APPLICATION_DIR    := $(CURDIR)
APPLICATION_NAME   := fv_app_pynn
BUILD_EXEC         := yes
GEN_REVISION       := no
include            $(FRAMEWORK_DIR)/app.mk

###############################################################################
# Additional special case targets should be added here
torch_dynamic := yes
ifneq (,$(findstring darwin,$(libmesh_HOST)))
        lib_suffix := dylib
else
        lib_suffix := so
endif
ifeq ($(torch_dynamic),yes)
        dynamic_lib := dynamicLibBuild=1
else
        lib_suffix := a
endif
TORCH_INC_PATH := -I/home/aiskhak2/projects/pytorch-install-moose/include -I/home/aiskhak2/projects/pytorch-install-moose/include/torch/csrc/api/include
TORCH_LIB_PATH := /home/aiskhak2/projects/pytorch-install-moose/lib
USE_CUDA := False
ifeq ($(USE_CUDA),True)
    TORCH_LIBS = -ltorch -lcaffe2 -lcaffe2_gpu -lc10 -lc10_cuda -lcuda -lnvrtc -lnvToolsExt # -lnccl -lmkldnn -lmkl_rt
else
    TORCH_LIBS = -ltorch -ltorch_cpu -lc10
endif
TORCH_DEPEND_LIBS  := $(TORCH_LIB_PATH)/*.$(lib_suffix)
app_INCLUDES += $(TORCH_INC_PATH)
$(info VAR="$(CONDA_PREFIX)")
$(info suffux = $(lib_suffix))
$(info lib = $(TORCH_LIB_PATH))
ADDITIONAL_DEPEND_LIBS += $(TORCH_DEPEND_LIBS)
ADDITIONAL_LIBS += -L$(TORCH_LIB_PATH) -Wl,-rpath,$(TORCH_LIB_PATH) $(TORCH_LIBS) -pthread #-D_GLIBCXX_USE_CXX11_ABI=0 -std=c++11
