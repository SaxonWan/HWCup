user_main_src  = ${wildcard $(TARGET_DIR)/user_main/*.c}
user_main_inc = -I ${wildcard $(TARGET_DIR)/user_main}
C_SOURCES += $(user_main_src)
C_INCLUDES += $(user_main_inc)

emw3080_src = ${wildcard $(TARGET_DIR)/Hardware/emw3080/*.c} 
emw3080_inc = -I ${wildcard $(TARGET_DIR)/Hardware/emw3080}
C_SOURCES += $(emw3080_src)
C_INCLUDES += $(emw3080_inc)

dobot_src = ${wildcard $(TARGET_DIR)/Hardware/dobot/*.c}
dobot_inc = -I ${wildcard $(TARGET_DIR)/Hardware/dobot}
C_SOURCES += $(dobot_src)
C_INCLUDES += $(dobot_inc)

RasPi_src = ${wildcard $(TARGET_DIR)/Hardware/uart_RasPi/*.c}
RasPi_inc = -I ${wildcard $(TARGET_DIR)/Hardware/uart_RasPi}
C_SOURCES += $(RasPi_src)
C_INCLUDES += $(RasPi_inc)

conveyor_src = ${wildcard $(TARGET_DIR)/Hardware/conveyor/*.c}
conveyor_inc = -I ${wildcard $(TARGET_DIR)/Hardware/conveyor}
C_SOURCES += $(conveyor_src)
C_INCLUDES += $(conveyor_inc)
