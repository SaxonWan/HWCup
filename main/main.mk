	main_src  = ${wildcard $(TARGET_DIR)/main/*.c}
	main_inc = -I $(TARGET_DIR)/main
	
	emw3080_src = ${wildcard $(TARGET_DIR)/Hardware/emw3080/*.c} 
	emw3080_inc = -I ${wildcard $(TARGET_DIR)/Hardware/emw3080}
	dobot_src = ${wildcard $(TARGET_DIR)/Hardware/dobot/*.c}
	dobot_inc = -I ${wildcard $(TARGET_DIR)/Hardware/dobot}

	user_demo_defs = -D CONFIG_OC_STREELIGHT_DEMO_ENABLE=1


	C_SOURCES += $(main_src)
	C_INCLUDES += $(main_inc)
	C_SOURCES += $(user_hardware_src)
	C_INCLUDES += $(user_hardware_inc)
	C_DEFS += $(user_demo_defs)
