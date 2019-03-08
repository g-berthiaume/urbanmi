#-----------------------------------------------------
# Simple makefile
#
# G. Berthiaume - 2019
#-----------------------------------------------------

#                        #
# USER DEFINE VARIABLES  #
#                        #

# What is the complier
CC ?= gcc 

# What is the output name
TARGET_EXEC ?= urbanmi

# Where to build ? 
BUILD_DIR ?= ./build

# Where are the source ? 
SRC_DIRS ?= ./src

# Flags
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS 	 ?= $(INC_FLAGS) -Wall -Wextra -g -std=c11 -O2 # -fsanitize=address
CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

#                  #
# GLOBAL VARIABLES #
#                  #

# Finding the dependecies
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)


#           #
# COMMNANDS #
#           #
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean # 'make clean' will run the recipe regardless of whether there is a file named clean.

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p