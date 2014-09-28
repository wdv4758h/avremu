test:
	pdflatex -halt-on-error avr.tex
	cd tests; ./test-suite
