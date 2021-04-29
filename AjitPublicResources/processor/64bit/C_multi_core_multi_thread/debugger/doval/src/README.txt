Debugging support for Ajit Processor
--------------------------------------

Expanded versions of the short forms used :

SPI : Server to Processor Interface ( also mentioned as debug link )
GSB : GDB to Server Bridge ( also mentioned as RSP link )

Functions defined :
====================
1. send_spi_cmd : Send the data through server to processor interface

2. recv_spi_cmd : Receives the response from server to processor interface

3. gpb_init : Connect to a particular socket on the PC and initiate communication

4. gsb_receive : Receive one GDB to Server Bridge packet and decode it

5. gsb_compute_response : Compute the response for a given GDB to Server Bridge packet

6. gsb_send : Send the response packet back through the GDB to Server Bridge link




SPARC Register order information.  
========================================

  "g0", "g1", "g2", "g3", "g4", "g5", "g6", "g7",
  "o0", "o1", "o2", "o3", "o4", "o5", "sp", "o7",
  "l0", "l1", "l2", "l3", "l4", "l5", "l6", "l7",
  "i0", "i1", "i2", "i3", "i4", "i5", "fp", "i7",

  "f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7",
  "f8", "f9", "f10", "f11", "f12", "f13", "f14", "f15",
  "f16", "f17", "f18", "f19", "f20", "f21", "f22", "f23",
  "f24", "f25", "f26", "f27", "f28", "f29", "f30", "f31",

  "y", "psr", "wim", "tbr", "pc", "npc", "fsr", "csr"
