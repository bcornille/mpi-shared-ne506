default: doxy src test

.PHONY: doxy src test clean clean_doxy clean_src clean_tests

doxy:
	doxygen Doxyfile

src:
	cd src/; make; cd ../

test:
	cd test/; make; cd ../

clean: clean_doxy clean_src clean_test

clean_doxy:
	rm -rf docs/html/ docs/latex/

clean_src:
	cd src/; make clean; cd ../

clean_test:
	cd test/; make clean; cd ../
