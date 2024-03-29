##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -O2 -ggdb -fomit-frame-pointer
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT = 
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = no
endif

# Enable register caching optimization (read documentation).
# Option not tested on MSP430, DO NOT USE.
ifeq ($(USE_CURRP_CACHING),)
  USE_CURRP_CACHING = no
endif

#
# Build global options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = ch

# Define linker script file here
LDSCRIPT = msp430.x
#LDSCRIPT = $(CHIBIOS)/Application/CC430-CC430F6137-GCC/msp430.x

# Imported source files
#CHIBIOS = ../..
CHIBIOS = .
include $(CHIBIOS)/boards/ezChronos_CC430_F6137/board.mk
include $(CHIBIOS)/os/hal/platforms/MSP430/platform.mk
include $(CHIBIOS)/os/hal/hal.mk
include $(CHIBIOS)/os/ports/GCC/MSP430/port.mk
include $(CHIBIOS)/os/kernel/kernel.mk
include $(CHIBIOS)/Application/drivers/drivers.mk
include $(CHIBIOS)/Application/logic/logic.mk
#include $(CHIBIOS)/Application/simpliciti/simpliciti.mk
#include $(CHIBIOS)Application/logic/logic.mk
#include $(CHIBIOS)/test/test.mk

# C sources here.
CSRC = $(PORTSRC) \
       $(KERNSRC) \
       $(TESTSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
	$(DRIVERSSRC) \
	$(SIMPLICITISRC) \
	$(CHIBIOSSRC) \
       $(CHIBIOS)/os/various/evtimer.c \
       $(CHIBIOS)/Application/CC430-CC430F6137-GCC/main.c

# C++ sources here.
CPPSRC =

# List ASM source files here
ASMSRC = $(PORTASM)

INCDIR = $(PORTINC) $(KERNINC) $(TESTINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) \
	$(DRIVERSINC) $(LOGICINC) $(SIMPLICITIINC) \
         $(CHIBIOS)/os/various

#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = cc430f6137

TRGT = msp430-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
OD   = $(TRGT)objdump
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

# Define C warning options here
CWARN = -Wall -Wextra -Wstrict-prototypes

# Define C++ warning options here
CPPWARN = -Wall -Wextra

#
# Compiler settings
##############################################################################

##############################################################################
# Start of default section
#

# List all default C defines here, like -D_DEBUG=1
DDEFS = -D__CC430F6137__ -D__MSP430_6137__ -DMRFI_CC430 -DELIMINATE_BLUEROBIN -DISM_EU -DELIMINATE_SIMPLICITI

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =

# List all default directories to look for include files here
DINCDIR = $(CHIBIOS)/Application/drivers \
	$(CHIBIOS)/Application/logic \
	$(CHIBIOS)/Application/CC430-CC430F6137-GCC \
	/usr/msp430/include/

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS =

#
# End of default section
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

#
# End of user defines
##############################################################################

include $(CHIBIOS)/os/ports/GCC/MSP430/rules.mk
