export TEXINPUTS := $(shell pwd)//:${TEXINPUTS}

test: test-simple
	cd source/test-suite; ./test-suite

test-simple: source/simple-testsuite.tex
	pdflatex -halt-on-error $<

test-%: source/test-suite/%.c
	cd source/test-suite; ./test-suite single $(shell basename $<)

.PHONY: test-simple
