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
	             --suppress=*:Lexer.cxx                                   \
	             --suppress=*:Lexer.lxx                                   \
	             --suppress=*:Parser.cxx                                  \
	             --suppress=*:Parser.hxx                                  \
	             $(SOURCES)                                               \
	             $(INCLUDES)

################################################################################
# PARSER
################################################################################

.PHONY: parser
parser: $(SOURCEDIR)/Parser.cxx.cpp $(SOURCEDIR)/Parser.hxx $(SOURCEDIR)/Lexer.cxx.cpp $(SOURCEDIR)/Lexer.hxx
	@:

$(SOURCEDIR)/Parser.cxx.cpp $(SOURCEDIR)/Parser.hxx $(SOURCEDIR)/Lexer.cxx.cpp $(SOURCEDIR)/Lexer.hxx: $(GRAMMARDIR)/Parser.yxx $(GRAMMARDIR)/Lexer.lxx
	$(CD) $(GRAMMARDIR) && $(BISON) $(BISONFLAGS) --xml --graph=Parser.gv Parser.yxx
	$(MV) $(GRAMMARDIR)/Parser.cxx $(SOURCEDIR)/Parser.cxx.cpp
	$(MV) $(GRAMMARDIR)/Parser.hxx $(SOURCEDIR)/Parser.hxx
	$(CD) $(GRAMMARDIR) && $(FLEX) $(FLEXFLAGS) Lexer.lxx
	$(MV) $(GRAMMARDIR)/Lexer.cxx $(SOURCEDIR)/Lexer.cxx.cpp
	$(MV) $(GRAMMARDIR)/Lexer.hxx $(SOURCEDIR)/Lexer.hxx
