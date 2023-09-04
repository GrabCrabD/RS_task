CMAKE_ROOT := .
BUILD_DIR := ../build
LIBS = -lgtest -lgtest_main -pthread
DCMAKE_BUILD_TYPE := Debug

SRC := $(shell find $(CMAKE_ROOT) -name "*.cpp")
HEADERS := $(shell find $(CMAKE_ROOT) -name "*.h")

all: build

build:
	cmake -S $(CMAKE_ROOT) -B $(BUILD_DIR) -DCMAKE_BUILD_TYPE=${DCMAKE_BUILD_TYPE}
	cmake --build $(BUILD_DIR)

lint:
	@clang-format --style=Google --Werror --dry-run $(SRC) $(HEADERS) && echo "Clagn-format passed"

fmt:
	@clang-format --style=Google --Werror -i $(SRC) $(HEADERS) && echo "Formatted"


clean:
	rm -rf $(BUILD_DIR)

.PHONY: lint fmt build test tests clean