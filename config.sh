# sudo apt install make libncurses5-dev libncursesw5-dev flex bison gperf

COURSE_FOLDER=$(pwd)


echo $COURSE_FOLDER
export -p IDF_PATH=$COURSE_FOLDER/ESP8266_RTOS_SDK
echo $IDF_PATH

export -p CONFIG_PYTHON="python3"
export -p CONFIG_MAKE_WARN_UNDEFINED_VARIABLES=y
export -p PATH="$PATH:$IDF_PATH/bin:$COURSE_FOLDER/xtensa-lx106-elf/bin"
