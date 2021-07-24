#ifndef AJIT_CORTOS_H
#define AJIT_CORTOS_H

int ajit_lock_acquire_buzy(int index);
int ajit_lock_acquire(int index);
void ajit_lock_release(int index);


typedef union _AjitMessage32Bytes {
  char arr[32];

  struct {
    int code_a;
    char arr_a[28];
  };

  struct {
    int code_b;
    double d1;
    double d2;
  };

  struct {
    int code_c;
    union _AjitMessage32Bytes *ptr;
  };

  struct {
    int code_d;
    int val[7];
  };

  struct { // for Ajit's Queue Header
    int syncLock;
    int totalMsgs;
    int readIndex;
    int writeIndex;
  };

} AjitMessage;


/*
Sends an AjitMessage.
  - Returns zero if the queue is full.
  - Returns non-zero if the msg was added.
*/
int writeAjitMessage(int queueId, AjitMessage *msg);

/*
Gets an AjitMessage.
  - Returns zero if the queue is empty.
  - Returns non-zero if the msg was put into the *msg location.
*/
int readAjitMessage(int queueId, AjitMessage *msg);


#endif