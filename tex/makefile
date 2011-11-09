pdfname = pd-external-tutorial.pdf

all: $(pdfname)

$(pdfname): $(subst .pdf,.tex,$(pdfname))
	pdflatex -halt-on-error -jobname $(@:.pdf=) $^
#	bibtex `basename $@ .pdf`
#	makeglossaries `basename $@ .pdf`
	pdflatex -halt-on-error -jobname $(@:.pdf=) $^
#	pdflatex -halt-on-error -jobname $(@:.pdf=) $^

clean:
	rm -rf *.{log,bbl,aux,dvi,backup,blg,toc,bak,out,acn,acr,alg,glg,glo,gls,ist,xdy}


wipe: clean
	rm -rf $(pdfname)

edit:
	vim -p *.tex makefile

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
