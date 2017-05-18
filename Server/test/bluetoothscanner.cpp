#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/rfcomm.h>
#include <string.h>
#include "bluetoothscanner.h"


BluetoothScanner::BluetoothScanner(void){
  dev_id = hci_get_route(NULL);
  sock = hci_open_dev( dev_id );

  if (dev_id < 0 || sock < 0) {
    perror("opening socket");
    exit(1);
  }
  len = 8;
  max_rsp = 255;
  flags = IREQ_CACHE_FLUSH;
  this->scan();
}
BluetoothScanner::~BluetoothScanner(void){
  free( ii );
  close(sock);
}

void BluetoothScanner::scan(){
  ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
  num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
  if( num_rsp < 0 ) perror("hci_inquiry");
  for (i = 0; i < num_rsp; i++) {
    ba2str(&(ii+i)->bdaddr, addr);
    memset(name, 0, sizeof(name));
    if (hci_read_remote_name(sock, &(ii+i)->bdaddr, sizeof(name),
                             name, 0) < 0)
      strcpy(name, "[unknown]");
    printf("%s %s\n", addr, name);
  }
 
}
