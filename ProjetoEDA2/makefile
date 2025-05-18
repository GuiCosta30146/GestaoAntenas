# Alvo principal: cria o executável "antenas"
# Usa os ficheiros objeto e as bibliotecas estáticas
antenas: principal.o efeitonefasto.o ficheiros.o grafos.o listas.o libefeito.a libficheiros.a libgrafos.a liblistas.a
	gcc -o antenas principal.o libefeito.a libficheiros.a libgrafos.a liblistas.a

# Compila o módulo efeitoinefasto
efeitoinefasto.o: efeitonefasto.c efeitonefasto.h estruturas.h
	gcc -c efeitonefasto.c

# Compila o módulo ficheiros
ficheiros.o: ficheiros.c ficheiros.h estruturas.h
	gcc -c ficheiros.c

# Compila o módulo grafos
grafos.o: grafos.c grafos.h estruturas.h
	gcc -c grafos.c

# Compila o módulo listas
listas.o: listas.c listas.h estruturas.h
	gcc -c listas.c

# Compila o ficheiro principal do programa (pode ser o teu main)
principal.o: principal.c grafos.h estruturas.h
	gcc -c principal.c

# Cria a biblioteca estática do módulo efeitoinefasto
libefeito.a: efeitonefasto.o
	ar rcs libefeito.a efeitonefasto.o

# Cria a biblioteca estática do módulo ficheiros
libficheiros.a: ficheiros.o
	ar rcs libficheiros.a ficheiros.o

# Cria a biblioteca estática do módulo grafos
libgrafos.a: grafos.o
	ar rcs libgrafos.a grafos.o

# Cria a biblioteca estática do módulo listas
liblistas.a: listas.o
	ar rcs liblistas.a listas.o

# Limpa os ficheiros objeto, bibliotecas e o executável
clean:
	rm -f *.o *.a antenas
