# Backup System

## Scenario

For speed, a data analysis program uses memory pages (typically, it uses around 4GB of RAM) to store information.
Because the data is critical, its loss is not allowed in case the operating system is unexpectedly restarted.
We want to add a backup functionality to the program so that data from memory is periodically saved to disk.
For data recovery, analysis data for the last N intervals is kept (we have N files of 4GB each, each file retains analysis data from a backup).

All answers should be justified.

## Questions

1. How would you implement such a backup system?

1. How do you determine the opportune moment for performing the backup?

1. Do you use a separate process or thread for performing the backup?
Justify your answer.

1. How do you manage the files saved to disk?

1. How do you analyze the overhead brought by the backup functionality?
