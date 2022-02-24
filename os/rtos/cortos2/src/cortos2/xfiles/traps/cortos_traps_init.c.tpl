
% for handler in confObj.software.traps.hw:
extern void (*{{handler.function}}) ();
% end

void cortos_init_hw_traps() {
  ajit_initialize_interrupt_handlers_to_null();

  % for handler in confObj.software.traps.hw:
  ajit_set_interrupt_handler({{handler.index}}, &({{handler.function}}));
  %end

  enableInterruptControllerAndAllInterrupts(0,0);
}

void cortos_init_sw_traps() {

}
