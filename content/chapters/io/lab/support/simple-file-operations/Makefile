BINARIES = file_operations directory_operations
include ../../../../../common/makefile/multiple.mk

JAVAC = javac
JAVA_FILE_OPERATIONS = FileOperations

java-file-operations: $(JAVA_FILE_OPERATIONS).java
	$(JAVAC) $(JAVA_FILE_OPERATIONS).java

clean::
	-rm -f $(JAVA_FILE_OPERATIONS).class
