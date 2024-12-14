SOURCE=$(wildcard *.tex)

OS=`uname -s`

ifeq ($(OS),Linux)
OPEN=xdg-open
else
OPEN=open
endif

all: pdf, open

dvi:
	latex $(SOURCE)

pdf:
	pdflatex $(SOURCE)

open:
	$(OPEN) *.pdf

clean:
	-rm *.aux *.log
