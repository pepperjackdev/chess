ifndef VERBOSE
.SILENT:
endif

# Runs the project
run: build
	./build/chess

# Builds the sources with build-system
build: generate
	cmake --build build

# Generates the build-system's scripts
generate:
	cmake -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Clean
clean:
	cmake --build build --target clean
