V=1
SOURCE_DIR=./
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

# Nombre de tu juego de memes
all: mario64_chueco.z64

# Junta los archivos compilados en la ROM definitiva
mario64_chueco.z64: $(BUILD_DIR)/mario64_chueco.elf
	$(N64_BINDIR)/n64tool -l 2M -t "MARIO 64 CHUECO" -h $(N64_INST)/mips64-elf/lib/header -o $@ $<
	$(N64_BINDIR)/chksum64 $@

$(BUILD_DIR)/mario64_chueco.elf: $(BUILD_DIR)/main.o
	$(N64_BINDIR)/mips64-elf-gcc -o $@ $^ $(LDFLAGS) -lgl -lGLU -lpng -lm

clean:
	rm -rf $(BUILD_DIR) mario64_chueco.z64

.PHONY: all clean
