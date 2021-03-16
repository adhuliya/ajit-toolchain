MAIN_FILE=Titto_thesis
SUB_FILES=TitlePage/TitlePage.tex Declaration/Declaration.tex Acknowledgement/Acknowledgement.tex Abstract/Abstract.tex Introduction/Introduction.tex Debug/Debug.tex SysArch/SysArch.tex Implementation/Implementation.tex Conclusion/Conclusion.tex AppendixI/AppendixI.tex AppendixII/AppendixII.tex AppendixIII/AppendixIII.tex
IMAGES=Figs/Aamodel/Aamodel.tex Figs/Aamodel/Aamodel.eps  Figs/appTEU/appTEU.eps Figs/Architecture/Architecture.eps Figs/Architecture/Architecture.tex Figs/Cmodel/Cmodel.tex Figs/Cmodel/Cmodel.eps Figs/DebugPacket/DebugPacket.tex Figs/DebugPacket/DebugPacket.eps Figs/FPGA/FPGA.eps Figs/FPGA/FPGA.tex Figs/GDBcommunicate/GDBcommunicate.tex Figs/GDBcommunicate/GDBcommunicate.eps Figs/RSPpacket/RSPpacket.tex Figs/RSPpacket/RSPpacket.eps Figs/Screenshot/screen.png Figs/SessionComm/SessionComm.tex Figs/SessionComm/SessionComm.eps
BIB_FILE=References/references.bib

all: build biber rebuild

build: $(MAIN_FILE).tex  $(SUB_FILES) $(IMAGES)
	pdflatex --shell-escape $(MAIN_FILE).tex
	
biber: $(BIB_FILE) $(MAIN_FILE).aux
	biber $(MAIN_FILE)
rebuild: $(MAIN_FILE).aux $(MAIN_FILE).bbl
	pdflatex --shell-escape $(MAIN_FILE)

clean:
	rm -rf TitlePage/*.aux Declaration/*.aux Acknowledgement/*.aux Abstract/*.aux Introduction/*.aux Debug/*.aux SysArch/*.aux Implementation/*.aux Conclusion/*.aux AppendixI/*.aux AppendixII/*.aux AppendixIII/*.aux Figs/Aamodel/*.pdf Figs/appTEU/*.pdf Figs/Architecture/*.pdf Figs/Cmodel/*.pdf Figs/DebugPacket/*.pdf Figs/FPGA/*.pdf Figs/GDBcommunicate/*.pdf Figs/RSPpacket/*.pdf Figs/SessionComm/*.pdf *.aux *.log *.xml *.toc *.out *.bbl *.bcf *.blg *.lof

PHONY: all clean
