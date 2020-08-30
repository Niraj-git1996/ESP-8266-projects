# INTRODUCTION TO  ESP8266 NODEMCU

**NodeMCU is an open source LUA based firmware developed for ESP8266 wifi chip. By exploring functionality with ESP8266 chip, NodeMCU firmware comes with ESP8266 Development board/kit i.e. NodeMCU Development board.**
![esp_image](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Development%20Boards/Node-MCU-Devkit-1-0.jpg)


## PIN DEFINITION
![pin_def](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Development%20Boards/NODEMCU_DEVKIT_V1_0_PINMAP.png)

### NODE MCU GPIO PIN

**General-purpose input/output (GPIO) is a pin on an IC (Integrated Circuit). It can be either input pin or output pin, whose behavior can be controlled at the run time. refer the image below.**

![gpio](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20ESPlorer%20IDE/NodeMCU%20GPIO/NodeMCU%20GPIOs.png)

### NODE MCU ADC PIN

**Analog to Digital Converter(ADC) is used to convert analog signal into digital form. ESP8266 has inbuilt 10-bit ADC with only one ADC channel i.e. it has only one ADC input pin to read analog voltage from external device/sensor.**
###### The ADC channel on ESP8266 is multiplexed with the battery voltage. Hence, we can set it to measure either on board supply voltage or external analog voltage. The input voltage range for ADC pin is 0–1.0V while reading external analog voltage.
![ADC_pin](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20ESPlorer%20IDE/NodeMCU%20ADC/NodeMCU_ADC_Pin.png)

### NODE MCU SPI(Serial programming interface)

###### NodeMCU based ESP8266 has Hardware SPI with four pins available for SPI communication. With this SPI interface, we can connect any SPI enabled device with NodeMCU and make communication possible with it.


###### ESP8266 has SPI pins (SD1, CMD, SD0, CLK) which are exclusively used for Quad-SPI communication with flash memory on ESP-12E, hence, they can’t be used for SPI applications. We can use Hardware SPI interface for user end applications.

**Below figure shows Quad SPI interface pins that are internally used for flash.**

![spi_img](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20SPI/NodeMCU_SPI_Pins.png)

### NODE MCU I2C (Inter-Integrated Circuit) Pins

###### SDA (serial data) wire is used for data exchange in between master and slave device. SCL (serial clock) is used for synchronous clock in between master and slave device.

###### NodeMCU has I2C functionality support on its GPIO pins. Due to internal functionality on ESP-12E we cannot use all its GPIOs for I2C functionality. So, do tests before using any GPIO for I2C applications.

below the image of arduino ide connection woth esp8266

![i2c_img](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20ESPlorer%20IDE/NodeMCU%20I2C/Arduino_NodeMCU_I2C_Interface.png)

 ### NODE MCU UART (Universal Asynchronous Receiver Transmitter)
 
 ###### NodeMCU based ESP8266 has two UART interfaces, UART0 and UART1. The ESP8266 data transfer speed via UART interfaces can reach 40 times of 115200 i.e. 4.5 Mbps. By default, UART0 baud rate is 115200 for the oscillator of 40MHz. It can be changed to user defined value accorto need of application.

![uart_pin](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20ESPlorer%20IDE/NodeMCU%20UART/NodeMCU_UART_Pins.png)

### PWM NODE MCU PIN

###### NodeMCU based ESP8266 has the functionality of PWM interfaces via software programming. It is achieved with the timer interruption method. PWM frequency range for ESP8266 is adjustable up to 1KHz.


![pwm_pin](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20PWM/NodeMCU_PWM_Pins.png)

## NODEMCU as HTTP client
###### HTTP client helps sending HTTP requests and receiving HTTP responses from HTTP server.
###### NodeMCU is an open source IoT platform. It is a firmware which runs on ESP8266 Wi-Fi SoC from Espressif Systems. It has on board wi-fi available through which IoT applications becomes easy to build.

![client_img](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Client/NodeMCU%20HTTP%20Client.png)


## NODEMCU as HTTP server

###### NodeMCU wi-fi has Access Point (AP) mode through which it can create Wireless LAN to which any wi-fi enabled device can connect as shown in below figure.

![server_img](https://www.electronicwings.com/public/images/user_images/images/NodeMCU/NodeMCU%20Basics%20using%20Arduino%20IDE/NodeMCU%20HTTP%20Server/NodeMCU_WiFi_AP_Mode.png)




