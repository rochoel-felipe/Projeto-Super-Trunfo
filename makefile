main: main.o
	@echo "Gerando arquivo executável"
	gcc *.o -o main
main.o: main.c
	@echo "Compilando e gerando os objetos"
	gcc -c *.c
clean:
	@echo "Apagando objetos e executáveis antigos..."
	rm -f *.o main
run:
	./main
