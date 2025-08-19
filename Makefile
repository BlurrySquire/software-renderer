CC  := gcc
CXX := g++

SOURCE_DIR := source
BUILD_DIR  := build

C_FLAGS   := -Wall -Wextra -std=gnu11 -I$(SOURCE_DIR) -DPLATFORM_X11
LD_FLAGS  := -lX11

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
	$(CXX) $(LD_FLAGS) $(OBJECTS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) -c $< -o $@