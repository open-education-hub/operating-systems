LDFLAGS = -z lazy

.PHONY: all clean

all: hello

hello: hello.go
	go build -ldflags '-linkmode external -extldflags "-dynamic"' $<

clean:
	-rm -f hello
	-rm -f *~
