#
# AJIT ISA Document - 01
#
### Directory Structure
TOP=$(shell pwd)
SRCDIR=$(TOP)/src
BLDDIR=$(TOP)/build
OUTDIR=$(TOP)/output
IMGDIR=$(TOP)/figures
FIGDIR=$(IMGDIR)
EPSDIR=$(IMGDIR)
IMGOUTDIR=$(IMGDIR)
RELSRCDIR=.
RELEPSDIR=.

### Commands and options (if any)
#LATEX=pdflatex
TODAY=$(shell date +%d-%m-%Y-%H-%M-%S)
DVIPS=dvips
LATEX=latex
DVIPDF=dvipdf
PS2PDF=ps2pdf
BIBTEX=bibtex
LATEXOPTS=-interaction=batchmode -output-directory=$(BLDDIR)

# Our document!
ISANAME=isa
ISABIBFILE= # $(SRCDIR)/references/reviews.bib
ISASOURCES=$(SRCDIR)/$(ISANAME).tex          \
	     $(ISABIBFILE)

ISARELBIBFILE=$ $(RELSRCDIR)/refs.bib
ISARELSOURCES=$(RELSRCDIR)/$(ISANAME).tex    \
	        $(ISARELBIBFILE)
ISARELMAKEFILE=Makefile

ISAMAINTEX=$(BLDDIR)/$(ISANAME).tex

ISADVIOUT=$(ISANAME).dvi
ISAPSOUT=$(ISANAME).ps
ISAPDFOUT=$(ISANAME).pdf

ISAAUX=$(ISANAME).aux
ISATOC=$(ISANAME).toc
ISALOG=$(ISANAME).log
ISAFIG=$(ISANAME).lof
ISATAB=$(ISANAME).lot
ISATGZ=$(ISANAME)-$(TODAY).tgz

ALLTGZ=arxivsrc-$(TODAY).tgz

# Targets
default: all

all: cls

cls: arxiv
	@echo "Done."

tarall: arxivtar

# ISA Target
arxiv: outdirexist $(ISAPDFOUT)
	@echo -n "-> Moving `basename $(ISAPDFOUT)`"   && \
	echo -n " to `basename $(OUTDIR)`/ ... "       && \
	cd $(BLDDIR)                                   && \
	mv -f $(ISAPDFOUT) $(OUTDIR)                   && \
	cd $(TOP)

$(ISAPDFOUT): $(ISAPSOUT)
	@echo -n "-> Generating PDF from `basename $(ISAPSOUT)`  ... "  && \
	cd $(BLDDIR)                                                    && \
	$(PS2PDF) $(ISAPSOUT) $(ISAPDFOUT) > /dev/null 2>&1             && \
	/bin/rm $(ISAPSOUT)                                             && \
	cd $(TOP)                                                       && \
	echo "Done."

$(ISAPSOUT): $(ISADVIOUT)
	@echo -n "-> Generating PS  from `basename $(ISADVIOUT)` ... "  && \
	cd $(BLDDIR)                                                    && \
	$(DVIPS) -q $(ISADVIOUT) -o $(ISAPSOUT)                         && \
	cd $(TOP)                                                       && \
	echo "Done."

$(ISADVIOUT): blddirexist $(ISASOURCES)
	@echo -n "-> Generating DVI from `basename $(ISAMAINTEX)` ... "  && \
	cp $(ISASOURCES) $(BLDDIR)                                       && \
	cd $(BLDDIR)                                                     && \
	$(LATEX)  $(LATEXOPTS) $(ISAMAINTEX) > /dev/null                 && \
	$(LATEX)  $(LATEXOPTS) $(ISAMAINTEX) > /dev/null                 && \
	$(LATEX)  $(LATEXOPTS) $(ISAMAINTEX) > /dev/null                 && \
	cd $(TOP)                                                        && \
	echo "Done."                                                     || \
	(less $(BLDDIR)/$(ISANAME).log                                   && \
	echo -e "\n** Log file: $(BLDDIR)/$(ISANAME).log"                && \
	/bin/false)

blddirexist: 
	@printf "Checking for BUILD  directory ... "     && \
	[ ! -d $(BLDDIR) ]                               && \
	mkdir $(BLDDIR)                                  && \
	printf "created.\n"                              || \
	(printf "exists.\n" && /bin/true)

outdirexist: 
	@printf "Checking for OUTPUT directory ... "     && \
	[ ! -d $(OUTDIR) ]                               && \
	mkdir $(OUTDIR)                                  && \
	printf "created.\n"                              || \
	(printf "exists.\n" && /bin/true)

# Tarball targets
alltar: arxivtar
	@echo "Done."

arxivtar:
	@tar zcvf $(ISATGZ)         \
	          $(ISARELMAKEFILE) \
                  $(ISARELSOURCES)  \
                  $(RELEPSDIR)/*.eps

# Maintenance targets

clean: arxivclean texclean
	rmdir $(BLDDIR)

texclean: arxivtexclean

# ISA clean
arxivclean: arxivtexclean
	/bin/rm -f                \
	   $(OUTDIR)/$(ISAPDFOUT) \
	   $(OUTDIR)/$(ISAPSOUT)  

arxivtexclean:
	/bin/rm -f                \
	   $(BLDDIR)/$(ISADVIOUT) \
	   $(BLDDIR)/$(ISAAUX)    \
	   $(BLDDIR)/$(ISALOG)    \
	   $(BLDDIR)/$(ISATOC)    \
	   $(BLDDIR)/$(ISAFIG)    \
	   $(BLDDIR)/$(ISATAB)    \
	   $(BLDDIR)/*.tex        \
	   $(BLDDIR)/*.eps        \
	   $(BLDDIR)/$(ISANAME).* \
	   $(BLDDIR)/*.bib        \
	   $(BLDDIR)/*~

help:
	@echo
	@echo "Usage: make {clean|texclean|help}"
	@echo "   No arguments:    Build the PDF version of the paper"
	@echo "   clean:           Remove everything that we generate"
	@echo "   texclean:        Remove everything that TeX generates"
	@echo "   help:            This help"
	@echo
