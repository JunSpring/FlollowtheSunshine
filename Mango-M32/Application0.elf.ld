
/*
!!! Primary linker script file generated automatically !!!
This file contains the input and output files names
It also includes the secondary/main linker script that is specified in the Ride options (default or custom)
*/

SEARCH_DIR(".")
SEARCH_DIR("C:\ride_project\FlollowtheSunshine\Mango-M32\obj")
SEARCH_DIR("C:\Program Files (x86)\Raisonance\Ride\Lib\ARM")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\delay.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\main.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_it.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\system_stm32f10x.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\startup_stm32f10x_md.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\misc.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_flash.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_tim.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_gpio.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_usart.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_adc.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\stm32f10x_rcc.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\usart3.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\motor_control.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\soil_moisture_sensor.o")
INPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\obj\cds_sensor.o")
EXTERN( __io_putchar )
EXTERN( _write )
GROUP(
"STM32x_io_putchar_thumb.a"
"std_sbrk_thumb.lib"
"smallprintf_thumb.a"
"libc.a"
"libm.a"

)
INCLUDE "C:\ride_project\FlollowtheSunshine\Mango-M32\obj\STM32F103_128K_20K_FLASH.ld"
OUTPUT("C:\ride_project\FlollowtheSunshine\Mango-M32\Application0.elf")
