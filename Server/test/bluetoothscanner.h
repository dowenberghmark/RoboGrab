#ifndef BLUETOOTHSCANNER_H
#define BLUETOOTHSCANNER_H

class BluetoothScanner
{
 public:
  BluetoothScanner(void);
  virtual ~BluetoothScanner(void);
 private:
  void scan();
  inquiry_info *ii = NULL;
  int max_rsp, num_rsp;
  int dev_id, sock, len, flags;
  int i;
  char addr[19] = { 0 };
  char name[248] = { 0 };
  
  
};


#endif // BLUETOOTHSCANNER_H
