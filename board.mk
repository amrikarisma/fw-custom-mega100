BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
	$(BOARD_DIR)/board_storage.cpp \
    $(BOARD_DIR)/firmware/pinouts.cpp \
    $(BOARD_DIR)/default_tune.cpp \


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# reduce memory usage monitoring
DDEFS += -DRAM_UNUSED_SIZE=100

# assign critical LED to a non-existent pin
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::Unassigned


# we do not have much Lua RAM, let's drop some fancy functions
DDEFS += -DWITH_LUA_CONSUMPTION=FALSE
DDEFS += -DWITH_LUA_PID=FALSE
DDEFS += -DWITH_LUA_STOP_ENGINE=FALSE

# This board uses ChibiOS MFS driver on external SPI flash
include $(PROJECT_DIR)/hw_layer/ports/stm32/use_higher_level_flash_api.mk
#Serial flash driver
include $(PROJECT_DIR)/hw_layer/drivers/flash/w25q/w25q_single_spi.mk

# Otherwise writeToFlashNow() is called from ISR context (slow timer callback)
DDEFS += -DEFI_FLASH_WRITE_THREAD=TRUE
DDEFS += -DEFI_STORAGE_MFS_EXTERNAL=TRUE
# Move persistentState out of CCM as it should be accessible by DMA
DDEFS += -DPERSISTENT_LOCATION=""
DDEFS += -DLUA_HEAD_RAM_SECTION=CCM_OPTIONAL
