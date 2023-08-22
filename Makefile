# Compiler and compiler flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude

# Directories
SRCDIR := src
INCDIR := include
BUILDDIR := build

# Determine the operating system
ifeq ($(OS),Windows_NT)
	RM := del /Q
	MKDIR := mkdir
	TARGET := file_manager.exe
else
	RM := rm -f
	MKDIR := mkdir -p
	TARGET := file_manager
endif

# Precompiled header
PCH := $(INCDIR)/pch.h
PCH_FLAGS := -include $(PCH)

# Source, header, and object files
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Main target (executable)
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(PCH_FLAGS) -o $@ $(OBJECTS)

# Build object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(PCH_FLAGS) -I$(INCDIR) -c $< -o $@

# Create build directory
$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

clean:
	$(RM) $(subst /,\,$(OBJECTS)) $(subst /,\,$(TARGET))
	$(RM) -r $(BUILDDIR)