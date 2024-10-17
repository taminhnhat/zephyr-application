

# File Shortcut
## Application
[root dir](../applications/)  
[overlay](../applications/boards/stm32f4_disco.overlay)  

### Build
[root dir](../applications/build/)  
[dts](../applications/build/zephyr/zephyr.dts)  
[.config](../applications/build/zephyr/.config)  
[autoconf.h](../applications/build/zephyr/include/generated/zephyr/autoconf.h)  

## Zephyr
[root dir](../zephyr/)  
### gpio driver
[gpio CMakeLists.txt](../zephyr/drivers/gpio/CMakeLists.txt)  
[gpio_stm32.c](../zephyr/drivers/gpio/gpio_stm32.c)  |  [gpio_stm32.h](../zephyr/drivers/gpio/gpio_stm32.h)  
[gpio_stm32_mydisco.c](../zephyr/drivers/gpio/gpio_stm32_mydisco.c)  |  [gpio_stm32_mydisco.h](../zephyr/drivers/gpio/gpio_stm32_mydisco.h)  
[gpio Kconfig](../zephyr/drivers/gpio/Kconfig)  |  [gpio Kconfig.stm32](../zephyr/drivers/gpio/Kconfig.stm32)  |  [gpio Kconfig.stm32_mydisco](../zephyr/drivers/gpio/Kconfig.stm32_mydisco)  
[st,stm32-gpio.yaml](../zephyr/dts/bindings/gpio/st,stm32-gpio.yaml)  |  [st,stm32-gpio-mydisco.yaml](../zephyr/dts/bindings/gpio/st,stm32-mydisco-gpio.yaml)  
### pin control driver
[pinctrl CMakeLists.txt](../zephyr/drivers/pinctrl/CMakeLists.txt)  
[pinctrl_stm32.c](../zephyr/drivers/pinctrl/pinctrl_stm32.c)  
[pinctrl_stm32_mydisco.c](../zephyr/drivers/pinctrl/pinctrl_stm32_mydisco.c)  
[pinctrl Kconfig](../zephyr/drivers/pinctrl/Kconfig)  |  [pinctrl Kconfig.stm32](../zephyr/drivers/pinctrl/Kconfig.stm32)  |  [pinctrl Kconfig.stm32_mydisco](../zephyr/drivers/pinctrl/Kconfig.stm32_mydisco)  
[st,stm32-pinctrl.yaml](../zephyr/dts/bindings/pinctrl/st,stm32-pinctrl.yaml)  |  [st,stm32-pinctrl-mydisco.yaml](../zephyr/dts/bindings/pinctrl/st,stm32-pinctrl-mydisco.yaml)  

# REFERENCE
[zephyr device driver model](https://docs.zephyrproject.org/latest/kernel/drivers/index.html)  
[zephyr build system (CMake)](https://docs.zephyrproject.org/latest/build/cmake/index.html)  
