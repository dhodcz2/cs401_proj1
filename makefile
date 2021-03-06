
all: ssum ssum_memo ssum_r

clean:
	rm -f  ssum ssum_memo ssum_r

ssum: ssum.cpp
	g++ -std=c++11 ssum.cpp -o ssum

ssum_memo: ssum_memo.cpp
	g++ -std=c++11 ssum_memo.cpp -o ssum_memo

ssum_r: ssum_r.c
	gcc ssum_r.c -o ssum_r
