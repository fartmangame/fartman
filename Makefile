# fartman makefile
# convenient shortcuts to common build operations

# detect number of cpu cores for parallel builds
NPROC := $(shell nproc 2>/dev/null || echo 4)

# build directory
BUILD_DIR := build

# default build type (Debug or Release)
BUILD_TYPE ?= Debug

.PHONY: all
all: build

.PHONY: build
build:
	@echo "building fartman ($(BUILD_TYPE))"
	@mkdir -p $(BUILD_DIR)
	@cmake -S . -G "Unix Makefiles" -B $(BUILD_DIR)
	@cmake -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=$(BUILD_TYPE) -DCMAKE_CXX_STANDARD=17
	@cmake --build $(BUILD_DIR) -j $(NPROC)
	@echo "build complete!"

.PHONY: release
release:
	@$(MAKE) BUILD_TYPE=Release build

.PHONY: debug
debug:
	@$(MAKE) BUILD_TYPE=Debug build

.PHONY: test
test: build
	@echo "running tests"
	@cd $(BUILD_DIR) && ctest --output-on-failure -j $(NPROC)

.PHONY: clean
clean:
	@echo "cleaning build directory"
	@rm -rf $(BUILD_DIR)
	@echo "clean complete!"

.PHONY: rebuild
rebuild: clean build

.PHONY: help
help:
	@echo "fartman build system"
	@echo ""
	@echo "available targets:"
	@echo "  all       - same as build (default)"
	@echo "  build     - build the project with default configuration (debug)"
	@echo "  debug     - build with debug configuration"
	@echo "  release   - build with release configuration"
	@echo "  test      - build and run tests"
	@echo "  clean     - remove all build artifacts"
	@echo "  rebuild   - clean and rebuild the project"
	@echo "  help      - show this help message"
	@echo ""
	@echo "environment variables:"
	@echo "  BUILD_TYPE - set build type (Debug or Release, default: Debug)"
	@echo "  NPROC      - number of parallel build jobs (default: auto-detected)"
