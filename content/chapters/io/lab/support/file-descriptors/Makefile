BINARIES = file_operations print_errors
include ../../../../../common/makefile/multiple.mk

JAVAC = javac
JAVA_FILE_OPERATIONS = FileOperations

java-file-operations: $(JAVA_FILE_OPERATIONS).java
	$(JAVAC) $(JAVA_FILE_OPERATIONS).java

clean::
	-rm -f write_file.txt
	-rm -f $(JAVA_FILE_OPERATIONS).class