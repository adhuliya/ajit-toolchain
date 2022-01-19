#!/bin/sh

# run AJIT C Model on the generated mmap file
_MAIN="main";
ajit_C_system_model \
  -n {{confObj.coreCount}} \
  -t {{confObj.threadsPerCoreCount}} \
  -i {{hex(confObj.ramStartAddr)}} \
% if confObj.debugBuild:
  -g \
% for i in range(len(confObj.programs)):
  -p {{confObj.startingDebugPort+i}} \
% end
% end
  -m ${_MAIN}.mmap.remapped \
  -w ${_MAIN}.wtrace \
  -d \
  -r {{confObj.resultsFile}} \
  -l ${_MAIN}.log;
