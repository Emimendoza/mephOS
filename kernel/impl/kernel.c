#include <stddef.h>
#include <stdint.h>
#include <libfdt.h>



char *uart = (char *) 0x10000000;

void put_char(char c) {
	*uart = c;
}

void print(const char *str){
	while(*str != '\0'){
		put_char(*str);
		str++;
	}
}

_Noreturn void kmain(struct fdt_header *fdt){
	print("Hello world \n");
	int check_result = fdt_check_header(fdt);

	while(true){
		put_char(*uart);
	}
}