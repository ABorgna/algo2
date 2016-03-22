targets = tp1.pdf

includes = tads/campo.tex tads/db.tex tads/registro.tex tads/renombres.tex \
	   tads/tabla.tex tads/valor.tex

libs = aed2-itef.sty aed2-symb.sty aed2-tad.sty aed2-tokenizer.sty caratula.sty

all: $(targets)

$(targets) : %.pdf : %.tex $(libs) $(includes)
	pdflatex $<
	pdflatex $<

./%.sty:
	@ln -s ../libs/$@ $@

clean:
	@rm $(libs) 2>/dev/null || true
	@rm $(targets) 2>/dev/null || true
	@rm ./*.aux 2>/dev/null || true
	@rm ./*.log 2>/dev/null || true
	@rm ./*.out 2>/dev/null || true
	@rm ./*.toc 2>/dev/null || true
