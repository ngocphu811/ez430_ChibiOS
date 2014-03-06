.PHONY: clean All

All:
	@echo ----------Building project:[ ez430_ChibiOS - Debug ]----------
	@"C:\Program Files\BeRTOS SDK\cygwin\bin\make.exe"  -j 2 -f "ez430_ChibiOS.mk"
clean:
	@echo ----------Cleaning project:[ ez430_ChibiOS - Debug ]----------
	@"C:/Program Files/BeRTOS SDK/cygwin/bin/make.exe"  -j 2 -f "ez430_ChibiOS.mk" clean
