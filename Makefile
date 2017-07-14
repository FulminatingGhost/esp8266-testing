include user.cfg
SDK:=$(ESP_ROOT)/sdk
-include esp82xx/common.mf
-include esp82xx/main.mf

% :
	$(warning This is the empty rule. Something went wrong.)
	@true

SRCS += user/ssd1306_spi.c user/spi_interface.c
		
ifndef TARGET
$(info Modules were not checked out... use git clone --recursive in the future. Pulling now.)
$(shell git submodule update --init --recursive 2>/dev/null)
endif

# Example for a custom rule.
# Most of the build is handled in main.mf
.PHONY : showvars
showvars:
	$(foreach v, $(.VARIABLES), $(info $(v) = $($(v))))
	true

