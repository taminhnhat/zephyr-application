

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
### accelerometer driver
[accel CMakeLists.txt](../zephyr/drivers/accel/CMakeLists.txt)  
[accel_stm32.c](../zephyr/drivers/accel/accel_stm32.c)  
[accel Kconfig](../zephyr/drivers/accel/Kconfig)  
[accel Kconfig.stm32](../zephyr/drivers/accel/Kconfig.stm32)  
[st,stm32-accel.yaml](../zephyr/dts/bindings/accelerometer/st,stm32-accel.yaml)  

# Patchs
[patch dir](./patchs) stores patch file of zephyr source code.  
## add_gpio_driver.patch - adding gpio driver for stm32f4_disco  
- New compatible is "st,stm32-gpio-mydisco" 
- Create zephyr/dts/bindings/gpio/st,stm32-gpio-mydisco.yaml  
- Create zephyr/drivers/gpio/Kconfig.stm32_mydisco  
- Create zephyr/drivers/gpio/gpio_stm32_mydisco.c
- Create zephyr/drivers/gpio/gpio_stm32_mydisco.h  
- Modify zephyr/drivers/gpio/CMakeLists.txt to source gpio_stm32_mydisco.c  
- Modify zephyr/drivers/gpio/Kconfig to source new Kconfig.stm32_mydisco  
- Modify zephyr/drivers/pinctrl/pinctrl_stm32.c to source gpio_stm32_mydisco.h
```
zephyr
├── arch
├── boards
│   └── st
├── cmake
├── doc
├── drivers
│   └── gpio
|   |   ├── CMakeLists.txt                          Modified
|   |   ├── Kconfig                                 Modified
|   |   ├── Kconfig.stm32_mydisco                   Created
|   |   ├── gpio_stm32_mydisco.c                    Created
|   |   └── gpio_stm32_mydisco.h                    Created
│   └── pinctrl
│       └── pinctrl_stm32.c                         Modified
├── dts
│   └── bindings
│       └── gpio
│           └── st,stm32-gpio-mydisco.yaml          Created
├── include
```
## add_pinctrl_driver.patch - adding pin control driver for stm32f4_disco 
- New compatible is "st,stm32-pinctrl-mydisco" 
- Create zephyr/dts/bindings/pinctrl/st,stm32-pinctrl-mydisco.yaml  
- Create zephyr/drivers/pinctrl/Kconfig.stm32_mydisco  
- Create zephyr/drivers/pinctrl/pinctrl_stm32_mydisco.c
- Modify zephyr/drivers/pinctrl/CMakeLists.txt to source pinctrl_stm32_mydisco.c  
- Modify zephyr/drivers/pinctrl/Kconfig to source new Kconfig.stm32_mydisco    
```
zephyr
├── arch
├── boards
│   └── st
├── cmake
├── doc
├── drivers
│   └── pinctrl
|       ├── CMakeLists.txt
|       ├── Kconfig
|       ├── Kconfig.stm32_mydisco
|       └── pinctrl_stm32_mydisco.c
├── dts
│   └── bindings
│       └── pinctrl
│           └── st,stm32-gpio-mydisco.yaml
├── include
```
## adding accelerometer driver for stm32f4_disco  
- Compatible is "st,stm32-accel" 
- Create zephyr/dts/bindings/accel/st,stm32-accel.yaml  
- Create zephyr/drivers/accel/Kconfig.stm32_mydisco  
- Create zephyr/drivers/accel/gpio_stm32_mydisco.c
- Create zephyr/drivers/accel/gpio_stm32_mydisco.h  
- Modify zephyr/drivers/accel/CMakeLists.txt to source gpio_stm32_mydisco.c  
- Modify zephyr/drivers/accel/Kconfig to source new Kconfig.stm32_mydisco  
# REFERENCE
[zephyr device driver model](https://docs.zephyrproject.org/latest/kernel/drivers/index.html)  
[zephyr build system (CMake)](https://docs.zephyrproject.org/latest/build/cmake/index.html)  
