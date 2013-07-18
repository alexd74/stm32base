#!/bin/sh

pushd Libraries/STM32F10x_StdPeriph_Driver/

make
make cleanall

popd

pushd Libraries/STM32F4xx_StdPeriph_Driver/

make
make cleanall

make HARD_FLOAT=1
make cleanall

popd
