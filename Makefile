CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD_DIR = build
TARGET = $(BUILD_DIR)/shush
OBJS_DIR = $(BUILD_DIR)/objs
OBJS = $(OBJS_DIR)/shell.o $(OBJS_DIR)/exec.o $(OBJS_DIR)/builtins.o $(OBJS_DIR)/alias.o

# default target
all: $(TARGET) 

# linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# pattern rule to build .o files from .c files
$(OBJS_DIR)/%.o: %.c 
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf BUILD_DIR
