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
wget https://dl.espressif.com/dl/xtensa-lx106-elf-linux64-1.22.0-92-g8facf4c-5.2.0.tar.gz
tar -xvzf  xtensa-lx106-elf-linux64-1.22.0-92-g8facf4c-5.2.0.tar.gz

/usr/bin/python2 -m pip install --user -r ./ESP8266_RTOS_SDK/requirements.txt

