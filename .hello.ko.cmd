cmd_/usr/local/yourapp/modul/hello.ko := ld -r -m elf_i386 -T ./scripts/module-common.lds --build-id  -o /usr/local/yourapp/modul/hello.ko /usr/local/yourapp/modul/hello.o /usr/local/yourapp/modul/hello.mod.o ;  true
