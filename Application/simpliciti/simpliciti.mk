# List of all the simpliciTi related files.
SIMPLICITISRC = ${CHIBIOS}/Application/simpliciti/Applications/application/End_Device/main_ED_BM.c \
			${CHIBIOS}/Application/simpliciti/Components/bsp/bsp.c \
			${CHIBIOS}/Application/simpliciti/Components/bsp/boards/CC430EM/bsp_board.c \
			${CHIBIOS}/Application/simpliciti/Components/bsp/boards/CC430EM/bsp_drivers.c \
			${CHIBIOS}/Application/simpliciti/Components/bsp/drivers/code/bsp_buttons.c \
			${CHIBIOS}/Application/simpliciti/Components/bsp/drivers/code/bsp_leds.c \
			${CHIBIOS}/Application/simpliciti/Components/mrfi/mrfi.c \
			${CHIBIOS}/Application/simpliciti/Components/mrfi/radios/family5/mrfi_radio.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk/nwk.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk/nwk_api.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk/nwk_frame.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk/nwk_globals.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk/nwk_QMgmt.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_freq.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_ioctl.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_join.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_link.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_mgmt.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_ping.c \
			${CHIBIOS}/Application/simpliciti/Components/nwk_applications/nwk_security.c


# Required include directories
SIMPLICITIINC = ${CHIBIOS}/Application/simpliciti \
		${CHIBIOS}/Application/simpliciti/Applications/configuration \
		${CHIBIOS}/Application/simpliciti/Components \
		${CHIBIOS}/Application/simpliciti/Components/bsp \
		${CHIBIOS}/Application/simpliciti/Components/bsp/boards/CC430EM \
		${CHIBIOS}/Application/simpliciti/Components/bsp/boards/CC430EM/bsp_external \
		${CHIBIOS}/Application/simpliciti/Components/bsp/drivers \
		${CHIBIOS}/Application/simpliciti/Components/bsp/drivers/code \
		${CHIBIOS}/Application/simpliciti/Components/bsp/mcus \
		${CHIBIOS}/Application/simpliciti/Components/mrfi \
		${CHIBIOS}/Application/simpliciti/Components/mrfi/radios/family5 \
		${CHIBIOS}/Application/simpliciti/Components/mrfi/smartrf/CC430 \
		${CHIBIOS}/Application/simpliciti/Components/nwk \
		${CHIBIOS}/Application/simpliciti/Components/nwk_applications

