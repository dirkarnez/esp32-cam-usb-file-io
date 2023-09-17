#include <USBHost.h>
#include <USBHub.h>
#include <USBMSD.h>

USBHost usb;
USBHub hub1(&usb);
USBMSD usbmsd(&usb);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (usb.Init() == -1) {
    Serial.println("USB host initialization failed.");
    while (1);
  }
}

void loop() {
  usb.Task();

  if (usb.getUsbTaskState() == USB_TYPE_CONNECTED_MSD) {
    File file = SD.open("/usbdrive/test.txt", FILE_WRITE);
    if (file) {
      file.println("Hello, USB thumb drive!");
      file.close();
      Serial.println("Data written to file.");
    } else {
      Serial.println("Error opening file.");
    }

    usb.setUsbTaskState(USB_TYPE_NO_DEVICE_ATTACHED);
  }
}
