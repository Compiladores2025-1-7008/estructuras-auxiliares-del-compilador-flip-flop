CXX = g++
CXXFLAGS = -std=c++17 -Wall -I./src -I./external/googletest/googletest/include
LDFLAGS = -pthread

SRC_DIR = src
TEST_DIR = test
BUILD_DIR = build

# Dile a make dónde buscar los archivos fuente
VPATH = $(SRC_DIR):$(TEST_DIR)

# Encuentra todos los archivos .cpp en ambos directorios
# notdir para obtener solo el nombre del archivo, no la ruta
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cpp))
TEST_SRCS = $(notdir $(wildcard $(TEST_DIR)/*.cpp))

# Convierte los nombres de archivo .cpp a .o y ponlos en el directorio de build
OBJS = $(addprefix $(BUILD_DIR)/, $(SRCS:.cpp=.o))
TEST_OBJS = $(addprefix $(BUILD_DIR)/, $(TEST_SRCS:.cpp=.o))

GTEST_LIB = external/googletest/build/lib/libgtest_main.a external/googletest/build/lib/libgtest.a

TARGET_TEST = runTests

.PHONY: all test clean gtest distclean

all: test

# -------------------------
# Build GoogleTest
# -------------------------
gtest:
	@if [ ! -d "external/googletest" ]; then \
		echo "Clonando GoogleTest..."; \
		mkdir -p external; \
		cd external; \
		git clone https://github.com/google/googletest.git; \
	fi
	@mkdir -p external/googletest/build
	@cd external/googletest/build && cmake .. && make

# -------------------------
# Build and Run Tests
# -------------------------
test: $(TARGET_TEST)
	./$(TARGET_TEST)

$(TARGET_TEST): gtest $(OBJS) $(TEST_OBJS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJS) $(TEST_OBJS) $(GTEST_LIB)

# --- Regla de compilación ÚNICA ---
# VPATH se encargará de encontrar el .cpp en src/ o test/
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------------------------
# Clean
# -------------------------
clean:
	rm -rf $(BUILD_DIR) $(TARGET_TEST)

# Un clean más agresivo que también borra gtest
distclean: clean
	rm -rf external/googletest
