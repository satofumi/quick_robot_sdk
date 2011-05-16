# document

OUTPUT_HTML_DIR = generated_html

all : html

clean :

html : $(OUTPUT_HTML_DIR)/index.html

.PHONY : all clean html
######################################################################
$(OUTPUT_HTML_DIR)/index.html : $(wildcard dox/* ../libs/run_target/*.[ch] ../libs/run_target/samples/*.[ch] ../libs/run_target/dox/* ../libs/run/*.h ../libs/run/*.cpp ../libs/run/dox/* ../libs/lidar/*.h ../libs/lidar/*.cpp ../programs/run_path_recorder/* ../programs/run_path_recorder/dox/* ../programs/run_path_follower/* ../programs/run_path_follower/dox/* ../programs/run_wired_controller) Doxyfile
	doxygen
	cp ../packages/quick_robot_sdk/COPYING generated_html/
