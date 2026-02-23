# zyrthi-hal/Makefile
# 纯接口层：仅生成空静态库（占位，无实现）
AR ?= ar
ARFLAGS ?= rcs
BUILD_DIR ?= build
TARGET = $(BUILD_DIR)/libzyrthi-hal.a

# 默认目标：创建空库
all: mkdir_build $(TARGET)

# 创建 build 目录
mkdir_build:
	@mkdir -p $(BUILD_DIR)

# 生成空静态库（兼容 Core 层依赖，无任何代码）
$(TARGET):
	$(AR) $(ARFLAGS) $@ /dev/null

# 清理
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean mkdir_build