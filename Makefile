CC := g++
BUILD_DIR := build
TARGET := $(BUILD_DIR)/raytracer
TEST_OUT := $(BUILD_DIR)/out.ppm

$(TARGET): raytracer.cpp $(BUILD_DIR)
	$(CC) $< -o $@

$(BUILD_DIR):
	mkdir -p $@

test:
	$(TARGET) > $(TEST_OUT)

clean:
	rm $(BUILD_DIR)/*
	rmdir $(BUILD_DIR)
