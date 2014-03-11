# List of all the board related files.
BOARDSRC = ${CHIBIOS}/Application/drivers/display.c \
			${CHIBIOS}/Application/drivers/timer.c \
			${CHIBIOS}/Application/drivers/ports.c \
			${CHIBIOS}/Application/drivers/radio.c \
			${CHIBIOS}/Application/drivers/rf1a.c \
			${CHIBIOS}/Application/drivers/buzzer.c 

# Required include directories
BOARDINC = ${CHIBIOS}/Application/drivers \
	  $(CHIBIOS)/Application/logic
