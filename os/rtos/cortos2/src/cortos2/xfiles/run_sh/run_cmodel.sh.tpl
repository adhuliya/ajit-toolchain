#!/bin/sh

% if confObj.software.build.debug:
echo "################################################################"
echo "#                  RUNNING DEBUG BUILD"
echo "################################################################"
sleep 1;
% end

# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -R 123456 \
  -n {{confObj.hardware.cpu.coreCount}} \
  -t {{confObj.hardware.cpu.threadsPerCoreCount}} \
% if confObj.software.build.debug:
  -g \
% for i in range(len(confObj.software.program.programThreads)):
  -p {{confObj.software.build.firstDebugPort+i}} \
% end
% end
  -i {{hex(confObj.hardware.memory.ram.physicalStartAddr)}} \
  -m ${_MAIN}.mmap.remapped \
% if not confObj.software.build.debug:
  -w ${_MAIN}.wtrace \
% if confObj.software.projectFiles.resultsFile:
  -r {{confObj.software.projectFiles.resultsFile}} \
  -l ${_MAIN}.log \
% end
% end
;
