R := R
SOURCEDIR := src
INCLUDEDIR := inst/include

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
INCLUDES := $(shell find $(INCLUDEDIR) -name '*.hpp') $(shell find $(SOURCEDIR) -name '*.h')

CPPCHECK := cppcheck
SCAN_BUILD := scan-build

.PHONY: all api build check document test favicons

all: clean build check install document website

build: #document
	$(R) CMD build .

check: build
	$(R) CMD check rastr*tar.gz

clean:
	-rm -f rastr*tar.gz
	-rm -fr rastr.Rcheck
	-rm -rf src/*.o src/*.so

install: clean
	$(R) CMD INSTALL .

uninstall:
	$(R) --slave -e "remove.packages('rastr')"

document: install-devtools
	$(R) --slave -e "devtools::build_readme(); devtools::document();"

website: document
	$(R) --slave -e "pkgdown::build_site()"

test: install-devtools
	$(R) --slave -e "devtools::test()"

lintr: install-lintr
	$(R) --slave -e "quit(status = length(print(lintr::lint_package())) != 0)"

install-devtools:
	$(R) --slave -e "if (!require('devtools')) install.packages('devtools')"

install-lintr:
	$(R) --slave -e "if (!require('lintr')) install.packages('lintr')"

clang-tidy: clean
	$(SCAN_BUILD) make build

cppcheck:
	$(CPPCHECK) --version
	@$(CPPCHECK) --force                                                  \
	             --enable=all                                             \
	             --language=c++                                           \
	             --inconclusive                                           \
	             --std=c++11                                              \
	             --std=c++14                                              \
	             --inline-suppr                                           \
	             --error-exitcode=1                                       \
	             --quiet                                                  \
	             --suppress=missingIncludeSystem                          \
	             --suppress=unusedStructMember                            \
	              -I inst/include/                                        \
	             $(SOURCES)                                               \
	             $(INCLUDES)

api:
	cd api && R --file=api.R --args node-decl.yml tmpl store
	clang-format -i api/store/*.cpp
	mv api/store/impl.R R/autogen_node.R
	mv api/store/init.cpp src/autogen_init.h
	mv api/store/impl.cpp src/autogen_node_impl.h
	mv api/store/ifc.cpp inst/include/rastr/autogen_node_ifc.h

favicons:
	$(R) -e "pkgdown::build_favicons(overwrite = TRUE)"
