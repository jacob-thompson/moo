CFLAGS ?= -std=c99 -pedantic -Wall -Wextra -Werror

MAIN = moo
ADT = set
TEST = settest

$(MAIN): $(MAIN).o $(ADT).o
	$(CC) $(LDFLAGS) $^ -o $@

all: $(TEST) $(MAIN)

test: $(TEST)

$(TEST): $(TEST).o $(ADT).o
	$(CC) $(LDFLAGS) $^ -o $@

$(MAIN).o: $(MAIN).c $(ADT).h
	$(CC) $(CFLAGS) -c $< -o $@

$(ADT).o: $(ADT).c $(ADT).h
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST).o: $(TEST).c $(ADT).h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(TEST) $(MAIN)
	rm -f *.o
