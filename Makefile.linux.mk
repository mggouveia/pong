#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX = gcc

INCLUDE   = -I$(INT_DIR) -I$(INC_DIR)
LFLAGS    = -lSDL2
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c99 -fPIC -m64

#--------------------------------------------------------
# sources
#--------------------------------------------------------
SOURCES = $(shell find $(SRC_DIR) -name '*.c')

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCES))
DEPS	= $(OBJECTS:.o=.d)

#--------------------------------------------------------
# app rules
#--------------------------------------------------------
all: linux
linux: $(BIN_DIR)$(TARGET)

#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)$(TARGET)

#--------------------------------------------------------
# objects and target rules
#--------------------------------------------------------

$(BIN_DIR)$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS) $(LFLAGS)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $@
