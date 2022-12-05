"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[13165],{3905:(e,t,n)=>{n.d(t,{Zo:()=>d,kt:()=>u});var i=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);t&&(i=i.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,i)}return n}function r(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function p(e,t){if(null==e)return{};var n,i,a=function(e,t){if(null==e)return{};var n,i,a={},o=Object.keys(e);for(i=0;i<o.length;i++)n=o[i],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(i=0;i<o.length;i++)n=o[i],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=i.createContext({}),l=function(e){var t=i.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):r(r({},t),e)),n},d=function(e){var t=l(e.components);return i.createElement(s.Provider,{value:t},e.children)},m="mdxType",c={inlineCode:"code",wrapper:function(e){var t=e.children;return i.createElement(i.Fragment,{},t)}},h=i.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,d=p(e,["components","mdxType","originalType","parentName"]),m=l(n),h=a,u=m["".concat(s,".").concat(h)]||m[h]||c[h]||o;return n?i.createElement(u,r(r({ref:t},d),{},{components:n})):i.createElement(u,r({ref:t},d))}));function u(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,r=new Array(o);r[0]=h;var p={};for(var s in t)hasOwnProperty.call(t,s)&&(p[s]=t[s]);p.originalType=e,p[m]="string"==typeof e?e:a,r[1]=p;for(var l=2;l<o;l++)r[l]=n[l];return i.createElement.apply(null,r)}return i.createElement.apply(null,n)}h.displayName="MDXCreateElement"},75228:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>r,default:()=>m,frontMatter:()=>o,metadata:()=>p,toc:()=>l});var i=n(87462),a=(n(67294),n(3905));const o={},r="Pipes",p={unversionedId:"Lab/I/O/Remote I/O/content/pipes",id:"Lab/I/O/Remote I/O/content/pipes",title:"Pipes",description:"When it comes to inter-process communication, so far we know that 2 different processes can mmap() the same file and use that as some sort of shared memory, but this requires writing data to the disk which is slow.",source:"@site/docs/Lab/I/O/Remote I/O/content/pipes.md",sourceDirName:"Lab/I/O/Remote I/O/content",slug:"/Lab/I/O/Remote I/O/content/pipes",permalink:"/operating-systems/Lab/I/O/Remote I/O/content/pipes",draft:!1,tags:[],version:"current",frontMatter:{}},s={},l=[{value:"Anonymous Pipes - <code>pipe()</code>",id:"anonymous-pipes---pipe",level:2},{value:"Practice: Find the Right <del>Hole</del> File Descriptor",id:"practice-find-the-right-hole-file-descriptor",level:2},{value:"Practice: Inheritance",id:"practice-inheritance",level:3},{value:"Practice: Now We Pipe",id:"practice-now-we-pipe",level:3},{value:"Practiece: Receive Pipes",id:"practiece-receive-pipes",level:3},{value:"Anonymous Pipes: Conclusion",id:"anonymous-pipes-conclusion",level:3},{value:"Named Pipes - <code>mkfifo()</code>",id:"named-pipes---mkfifo",level:2},{value:"Pracice: From the CLI",id:"pracice-from-the-cli",level:3},{value:"Pracice: From the Code - Receive FIFO",id:"pracice-from-the-code---receive-fifo",level:3},{value:"Named Pipes: Conclusion",id:"named-pipes-conclusion",level:3}],d={toc:l};function m(e){let{components:t,...o}=e;return(0,a.kt)("wrapper",(0,i.Z)({},d,o,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"pipes"},"Pipes"),(0,a.kt)("p",null,"When it comes to inter-process communication, so far we know that 2 different processes can ",(0,a.kt)("inlineCode",{parentName:"p"},"mmap()")," the same file and use that as some sort of shared memory, but this requires writing data to the disk which is slow.\nThen we know they can ",(0,a.kt)("inlineCode",{parentName:"p"},"wait()"),"/",(0,a.kt)("inlineCode",{parentName:"p"},"waitpid()")," for each other to finish, or better yet, use shared semaphores or mutexes, but these mechanisms aren't good at at passing data between processes.\nSo our goals fot this session are to learn how to use an IPC (inter-process communication) mechanism that:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"allows transfers between processes, not notifications")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"is faster than reading and writing from/to files"))),(0,a.kt)("h2",{id:"anonymous-pipes---pipe"},"Anonymous Pipes - ",(0,a.kt)("inlineCode",{parentName:"h2"},"pipe()")),(0,a.kt)("p",null,"Have you ever wondered how Bash handles redirecting the ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout")," of a command to the ",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," of the next command in one-liners such as:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-bash"},"cat 'log_*.csv' | tr -s ' ' | cut -d ',' -f 2 | sort -u | head -n 10\n")),(0,a.kt)("p",null,"The ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout")," of ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," is the ",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," of ",(0,a.kt)("inlineCode",{parentName:"p"},"tr"),", whose ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout")," is the ",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," of ",(0,a.kt)("inlineCode",{parentName:"p"},"cut"),' and so on.\nThis "chain" of commands looks like this:'),(0,a.kt)("p",null,(0,a.kt)("img",{alt:"Piped Commands",src:n(12978).Z,width:"762",height:"82"})),(0,a.kt)("p",null,"So here we have a ",(0,a.kt)("strong",{parentName:"p"},"unidirectional")," stream of data that starts from ",(0,a.kt)("inlineCode",{parentName:"p"},"cat"),", is modified by each new command and then it's passed to the next one.\nWe can tell from the image above that the communication channel between any 2 adjacent commands allows one process to write to it while the other reads from it.\nFor example, there is no need for ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," to read any of ",(0,a.kt)("inlineCode",{parentName:"p"},"tr"),"'s output, only vice-versa."),(0,a.kt)("p",null,"Therefore, this communication channel needs 2 ends:\none for reading (from which commands get their input) and another for writing (to which commands write their output).\nIn UNIX, the need for such a channel is fulfilled by the ",(0,a.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/pipe.2.html"},(0,a.kt)("inlineCode",{parentName:"a"},"pipe()")," syscall"),".\nImagine there's a literal pipe between any 2 adjacent commands in the image above where data is what flows through this pipe ",(0,a.kt)("strong",{parentName:"p"},"in only a single way"),".\nThis is why the ",(0,a.kt)("inlineCode",{parentName:"p"},"|")," operator in Bash is called pipe and why the syscall is also named ",(0,a.kt)("inlineCode",{parentName:"p"},"pipe()"),"."),(0,a.kt)("p",null,"This type of pipe is also called an ",(0,a.kt)("strong",{parentName:"p"},"anonymous pipe"),", because it cannot be identified using a name (i.e. it is not backed by any file).\nThe data written to it is kept in a circular buffer inside the kernel from where it can be then read by the child process.\nThis is faster than writing data to a file, so we achieve both our ",(0,a.kt)("a",{parentName:"p",href:"#pipes"},"initial goals"),"."),(0,a.kt)("h2",{id:"practice-find-the-right-hole-file-descriptor"},"Practice: Find the Right ",(0,a.kt)("del",{parentName:"h2"},"Hole")," File Descriptor"),(0,a.kt)("p",null,"Navigate to ",(0,a.kt)("inlineCode",{parentName:"p"},"support/pipes/anonymous_pipe.c"),".\nCompile and run the code.\nIn another terminal, use ",(0,a.kt)("inlineCode",{parentName:"p"},"lsof")," to see:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"the file descriptors opened by the parent process between the creation of the pipe and the call to ",(0,a.kt)("inlineCode",{parentName:"p"},"fork()"))),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"the file descriptors opened by the child process"))),(0,a.kt)("p",null,(0,a.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/Remote%20I/O/quiz/pipe-ends"},"Quiz")),(0,a.kt)("p",null,"A simple way to memorise which pipe end is which is to thing about ",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout"),", respectively.\n",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," is file descriptor 0 and is mostly for reading and ",(0,a.kt)("inlineCode",{parentName:"p"},"pipedes[0]")," is also for reading.\nConversely, ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout")," is file descriptor 1 and is meant for writing, just like ",(0,a.kt)("inlineCode",{parentName:"p"},"pipedes[1]"),".\nNow you won't confuse them."),(0,a.kt)("h3",{id:"practice-inheritance"},"Practice: Inheritance"),(0,a.kt)("p",null,"An important thing to take note of before we actually use pipes is that file descriptors are ",(0,a.kt)("strong",{parentName:"p"},"inherited")," by the child process from the parent.\nSo if the parent opens some file descriptors (like, say, for a pipe), the child will also be able to use them.\nDon't believe us?"),(0,a.kt)("p",null,"Modify the code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/pipes/anonymous_pipes.c")," and call ",(0,a.kt)("inlineCode",{parentName:"p"},"wait_for_input()")," from the child process.\nThen use ",(0,a.kt)("inlineCode",{parentName:"p"},"lsof")," again with the PID of the child process to make sure file descriptors 3 and 4 are still open."),(0,a.kt)("h3",{id:"practice-now-we-pipe"},"Practice: Now We Pipe"),(0,a.kt)("p",null,"Now comes the moment you've most likely been waiting for.\nThe code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/pipes/anonymous_pipes.c")," wants to create something like a client-server dynamic between the parent and the child.\nThe parent reads data from ",(0,a.kt)("inlineCode",{parentName:"p"},"stdin")," and sends it to the child via the pipe they share.\nThe client (parent) ends communication when you type ",(0,a.kt)("inlineCode",{parentName:"p"},'"exit"'),"."),(0,a.kt)("p",null,"You can comment out the calls to ",(0,a.kt)("inlineCode",{parentName:"p"},"wait_for_input()")," if you find them annoying."),(0,a.kt)("h3",{id:"practiece-receive-pipes"},"Practiece: Receive Pipes"),(0,a.kt)("p",null,"Use your knowledge of pipes to solve the a CTF challenge.\nNavigate to ",(0,a.kt)("inlineCode",{parentName:"p"},"support/receive-challenges")," and look into the files ",(0,a.kt)("inlineCode",{parentName:"p"},"receive_pipe.c")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"send_fd_4.c"),".\nModify ",(0,a.kt)("inlineCode",{parentName:"p"},"receive_pipe.c")," so that it creates a pipe, then spawns a child process.\nThe child will redirect file descriptor 4 to ",(0,a.kt)("inlineCode",{parentName:"p"},"stdout")," and then ",(0,a.kt)("inlineCode",{parentName:"p"},"execlp()")," ",(0,a.kt)("inlineCode",{parentName:"p"},"send_fd_4"),".\n",(0,a.kt)("inlineCode",{parentName:"p"},"send_fd_4")," wries the flag to  file descriptor 4 (",(0,a.kt)("inlineCode",{parentName:"p"},"pipefd[1]"),"), so the parent process needs to read it from from ",(0,a.kt)("inlineCode",{parentName:"p"},"pipedefd[0]"),"."),(0,a.kt)("p",null,"Once you do this, note that file descriptors are also maintained after calling ",(0,a.kt)("inlineCode",{parentName:"p"},"exec()")," to run a completely new program."),(0,a.kt)("p",null,"Now if you want to use pipes even more, go over to ",(0,a.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/Remote%20I/O/content/arena#mini-shell-with-blackjack-and-pipes"},"the Arena")," and add support for pipes to the mini-shell you've previously worked on."),(0,a.kt)("h3",{id:"anonymous-pipes-conclusion"},"Anonymous Pipes: Conclusion"),(0,a.kt)("p",null,"Anonymous pipes give allow us to efficiently transmit data between 2 processes, as no disk access is required.\nHowever, they still have one major limitation."),(0,a.kt)("p",null,(0,a.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/Remote%20I/O/quiz/anonymous-pipes-limitation"},"Quiz")),(0,a.kt)("p",null,"The answer to this is to employ ",(0,a.kt)("em",{parentName:"p"},"some")," filesystem support."),(0,a.kt)("h2",{id:"named-pipes---mkfifo"},"Named Pipes - ",(0,a.kt)("inlineCode",{parentName:"h2"},"mkfifo()")),(0,a.kt)("p",null,"We will give up on some performance by writing data to a file, but the reading and writing to the file must behave just like using a named pipe:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"reading doesn't block while there's still data in the pipe"),(0,a.kt)("li",{parentName:"ul"},"reading from an empty pipe stalls the current thread until data becomes available.\nThis is one of the cases where ",(0,a.kt)("inlineCode",{parentName:"li"},"read()")," might not return as many bytes as we requested.\nRemember:\nalways use loops with ",(0,a.kt)("inlineCode",{parentName:"li"},"read()")," and ",(0,a.kt)("inlineCode",{parentName:"li"},"write()"))),(0,a.kt)("p",null,"Because this pipe uses a file, which must have a name, it is called a ",(0,a.kt)("strong",{parentName:"p"},"named pipe"),"."),(0,a.kt)("h3",{id:"pracice-from-the-cli"},"Pracice: From the CLI"),(0,a.kt)("p",null,"First, let's use named pipes from the terminal.\nUse the ",(0,a.kt)("inlineCode",{parentName:"p"},"mkfifo")," command to create one such file:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~$ mkfifo fifo\n\nstudent@os:~$ ls -l fifo\nprw-rw-r-- 1 student student 0 Nov 22 23:20 fifo|\n")),(0,a.kt)("p",null,"The fact that pipes are also called FIFOs should come as no surprise.\nThey act like queues/FIFOs:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"you add data to one end (push/enqueue)"),(0,a.kt)("li",{parentName:"ul"},"you extract data from the other (pop/dequeue)")),(0,a.kt)("p",null,"Also note the ",(0,a.kt)("inlineCode",{parentName:"p"},"p")," at the beginning of the output above.\nIt symbolises the type of this file:\na named ",(0,a.kt)("strong",{parentName:"p"},"pipe"),"."),(0,a.kt)("p",null,"Now let's use it.\nOpen 2 terminals."),(0,a.kt)("ol",null,(0,a.kt)("li",{parentName:"ol"},(0,a.kt)("p",{parentName:"li"},"In the first one, use ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," to read from ",(0,a.kt)("inlineCode",{parentName:"p"},"fifo"),".\nNote that the command is blocked because the pipe is empty so ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," has nothing to read.\nThen, in the second terminal, write some message to ",(0,a.kt)("inlineCode",{parentName:"p"},"fifo")," using ",(0,a.kt)("inlineCode",{parentName:"p"},"echo"),".\nIn the first terminal, you should see that ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," has finished and the message has appeared there.")),(0,a.kt)("li",{parentName:"ol"},(0,a.kt)("p",{parentName:"li"},"Now do it the other way around:\nfirst ",(0,a.kt)("inlineCode",{parentName:"p"},"echo")," some string into the pipe and ",(0,a.kt)("strong",{parentName:"p"},"then")," read it with ",(0,a.kt)("inlineCode",{parentName:"p"},"cat"),".\nNote that now the ",(0,a.kt)("inlineCode",{parentName:"p"},"echo")," command is blocked.\nNow ",(0,a.kt)("inlineCode",{parentName:"p"},"cat")," should end immediately and the string should appear because we have already placed some data in the pipe.\nAlso, the previous ",(0,a.kt)("inlineCode",{parentName:"p"},"echo")," should finish now."))),(0,a.kt)("p",null,(0,a.kt)("strong",{parentName:"p"},"Remember:"),"\n",(0,a.kt)("strong",{parentName:"p"},"Reading from a pipe blocks while the pipe is empty."),"\n",(0,a.kt)("strong",{parentName:"p"},"Writing to a pipe blocks until it is empty.")),(0,a.kt)("h3",{id:"pracice-from-the-code---receive-fifo"},"Pracice: From the Code - Receive FIFO"),(0,a.kt)("p",null,"The libc function with which we can create named pipes is...\n",(0,a.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man3/mkfifo.3.html"},(0,a.kt)("inlineCode",{parentName:"a"},"mkfifo()")),".\nYou weren't expecting this, were you?\nIts underlying syscall is ",(0,a.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/mknodat.2.html"},(0,a.kt)("inlineCode",{parentName:"a"},"mknod()")),", which simply creates a file of whatever type we specify, but that's besides the point."),(0,a.kt)("p",null,"Navigate to ",(0,a.kt)("inlineCode",{parentName:"p"},"support/receive-challenges/")," and look into ",(0,a.kt)("inlineCode",{parentName:"p"},"receive_fifo.c")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"send_fifo.c"),".\nFollow the ",(0,a.kt)("inlineCode",{parentName:"p"},"TODO"),"s in the former file to read the flag that the latter writes into the named pipe.\nNote that after you create the named pipe, you have to read from it like you would from any regular file."),(0,a.kt)("h3",{id:"named-pipes-conclusion"},"Named Pipes: Conclusion"),(0,a.kt)("p",null,"It is nice to remember that named pipes sacrifice little to no performance when compared to anonymous pipes.\nWhile it may seem that the data being passed through them is written to the disk, then read and overwritten, this is not the case.\nThe FIFO file is just a handler within the filesystem that is used to write data to a buffer inside the kernel.\nThis buffer holds the data that is passed between processes, not the filesystem.\nSo we still don't break our 2 desires from the beginning of this section:\nto allow data transfer and to do so efficiently."))}m.isMDXComponent=!0},12978:(e,t,n)=>{n.d(t,{Z:()=>i});const i=n.p+"assets/images/piped-commands-118a36fba312c6bea5270dba74d653e2.svg"}}]);