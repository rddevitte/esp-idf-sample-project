# ESP-IDF Sample Project

## Introduction

This is a relative simple and small project I've created to teach myself how to code, build and
flash an ESP32 project using the ESP-IDF tools directly, i.e., no IDE required, only a text editor
and the terminal.

Plus, the project shows

- how to structure the code onto components (&ldquo;componentize&rdquo;);
- how to make some project parameters configurable through `menuconfig`.

The project has two main components:

- the `output_pin_toggler`, used to blink an LED connected to pin 16 of the board;
- the `random_numbers_getter`, used to simulate the values of sensors.

Each component is used by two independent running tasks, `led_blinker_task` and
`fake_sensors_value_printer_task`.

## Assumptions

It is assumed:

- one is using any GNU/Linux operating system distribution;
- one has an ESP32 module laying around, for flashing and testing;
- one has already followed the [Espressif documentation on how to install the ESP-IDF toolchain on
  one's machine][1]; and
- the installation location is the default one, i.e. the `~/esp/esp-idf` directory.

[1]: https://docs.espressif.com/projects/esp-idf/en/stable/esp32/get-started/linux-macos-setup.html

## Steps

### Set up the environment

With this project cloned and the terminal open in the project's root directory, run

    source ~/esp/esp-idf/export.sh

### Set target board

To set a generic ESP32 as the target board, run

    idf.py set-target esp32

Please refer to the Espressif documentation in order to set a different board as the target.

### Configure 

To configure project-specific parameters, run

    idf.py menuconfig

Navigate through:

- *Project-specific configuration*;
    - *Blink GPIO number*: default is pin 16;
    - *Waiting period in ms*: default is 1000 milliseconds (= 1 second).

### Build

To build the project, run

    idf.py build

### Flash and monitor the serial output

Assuming the board has been already connected to any USB port of one's machine, and the device is
the `/dev/ttyUSB0`, run

    idf.py -p /dev/ttyUSB0 flash monitor

### Clean

To remove the artifacts produced by the build process, run

    rm -rf sdkconfig* build/

## Credits

Thanks to [this YouTube video by Low Level Learning][2] for inspiring me to create this project.

[2]: https://www.youtube.com/watch?v=dOVjb2wXI84

Also thanks to Espressif for providing project examples on ESP-32, which are located in
`~/esp/esp-idf/examples` directory.
