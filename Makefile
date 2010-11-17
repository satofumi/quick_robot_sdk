# tsukuba_2010/

GENERATED_HTML = generated_html

all : html samples test
	cd libs/ && $(MAKE)
	cd programs/ && $(MAKE)

clean :
	$(RM) -rf $(GENERATED_HTML)
	cd libs/ && $(MAKE) clean
	cd programs/ && $(MAKE) clean
	cd packages/ && $(MAKE) clean

samples :
	cd libs/controller/samples/ && $(MAKE)
	cd libs/run_target/samples/ && $(MAKE)
	cd libs/run/samples/ && $(MAKE)
	cd libs/lidar/samples/ && $(MAKE)
	cd programs/run_path_follower/samples/ && $(MAKE)

test :
	cd libs/run_target/test/ && $(MAKE)

html : $(GENERATED_HTML)/index.html

upload : html
	rsync -avz -e ssh --delete generated_html/* hyakuren-soft@hyakuren-soft.sakura.ne.jp:/home/hyakuren-soft/www/robot_soft/

$(GENERATED_HTML)/index.html : $(wildcard dox/* libs/run_target/*.[ch] libs/run_target/samples/*.[ch] libs/run_target/dox/* libs/run/*.h libs/run/*.cpp libs/run/dox/* libs/lidar/*.h libs/lidar/*.cpp programs/run_path_recorder/* programs/run_path_recorder/dox/* programs/run_path_follower/* programs/run_path_follower/dox/* programs/run_wired_controller) Doxyfile
	doxygen
