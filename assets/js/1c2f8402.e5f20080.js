"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[33457],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>u});var a=n(67294);function i(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function r(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function o(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?r(Object(n),!0).forEach((function(t){i(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):r(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,a,i=function(e,t){if(null==e)return{};var n,a,i={},r=Object.keys(e);for(a=0;a<r.length;a++)n=r[a],t.indexOf(n)>=0||(i[n]=e[n]);return i}(e,t);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);for(a=0;a<r.length;a++)n=r[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var s=a.createContext({}),p=function(e){var t=a.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):o(o({},t),e)),n},c=function(e){var t=p(e.components);return a.createElement(s.Provider,{value:t},e.children)},d={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},h=a.forwardRef((function(e,t){var n=e.components,i=e.mdxType,r=e.originalType,s=e.parentName,c=l(e,["components","mdxType","originalType","parentName"]),h=p(n),u=i,f=h["".concat(s,".").concat(u)]||h[u]||d[u]||r;return n?a.createElement(f,o(o({ref:t},c),{},{components:n})):a.createElement(f,o({ref:t},c))}));function u(e,t){var n=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var r=n.length,o=new Array(r);o[0]=h;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l.mdxType="string"==typeof e?e:i,o[1]=l;for(var p=2;p<r;p++)o[p]=n[p];return a.createElement.apply(null,o)}return a.createElement.apply(null,n)}h.displayName="MDXCreateElement"},63113:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>o,default:()=>d,frontMatter:()=>r,metadata:()=>l,toc:()=>p});var a=n(87462),i=(n(67294),n(3905));const r={},o="File Handling",l={unversionedId:"Lab/I/O/File Mappings/content/file-handlers",id:"Lab/I/O/File Mappings/content/file-handlers",title:"File Handling",description:"You've most likely had to deal with files in the past.",source:"@site/docs/Lab/I/O/File Mappings/content/file-handlers.md",sourceDirName:"Lab/I/O/File Mappings/content",slug:"/Lab/I/O/File Mappings/content/file-handlers",permalink:"/operating-systems/Lab/I/O/File Mappings/content/file-handlers",draft:!1,tags:[],version:"current",frontMatter:{}},s={},p=[{value:"Reaching the File",id:"reaching-the-file",level:2},{value:"Limitations of High-level File Handlers",id:"limitations-of-high-level-file-handlers",level:3}],c={toc:p};function d(e){let{components:t,...n}=e;return(0,i.kt)("wrapper",(0,a.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,i.kt)("h1",{id:"file-handling"},"File Handling"),(0,i.kt)("p",null,"You've most likely had to deal with files in the past.\nGo to ",(0,i.kt)("inlineCode",{parentName:"p"},"support/simple-file-handling")," and run a most basic command:\n",(0,i.kt)("inlineCode",{parentName:"p"},"cat file.txt"),":"),(0,i.kt)("pre",null,(0,i.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/simple-file-handling$ cat file.txt\nOS Rullz!\n")),(0,i.kt)("p",null,"But how does ",(0,i.kt)("inlineCode",{parentName:"p"},"cat"),' actually "reach" to the file, then read its contents, then print them to standard output?\nThis is part of what we\'re going to learn.'),(0,i.kt)("h2",{id:"reaching-the-file"},"Reaching the File"),(0,i.kt)("p",null,"To manipulate the file (read its contents, modify them, change its size etc.), each process must first get a ",(0,i.kt)("strong",{parentName:"p"},"handler")," to this file.\nThink of this handler as an object by which the process can identify and refer to the file."),(0,i.kt)("p",null,"Now take a look at the code examples in ",(0,i.kt)("inlineCode",{parentName:"p"},"support/simple-file-handling"),".\nEach of them reads the contents of ",(0,i.kt)("inlineCode",{parentName:"p"},"file.txt"),", modifies them and then reads the previously modified file again.\nUse ",(0,i.kt)("inlineCode",{parentName:"p"},"make")," to compile the C code and ",(0,i.kt)("inlineCode",{parentName:"p"},"make java-file-operations")," to compile the Java code."),(0,i.kt)("p",null,"Now run the programs repeatedly in whatever order you wish:"),(0,i.kt)("pre",null,(0,i.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/simple-file-handling$ python3 file_operations.py\nFile contents are: OS Rullz!\nWrote new data to file\nFile contents are: Python was here!\n\nstudent@os:~/.../lab/support/simple-file-handling$ ./file_operations  # from the C code\nFile contents are: Python was here!\nWrote new data to file\nFile contents are: C was here!\n\nstudent@os:~/.../lab/support/simple-file-handling$ java FileOperations\nFile contents are: Python was here!\nWrote new data to file\nFile contents are: C was here!\n")),(0,i.kt)("p",null,"Note that each piece of code creates a variable which is then used as a handler."),(0,i.kt)("p",null,(0,i.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/File%20Mappings/quiz/file-handler-c"},"Quiz")),(0,i.kt)("h3",{id:"limitations-of-high-level-file-handlers"},"Limitations of High-level File Handlers"),(0,i.kt)("p",null,(0,i.kt)("strong",{parentName:"p"},"Everything in Linux is a file."),"\nThis statement says that the Linux OS treats every entry in a file system (regular file, directory, block device, char device, link, UNIX socket) as a file.\nThis is very convenient for creating a unified interface that deals with all these files.\nWe would like our file handlers to also be able to handle all types of files."),(0,i.kt)("p",null,"Let's try this.\nNavigate to ",(0,i.kt)("inlineCode",{parentName:"p"},"support/simple-file-operations/directory_operations.c"),".\nRead the code.\nIt does something very simple:\nit attempts to open the ",(0,i.kt)("inlineCode",{parentName:"p"},"dir")," directory the same way ",(0,i.kt)("inlineCode",{parentName:"p"},"file_operations.c")," tried to open ",(0,i.kt)("inlineCode",{parentName:"p"},"file.txt"),".\nCompile and run the code."),(0,i.kt)("pre",null,(0,i.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/simple-file-handling$ ./directory_operations\n18:18:11 FATAL directory_operations.c:14: fopen: Is a directory\n")),(0,i.kt)("p",null,"The error message is crystal clear: we cannot use ",(0,i.kt)("inlineCode",{parentName:"p"},"fopen()")," on directories.\nSo the ",(0,i.kt)("inlineCode",{parentName:"p"},"FILE")," structure is unsuited for directories.\nTherefore, this handler is not generic enough for a regular Linux filesystem."),(0,i.kt)("p",null,"To get to the directory, we need to use a lower-level function.\nLet's take a look at the syscall used by ",(0,i.kt)("inlineCode",{parentName:"p"},"fopen()"),"."),(0,i.kt)("p",null,(0,i.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/File%20Mappings/quiz/fopen-syscall"},"Quiz")),(0,i.kt)("p",null,"We will use a simpler syscall, called ",(0,i.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/open.2.html"},(0,i.kt)("inlineCode",{parentName:"a"},"open()")),".\nIn fact, ",(0,i.kt)("inlineCode",{parentName:"p"},"open()")," is a wrapper over ",(0,i.kt)("inlineCode",{parentName:"p"},"openat()"),".\nNavigate to ",(0,i.kt)("inlineCode",{parentName:"p"},"support/file-descriptors/directory_open.c"),".\nInspect, compile and run the code."),(0,i.kt)("pre",null,(0,i.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/file-descriptors$ ./open_directory\nDirectory file descriptor is: 3\n")),(0,i.kt)("p",null,"We can now see that the ",(0,i.kt)("inlineCode",{parentName:"p"},"open()")," syscall is capable of also handling directories, so its closer to what we want.\nNote that it is rather uncommon to use ",(0,i.kt)("inlineCode",{parentName:"p"},"open()")," for directories.\nMost of the time, ",(0,i.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man3/opendir.3.html"},(0,i.kt)("inlineCode",{parentName:"a"},"opendir()"))," is used instead.\nBut what does it return?\nFind out in ",(0,i.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/File%20Mappings/content/file-descriptors"},'the "File Descriptors" section'),"."))}d.isMDXComponent=!0}}]);