

# File Shortcut
### Application
[root dir](../applications/)  
[overlay](../applications/boards/stm32f4_disco.overlay)  

### Build
[root dir](../applications/build/)  
[dts](../applications/build/zephyr/zephyr.dts)  
[.config](../applications/build/zephyr/.config)  
[autoconf.h](../applications/build/zephyr/include/generated/zephyr/autoconf.h)  

### Zephyr
[root dir](../zephyr/)  
[gpio CMakeLists.txt](../zephyr/drivers/gpio/CMakeLists.txt)  
[gpio_stm32_mydisco.c](../zephyr/drivers/gpio/gpio_stm32_mydisco.c)  |  [gpio_stm32_mydisco.h](../zephyr/drivers/gpio/gpio_stm32_mydisco.h)  
[gpio Kconfig](../zephyr/drivers/gpio/Kconfig)  |  [gpio Kconfig.stm32](../zephyr/drivers/gpio/Kconfig.stm32)  |  [gpio Kconfig.stm32_mydisco](../zephyr/drivers/gpio/Kconfig.stm32_mydisco)  
[st,stm32-gpio.yaml](../zephyr/dts/bindings/gpio/st,stm32-gpio.yaml)  |  [st,stm32-mydisco-gpio.yaml](../zephyr/dts/bindings/gpio/st,stm32-mydisco-gpio.yaml)  

# REFERENCE
[zephyr device driver model](https://docs.zephyrproject.org/latest/kernel/drivers/index.html)  
[zephyr build system (CMake)](https://docs.zephyrproject.org/latest/build/cmake/index.html)  
