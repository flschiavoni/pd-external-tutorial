pdfname = pd-external-slides.pdf
tmp_extensions = log bbl aux dvi backup blg toc bak out acn acr alg glg glo  \
                 gls ist xdy nav snm

all: $(pdfname)

$(pdfname): $(subst .pdf,.tex,$(pdfname)) *.tex
	pdflatex -halt-on-error -jobname $(@:.pdf=) $^
#	bibtex `basename $@ .pdf`
#	pdflatex -halt-on-error -jobname $(@:.pdf=) $^
#	pdflatex -halt-on-error -jobname $(@:.pdf=) $^

clean:
	for ext in $(tmp_extensions); do rm -f *.$${ext}; done


wipe: clean
	rm -rf $(pdfname)

edit:
	vim -p *.tex makefile *.bib

check: *.tex
	for i in $^; do aspell check -t $$i; done

view: $(pdfname)
#	xdvi -margins 5cm -watchfile 1 -s 6 $(target)
	xpdf -remote $(pdfname) $<

loop: *.tex
	md5=`md5sum $^`;                             \
        while [ 1 ]; do                              \
          if [ "$$md5" != "`md5sum $^`" ]; then      \
            make;                                    \
            status=$$?;                              \
            while [ "$$status" != "0" ]; do          \
              echo "******************************"; \
              echo "* PROBLEMAS NO PROCESSAMENTO *"; \
              echo "******************************"; \
              echo -n "Tentando novamente em 5s.";   \
              sleep 5;                               \
              make;                                  \
              status=$$?;                            \
            done;                                    \
            md5=`md5sum $^`;                         \
            xpdf -remote $(pdfname) -reload;          \
          fi;                                        \
        sleep 1;                                     \
        done

.PHONY: clean edit view loop check
