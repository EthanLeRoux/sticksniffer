#include <stdio.h>
#include <libusb-1.0/libusb.h>

int main(void)  {
    libusb_context *ctx = NULL;
    libusb_device **device_list = NULL;

    int result = libusb_init(&ctx);
    if(result < 0) {
        fprintf(stderr, "Failed to init libusb: %s\n", libusb_error_name(result));
        return 1;
    }

    ssize_t count = libusb_get_device_list(ctx,&device_list);
    if(count < 0) {
        fprintf(stderr, "Failed to get device list: %s\n", libusb_error_name((int) count) );
    }

    printf("libusb initialized successfully!\n");

    printf("Found %zd devices(s)\n",  count );

    for (ssize_t i= 0; i< count; i++) {
        libusb_device *dev = device_list[i];

        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "Failed to get descriptor for device %zd:  %s\n",
                i, libusb_error_name(r));
            continue;
        }

        printf("Device %zd: VID:PID = %04x:%04x\n", i, desc.idVendor, desc.idProduct);
    }

    libusb_free_device_list(device_list, 1);
    libusb_exit(ctx);
    return 0;
}