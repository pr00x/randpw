CC=gcc
CFLAGS=-Wall -O2 -Wno-unused-function
SRC=randpw.c
EXEC=randpw
INSTALL_DIR=/usr/bin

all: $(EXEC)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	@echo "Cleaning up..."
	rm -f $(EXEC)
	@echo "Clean complete."

install: $(EXEC)
	@echo "Installing executable..."
	cp $(EXEC) $(INSTALL_DIR)
	@echo "Installation complete."

uninstall:
	@echo "Uninstalling executable..."
	rm -f $(INSTALL_DIR)/$(EXEC)
	@echo "Uninstallation complete."