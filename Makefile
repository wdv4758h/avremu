export TEXINPUTS := $(shell pwd)//:${TEXINPUTS}

source/avremu.pdf:
	cd source; latexmk -pdf -shell-escape avremu

test: test-simple
	cd source/test-suite; ./test-suite

test-simple: source/simple-testsuite.tex
	pdflatex -halt-on-error $<

test-%: source/test-suite/%.c
	cd source/test-suite; ./test-suite single $(shell basename $<)

avremu.zip: source/avremu.pdf
	rm -rf avremu avremu.zip
	mkdir avremu
	# TeX Directory
	mkdir -p  avremu/tex/latex/avremu
	cp tex/latex/avremu/*.tex avremu/tex/latex/avremu
	cp tex/latex/avremu/*.sty avremu/tex/latex/avremu
	# Source directory
	mkdir -p avremu/source/latex/avremu
	cp -r imgs avremu/source/latex/avremu
	mkdir -p avremu/source/latex/avremu/test-suite
	cp source/test-suite/*.c avremu/source/latex/avremu/test-suite
	cp  source/simple-testsuite.tex avremu/source/latex/avremu/
	# Documenation directory
	mkdir -p avremu/doc/latex/avremu
	cp source/avremu.pdf avremu/doc/latex/avremu
	zip -r avremu.zip avremu
	rm -rf avremu


.PHONY: test-simple source/avremu.pdf avremu.zip
