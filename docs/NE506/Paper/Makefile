# Name of manuscript
manuscript = Cornille_NE506_Paper

# PdfLaTeX compilation options
latexopt = -halt-on-error -file-line-error -output-directory=build

#=================================================================
# Generate PDF of manuscript using PdfLaTeX
#=================================================================

all: timings.eps $(manuscript).pdf

timings.eps: timings.gpi timings.dat
	gnuplot timings.gpi

$(manuscript).pdf: $(manuscript).tex references.bib
	mkdir -p build
	pdflatex $(latexopt) $(manuscript)
	bibtex -terse build/$(manuscript)
	pdflatex $(latexopt) $(manuscript)
	pdflatex $(latexopt) $(manuscript)

#=================================================================
# Other
#=================================================================

clean:
	rm -fr build timings.eps

.PHONY: all clean
