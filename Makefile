# Thanks makefiletutorial.com!
TARGET_EXEC := juh

BUILD_DIR := ./build
SRC_DIRS := ./src

# Grabs every .c and .s file for compilation
SRCS := $(shell find $(SRC_DIRS) -name '*.c' -or -name '*.s')

# Builds everything as a .o file
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Turns .o into .d for GCC
DEPS := $(OBJS:.o=.d)

# Scan our source directory for any other directories (headers might be there)
INC_DIRS := ./inc

# We need an '-I' before our headers so GCC will process them
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Generates Makefiles from our .d files we generated
CPPFLAGS := $(INC_FLAGS) -MMD -MP

# Final Build Step
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) -lraylib $(OBJS) -o $@ $(LDFLAGS)

# Build Step for C Source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Include our Generated Makefiles
-include $(DEPS)
