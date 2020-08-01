SOURCEDIR := src
INCLUDEDIR := inst/include
GRAMMARDIR := grammar

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
INCLUDES := $(shell find $(INCLUDEDIR) -name '*.hpp') $(shell find $(SOURCEDIR) -name '*.h')

CPPCHECK := cppcheck
SCAN_BUILD := scan-build
BISON := bison
FLEX := flex
MV := mv
CD := cd
FLEXFLAGS := -v
BISONFLAGS := -v

.PHONY: all build check document test

all: clean document build check

build: document
	R CMD build .

check: build
	R CMD check rastr*tar.gz

clean:
	-rm -f rastr*tar.gz
	-rm -fr rastr.Rcheck
	-rm -rf src/*.o src/*.so

install: clean
	R CMD INSTALL .

uninstall:
	R --slave -e "remove.packages('rastr')"

document: install-devtools
	R --slave -e "devtools::document()"

test: install-devtools
	R --slave -e "devtools::test()"

lintr: install-lintr
	R --slave -e "quit(status = length(print(lintr::lint_package())) != 0)"

install-devtools:
	R --slave -e "if (!require('devtools')) install.packages('devtools')"

install-lintr:
	R --slave -e "if (!require('lintr')) install.packages('lintr')"

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
	             --suppress=missingInclude                                \
	             --suppress=unusedFunction                                \
	             -I inst/include/                                         \
	             --suppress=*:RLexer.cxx                                  \
	             --suppress=*:RLexer.lxx                                  \
	             --suppress=*:RParser.cxx                                 \
	             --suppress=*:RParser.hxx                                 \
	             $(SOURCES)                                               \
	             $(INCLUDES)

################################################################################
# PARSER
################################################################################

.PHONY: parser
parser: $(SOURCEDIR)/RParser.cxx.cpp $(SOURCEDIR)/RParser.hxx $(SOURCEDIR)/RLexer.cxx.cpp $(SOURCEDIR)/RLexer.hxx
	@:

$(SOURCEDIR)/RParser.cxx.cpp $(SOURCEDIR)/RParser.hxx $(SOURCEDIR)/RLexer.cxx.cpp $(SOURCEDIR)/RLexer.hxx: $(GRAMMARDIR)/RParser.yxx $(GRAMMARDIR)/RLexer.lxx
	$(CD) $(GRAMMARDIR) && $(BISON) $(BISONFLAGS) --xml --graph=RParser.gv RParser.yxx
	$(MV) $(GRAMMARDIR)/RParser.cxx $(SOURCEDIR)/RParser.cxx.cpp
	$(MV) $(GRAMMARDIR)/RParser.hxx $(SOURCEDIR)/RParser.hxx
	$(CD) $(GRAMMARDIR) && $(FLEX) $(FLEXFLAGS) RLexer.lxx
	$(MV) $(GRAMMARDIR)/RLexer.cxx $(SOURCEDIR)/RLexer.cxx.cpp
	$(MV) $(GRAMMARDIR)/RLexer.hxx $(SOURCEDIR)/RLexer.hxx
