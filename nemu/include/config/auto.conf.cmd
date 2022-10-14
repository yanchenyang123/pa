deps_config := \
	src/device/Kconfig \
	src/memory/Kconfig \
	/home/ycy/ics2022/nemu/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
