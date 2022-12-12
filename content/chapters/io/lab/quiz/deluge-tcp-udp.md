# Deluge: TCP or UDP

## Question Text

Should Deluge use UDP or TCP to transfer torrent files?

## Question Answers

- It should use UDP for faster file transfers

+ It should use TCP to guarantee the integrity of the transferred files

## Feedback

Speed is nice to have.
Correctness is mandatory in most scenarios, including this one.
The only situation when correctness may be overlooked is when some given data will be quckly replaced by some other data.
But files are persistent.
If you download a video game from as a torrent (we've all done that), you want to keep it for a while and first and foremost, it has to work properly, i.e. not be corrupt.
