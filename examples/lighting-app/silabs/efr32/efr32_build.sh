#!/bin/bash

source third_party/connectedhomeip/scripts/activate.sh
# export silabs_board=BRD4186C
# export silabs_board=BRD4187C
# export silabs_board=BRD4187A
export silabs_board=BRD4187B
# export silabs_board=BRD4187C_40M
gn gen out/debug
ninja -C out/debug
DATE=$(date +%Y%m%d)

cp out/debug/chip-efr32-lighting-example.s37 /mnt/c/3_work/2_docments/3_CHIP/chip_firmware/chip-efr32-lighting-example_${silabs_board}_${DATE}.s37