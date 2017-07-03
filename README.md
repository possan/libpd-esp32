# pure-data on ESP32

Note; this is a very experimental hack/build of libpd for ESP32, it's out of tune, but it builds and runs! not tested on anything other than a NodeMCU ESP32

`components/libpd/libpd` contains a [clone of libpd including submodules](https://github.com/libpd/libpd)
`components/*spiffs*` contains [SPIFFS VFS code](https://github.com/loboris/ESP32_spiffs_example)

# Build it

I'm using the dockerized compiler, start it:

    export PATH_TO_ESP_IDF="<path to your esp-idf folder>"
    export PATH_TO_YOUR_PROJECT=`pwd`
    docker run --rm -it -v ${PATH_TO_ESP_IDF}:/esp/esp-idf -v ${PATH_TO_YOUR_PROJECT}:/esp/project bschwind/esp-32-build /bin/bash

Then inside the container, run:

    make menuconfig
    make

When updating the [contents of the filesystem](components/spiffs_image/image) you need to rebuild the image.

    mkspiffs -c components/spiffs_image/image -b 8192 -p 256 -s 1048576 build/spiffs_image.img


# Flash it

I'm flashing it outside of the docker container.

    # Flash the boot loader and partition table
    esptool.py --chip esp32 --port /dev/tty.SLAB_USBtoUART --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000 build/bootloader/bootloader.bin  0x8000 build/partitions_example.bin

    # flash spiffs image
    esptool.py --chip esp32 --port /dev/tty.SLAB_USBtoUART --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x180000 build/spiffs_image.img

    # flash main application
    esptool.py --chip esp32 --port /dev/tty.SLAB_USBtoUART --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect  0x10000 build/libpdtest.bin


