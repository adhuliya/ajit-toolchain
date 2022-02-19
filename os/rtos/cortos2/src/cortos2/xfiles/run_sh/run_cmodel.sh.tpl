#!/bin/sh

# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -n {{confObj.hardware.cpu.coreCount}} \
  -t {{confObj.hardware.cpu.threadsPerCoreCount}} \
% if confObj.software.build.debug:
  -g \
% for i in range(len(confObj.software.programs)):
  -p {{confObj.software.build.firstDebugPort+i}} \
% end
% end
  -i {{hex(confObj.hardware.memory.ram.physicalStartAddr)}} \
  -m ${_MAIN}.mmap.remapped \
  -w ${_MAIN}.wtrace \
  -d \
  -r {{confObj.software.projectFiles.resultsFile}} \
  -l ${_MAIN}.log \
;
