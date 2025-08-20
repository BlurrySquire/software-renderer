SOURCE_DIR := source
BUILD_DIR  := build

C_FLAGS_BASE := -Wall -Wextra -std=gnu11 -I$(SOURCE_DIR)

ifeq ($(platform),x11)
CC := gcc
LD := gcc

C_FLAGS   := -DPLATFORM_X11
LD_FLAGS  := -lX11

else ifeq ($(platform),redactedos)
CC := aarch64-elf-gcc
LD := aarch64-elf-ld

C_FLAGS   := -ffreestanding -nostdlib \
	-fno-exceptions -fno-unwind-tables -fno-asynchronous-unwind-tables \
	-g -O0 -mcpu=cortex-a72 \
	-DPLATFORM_REDACTEDOS -Ishared
LD_FLAGS  := -T redactedos.ld -nostdlib shared/libshared.a

endif

C_SOURCES   := $(shell find $(SOURCE_DIR) -name '*.c')
OBJECTS     := $(C_SOURCES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET := renderer.elf

all: $(TARGET)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET) $(BUILD_DIR)/*

$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(LD) $(LD_FLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS_BASE) $(C_FLAGS) -c $< -o $@