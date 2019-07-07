#for python 2
sudo apt install python-pip
pip2 install pyserial

sudo apt install make libncurses5-dev libncursesw5-dev flex bison gperf

#baixar e atualizar o SDK
git clone https://github.com/espressif/ESP8266_RTOS_SDK.git
cd ESP8266_RTOS_SDK
git checkout master
git pull
cd ..

#baixar a toolchain do xtensa
