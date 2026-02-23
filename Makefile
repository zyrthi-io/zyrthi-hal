# 1. 创建临时空文件
EMPTY_SRC := empty.c
EMPTY_OBJ := empty.o

# 2. 生成空c文件（仅在不存在时创建）
$(EMPTY_SRC):
	@echo "int zyrthi_hal_empty(void) { return 0; }" > $(EMPTY_SRC)

# 3. 编译空目标文件
$(EMPTY_OBJ): $(EMPTY_SRC)
	$(CC) $(CFLAGS) -c $(EMPTY_SRC) -o $(EMPTY_OBJ)

# 4. 打包空静态库
libzyrthi-hal.a: $(EMPTY_OBJ)
	$(AR) rcs $@ $(EMPTY_OBJ)

# 5. 清理临时文件
clean:
	rm -f libzyrthi-hal.a $(EMPTY_OBJ) $(EMPTY_SRC)