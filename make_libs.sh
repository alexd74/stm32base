#!/bin/sh

pushd Libraries/STM32F10x_StdPeriph_Driver/

make CHIP=STM32F10X_LD_VL
make cleanall
make CHIP=STM32F10X_CL
make cleanall

popd

pushd Libraries/STM32F4xx_StdPeriph_Driver/

make CHIP=STM32F429_439xx
make cleanall

make CHIP=STM32F429_439xx HARD_FLOAT=1
make cleanall

make CHIP=STM32F40_41xxx
make cleanall

make CHIP=STM32F40_41xxx HARD_FLOAT=1
make cleanall

popd
