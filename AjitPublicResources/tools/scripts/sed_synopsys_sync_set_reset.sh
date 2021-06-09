#!/bin/bash
sed  s/"--##decl_synopsys_attribute_lib##"/"library synopsys; use synopsys.attributes.all;"/ < $1 | sed s/"--##decl_synopsys_sync_set_reset##"/"attribute sync_set_reset of reset: signal is \"true\";"/ > $2
