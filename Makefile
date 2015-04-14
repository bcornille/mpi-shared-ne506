default: doxy src test

doxy:
	doxygen Doxyfile

src:
	cd src/; make; cd ../

test:
	cd test/; make; cd ../

clean: clean_doxy clean_src clean_test

clean_doxy:
	rm -rf doc/

clean_src:
	cd src/; make clean; cd ../

clean_test:
	cd test/; make clean; cd ../
