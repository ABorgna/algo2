
.PHONY: tmp tar

all: tar tmp clean

tar: entregable.tar.gz

tmp: clean
	# Copiar todo a tmp
	mkdir tmp
	#find src \( -name '*.h' -o -name '*.cpp' \) -exec \
	#    cp {} tmp/ \;
	cp src/modulos/*.{cpp,h} tmp/
	cp src/aed2/*.{cpp,h} tmp/
	cp src/Driver.{cpp,h} tmp/
	cp src/aed2.h tmp/
	cp src/Tipos.h tmp/
	# Flatten los #includes
	find tmp \( -name '*.h' -o -name '*.cpp' \) -exec \
	    sed -i 's/#include *"[^"]*\/\([^\/]*\)"/#include "\1"/' {} \;

entregable.tar.gz: tmp
	tar -czf entregable.tar.gz tmp

clean:
	rm -rf tmp
	rm -f entregable.tar.gz

