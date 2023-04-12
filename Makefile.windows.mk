#--------------------------------------------------------
# compilation configuration
#--------------------------------------------------------
CXX = x86_64-w64-mingw32-gcc

INCLUDE   = -I$(INT_DIR) -I$(INC_DIR)
LFLAGS    = -mwindows -lmingw32 -lSDL2main -lSDL2
CFLAGS    = -MD -MP -Wall -Werror -pedantic -std=c99 -m64

#--------------------------------------------------------
# sources
#--------------------------------------------------------
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))
SOURCES = $(call rwildcard,$(SRC_DIR),*.c)

#--------------------------------------------------------
# objects ans dependencies
#--------------------------------------------------------
OBJECTS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SOURCES))
DEPS	= $(OBJECTS:.o=.d)

#--------------------------------------------------------
# app rules
#--------------------------------------------------------
all: win
win: $(BIN_DIR)$(TARGET).exe

#--------------------------------------------------------
# cleaning rule
#--------------------------------------------------------
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)$(TARGET).exe

#--------------------------------------------------------
# objects and target rules
#--------------------------------------------------------

$(BIN_DIR)$(TARGET).exe: $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CFLAGS) $(LFLAGS)

-include $(DEPS32)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CXX) -c $(CFLAGS) $(INCLUDE) $< -o $@
