BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
    $(BOARD_DIR)/firmware/pinouts.cpp \
    $(BOARD_DIR)/default_tune.cpp \


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

DDEFS += -DDISABLE_PIN_STATE_VALIDATION=TRUE

# quick board start-up with less fancy bootloader
DDEFS += -DBOOT_BACKDOOR_ENTRY_TIMEOUT_MS=0

DDEFS += -DEFI_LOGIC_ANALYZER=FALSE
DDEFS += -DEFI_MALFUNCTION_INDICATOR=FALSE

# reduce memory usage monitoring
DDEFS += -DRAM_UNUSED_SIZE=100

# assign critical LED to a non-existent pin
DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::B7


# we do not have much Lua RAM, let's drop some fancy functions
DDEFS += -DWITH_LUA_CONSUMPTION=FALSE
DDEFS += -DWITH_LUA_PID=FALSE
DDEFS += -DWITH_LUA_STOP_ENGINE=FALSE

DDEFS += -DEFI_LUA=FALSE
DDEFS += -DFLASH_ADDR=0x08075000
DDEFS += -DMIN_FLASH_SIZE=512
DDEFS += -DEFI_HD44780_LCD=FALSE


# This board has no storage
DDEFS += -DEFI_FILE_LOGGING=FALSE
USE_FATFS = no

ifeq ($(BOARD_HAS_EXT_FLASH),yes)
    # MRE has optional external SPI flash that uses ChibiOS MFS driver
    include $(PROJECT_DIR)/hw_layer/ports/stm32/use_higher_level_flash_api.mk
    include $(PROJECT_DIR)/hw_layer/drivers/flash/w25q/w25q_single_spi.mk
    # Otherwise writeToFlashNow() is called from ISR context (slow timer callback)
    DDEFS += -DEFI_FLASH_WRITE_THREAD=TRUE
    DDEFS += -DEFI_STORAGE_MFS_EXTERNAL=TRUE
    # Move persistentState out of CCM as it should be accessible by DMA
    DDEFS += -DPERSISTENT_LOCATION=""
    # Move LUA heap to CCM
    DDEFS += -DLUA_HEAD_RAM_SECTION=CCM_OPTIONAL
    BOARDCPPSRC += $(BOARD_DIR)/board_storage.cpp
endif

