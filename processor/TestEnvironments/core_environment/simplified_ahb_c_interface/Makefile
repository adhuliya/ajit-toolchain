TOPMODULES=-t get_simplified_ahb_command -t send_simplified_ahb_response
VHDLLIB=simplified_ahb_c_interface_
AA2CPREFIX=$(VHDLLIB)_
AA2C_C_FILE=$(AA2CPREFIX)aa_c_model.c
AA2CFILES=simplified_ahb_c_interface.aa
AA2VHDLFILES=  -A  simplified_ahb_c_interface.aa

all:aa2c/simplified_ahb_c_interface_aa_c_model.c
          
aa2c/simplified_ahb_c_interface_aa_c_model.c: $(AA2CFILES)
	buildFromSources.py  $(SIMULATOR) $(DEBUG) $(GNUPTH) -U -a simplified_ahb_c_interface -W $(VHDLLIB) -E to_vhdl $(TOPMODULES) $(AA2VHDLFILES)


clean:
	rm -rf vhdl/* aa2c/* *.c *.h *.txt .Aa .vC

PHONY: clean
