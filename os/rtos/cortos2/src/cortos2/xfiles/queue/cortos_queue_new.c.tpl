#include <cortos_queue.h>

CortosQueueHeader queueHeaders[{{len(queues)}}];

% for queue in queues:
#define {{queue.defineName}} {{queue.id}}
uint8_t cortos_queue_{{queue.id}}[{{queueLen}}][{{queueMsgSizeInBytes}}];
% end


void cortos_init_queues() {
  % for i, queue in enumerate(queues):
  // cortos queue {{i}}
  queueHeaders[i].totalMsgs      = 0;
  queueHeaders[i].readMsgIndex   = 0;
  queueHeaders[i].writeMsgIndex  = 0;
  queueHeaders[i].queuePtr       = cortos_queue_{{queue.id}};

  % end
}