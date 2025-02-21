BOARDCPPSRC =  $(BOARD_DIR)/board_configuration.cpp \
    $(BOARD_DIR)/firmware/pinouts.cpp \
    $(BOARD_DIR)/default_tune.cpp \


BOARDINC += $(BOARD_DIR)/generated/controllers/generated

# defines SHORT_BOARD_NAME
include $(BOARD_DIR)/meta-info.env

# reduce memory usage monitoring
DDEFS += -DRAM_UNUSED_SIZE=100

# assign critical LED to a non-existent pin
# DDEFS += -DLED_CRITICAL_ERROR_BRAIN_PIN=Gpio::I15

# This board has 512K STM32F407
DDEFS += -DMIN_FLASH_SIZE=512
DDEFS += -DEFI_LUA=FALSE

# This board has no storage
DDEFS += -DEFI_FILE_LOGGING=FALSE
USE_FATFS = no