# List of all the MSP430 platform files.
PLATFORMSRC = ${CHIBIOS}/os/hal/platforms/MSP430/hal_lld.c \
              ${CHIBIOS}/os/hal/platforms/MSP430/pal_lld.c \
              ${CHIBIOS}/os/hal/platforms/MSP430/serial_lld.c \
			  ${CHIBIOS}/os/hal/platforms/MSP430/HAL_PMM.c \
			  ${CHIBIOS}/os/hal/platforms/MSP430/HAL_UCS.c

# Required include directories
PLATFORMINC = ${CHIBIOS}/os/hal/platforms/MSP430
