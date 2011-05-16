# quick_robot_sdk

all : html samples test
	cd libs/ && $(MAKE)
	cd programs/ && $(MAKE)
	cd document/ && $(MAKE)

clean :
	$(RM) -rf $(GENERATED_HTML)
	cd libs/ && $(MAKE) clean
	cd programs/ && $(MAKE) clean
	cd packages/ && $(MAKE) clean
	cd document/ && $(MAKE) clean

samples :
	cd libs/controller/samples/ && $(MAKE)
	cd libs/run_target/samples/ && $(MAKE)
	cd libs/run/samples/ && $(MAKE)
	cd libs/lidar/samples/ && $(MAKE)
	cd programs/run_path_follower/samples/ && $(MAKE)

test :
	cd libs/run_target/test/ && $(MAKE)

html :
	cd document/ && $(MAKE)
