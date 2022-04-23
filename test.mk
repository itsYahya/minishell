GPP = g++

TEST_BDIR = tests/build
TEST_FILES = test_scan_word test_scan_var test_scan_literal
TEST_OBJ = $(addprefix $(TEST_BDIR)/, $(TEST_FILES:=.o))
TEST_CFLAGS = -Wall -Werror -Wextra
TEST_LDFLAGS = -lreadline -lgtest  -lpthread
TESTER = tester

test_run: $(TESTER) 
	./tester

$(TESTER): $(TEST_OBJ) $(OBJ)
	$(GPP) $(TEST_CFLAGS) $(INC) $^ tests/main.cpp $(TEST_LDFLAGS) -o $@


test_clean:
	rm -rf $(TEST_BDIR)
	rm -rf $(TESTER) 

$(TEST_BDIR)/%.o: tests/%.cpp
	mkdir -p $(@D)
	$(GPP) $(INC) -c $^ -o $@
