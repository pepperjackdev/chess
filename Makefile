ifndef VERBOSE
.SILENT:
endif

# Default target
all: gui

# Generate build files
generate:
	cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build everything
build: generate
	cmake --build build

# Build only the GUI executable
gui: generate
	cmake --build build --target gui
	./build/gui

# Build only the perft executable
perft: generate
	cmake --build build --target perft
	./build/perft

# Clean
clean:
	cmake --build build --target clean

# Remove the build directory completely
distclean:
	rm -rf build