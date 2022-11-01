"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[54473],{3905:(e,t,l)=>{l.d(t,{Zo:()=>p,kt:()=>u});var a=l(67294);function n(e,t,l){return t in e?Object.defineProperty(e,t,{value:l,enumerable:!0,configurable:!0,writable:!0}):e[t]=l,e}function r(e,t){var l=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),l.push.apply(l,a)}return l}function i(e){for(var t=1;t<arguments.length;t++){var l=null!=arguments[t]?arguments[t]:{};t%2?r(Object(l),!0).forEach((function(t){n(e,t,l[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(l)):r(Object(l)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(l,t))}))}return e}function o(e,t){if(null==e)return{};var l,a,n=function(e,t){if(null==e)return{};var l,a,n={},r=Object.keys(e);for(a=0;a<r.length;a++)l=r[a],t.indexOf(l)>=0||(n[l]=e[l]);return n}(e,t);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);for(a=0;a<r.length;a++)l=r[a],t.indexOf(l)>=0||Object.prototype.propertyIsEnumerable.call(e,l)&&(n[l]=e[l])}return n}var s=a.createContext({}),c=function(e){var t=a.useContext(s),l=t;return e&&(l="function"==typeof e?e(t):i(i({},t),e)),l},p=function(e){var t=c(e.components);return a.createElement(s.Provider,{value:t},e.children)},m={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},d=a.forwardRef((function(e,t){var l=e.components,n=e.mdxType,r=e.originalType,s=e.parentName,p=o(e,["components","mdxType","originalType","parentName"]),d=c(l),u=n,y=d["".concat(s,".").concat(u)]||d[u]||m[u]||r;return l?a.createElement(y,i(i({ref:t},p),{},{components:l})):a.createElement(y,i({ref:t},p))}));function u(e,t){var l=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var r=l.length,i=new Array(r);i[0]=d;var o={};for(var s in t)hasOwnProperty.call(t,s)&&(o[s]=t[s]);o.originalType=e,o.mdxType="string"==typeof e?e:n,i[1]=o;for(var c=2;c<r;c++)i[c]=l[c];return a.createElement.apply(null,i)}return a.createElement.apply(null,l)}d.displayName="MDXCreateElement"},62350:(e,t,l)=>{l.r(t),l.d(t,{assets:()=>s,contentTitle:()=>i,default:()=>m,frontMatter:()=>r,metadata:()=>o,toc:()=>c});var a=l(87462),n=(l(67294),l(3905));const r={},i=void 0,o={unversionedId:"Lab/Software-Stack/Libc/content/libcall-syscall",id:"Lab/Software-Stack/Libc/content/libcall-syscall",title:"libcall-syscall",description:"Library calls vs system calls",source:"@site/docs/Lab/Software-Stack/Libc/content/libcall-syscall.md",sourceDirName:"Lab/Software-Stack/Libc/content",slug:"/Lab/Software-Stack/Libc/content/libcall-syscall",permalink:"/operating-systems/Lab/Software-Stack/Libc/content/libcall-syscall",draft:!1,tags:[],version:"current",frontMatter:{}},s={},c=[{value:"Library calls vs system calls",id:"library-calls-vs-system-calls",level:3},{value:"Practice",id:"practice",level:4}],p={toc:c};function m(e){let{components:t,...l}=e;return(0,n.kt)("wrapper",(0,a.Z)({},p,l,{components:t,mdxType:"MDXLayout"}),(0,n.kt)("h3",{id:"library-calls-vs-system-calls"},"Library calls vs system calls"),(0,n.kt)("p",null,"The standard C library has primarily two uses:"),(0,n.kt)("ol",null,(0,n.kt)("li",{parentName:"ol"},"wrapping system calls into easier to use C-style library calls, such as ",(0,n.kt)("inlineCode",{parentName:"li"},"open()"),", ",(0,n.kt)("inlineCode",{parentName:"li"},"write()"),", ",(0,n.kt)("inlineCode",{parentName:"li"},"read()")),(0,n.kt)("li",{parentName:"ol"},"adding common functionality required for our program, such as string management (",(0,n.kt)("inlineCode",{parentName:"li"},"strcpy"),"), memory management (",(0,n.kt)("inlineCode",{parentName:"li"},"malloc()"),") or formatted I/O (",(0,n.kt)("inlineCode",{parentName:"li"},"printf()"),")")),(0,n.kt)("p",null,"The first use means a 1-to-1 mapping between library calls and system calls: one library call means one system call.\nThe second group doesn't have a standard mapping.\nA library call could be mapped to no system calls, one system call, two or more system calls or it may depend (a system call may or may not happen)."),(0,n.kt)("p",null,"The ",(0,n.kt)("inlineCode",{parentName:"p"},"support/libcall-syscall/")," folder stores the implementation of a simple program that makes different library calls.\nLet's build the program and then trace the library calls (with ",(0,n.kt)("inlineCode",{parentName:"p"},"ltrace"),") and the system calls (with ",(0,n.kt)("inlineCode",{parentName:"p"},"strace"),"):"),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre"},'student@os:~/.../lab/support/libcall-syscall$ make\ncc -Wall   -c -o call.o call.c\ncc   call.o   -o call\ncc -Wall   -c -o call2.o call2.c\ncc   call2.o   -o call2\n\nstudent@os:~/.../lab/support/libcall-syscall$ ltrace ./call\nfopen("a.txt", "wt")                                                                                             = 0x556d57679260\nstrlen("Hello, world!\\n")                                                                                        = 14\nfwrite("Hello, world!\\n", 1, 14, 0x556d57679260)                                                                 = 14\nstrlen("Bye, world!\\n")                                                                                          = 12\nfwrite("Bye, world!\\n", 1, 12, 0x556d57679260)                                                                   = 12\nfflush(0x556d57679260)                                                                                           = 0\n+++ exited (status 0) +++\n\nstudent@os:~/.../lab/support/libcall-syscall$ strace ./call\n[...]\nopenat(AT_FDCWD, "a.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3\nfstat(3, {st_mode=S_IFREG|0664, st_size=0, ...}) = 0\nwrite(3, "Hello, world!\\nBye, world!\\n", 26) = 26\nexit_group(0)                           = ?\n+++ exited with 0 +++\n')),(0,n.kt)("p",null,"We have the following mappings:"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},"The ",(0,n.kt)("inlineCode",{parentName:"li"},"fopen()")," library call invokes the ",(0,n.kt)("inlineCode",{parentName:"li"},"openat")," and the ",(0,n.kt)("inlineCode",{parentName:"li"},"fstat")," system calls."),(0,n.kt)("li",{parentName:"ul"},"The ",(0,n.kt)("inlineCode",{parentName:"li"},"fwrite()")," library call invokes no system calls."),(0,n.kt)("li",{parentName:"ul"},"The ",(0,n.kt)("inlineCode",{parentName:"li"},"strlen()")," library call invokes no system calls."),(0,n.kt)("li",{parentName:"ul"},"The ",(0,n.kt)("inlineCode",{parentName:"li"},"fflush()")," library call invokes the ",(0,n.kt)("inlineCode",{parentName:"li"},"write")," system call.")),(0,n.kt)("p",null,"This all seems to make sense.\nThe main reason for ",(0,n.kt)("inlineCode",{parentName:"p"},"fwrite()")," not making any system calls is the use of a standard C library buffer.\nCalls the ",(0,n.kt)("inlineCode",{parentName:"p"},"fwrite()")," end up writing to that buffer to reduce the number of system calls.\nActual system calls are made either when the standard C library buffer is full or when an ",(0,n.kt)("inlineCode",{parentName:"p"},"fflush()")," library call is made."),(0,n.kt)("h4",{id:"practice"},"Practice"),(0,n.kt)("p",null,"Enter the ",(0,n.kt)("inlineCode",{parentName:"p"},"support/libcall-syscall/")," folder and go through the practice items below."),(0,n.kt)("ol",null,(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},"Check library calls and system calls for the ",(0,n.kt)("inlineCode",{parentName:"p"},"call2.c")," file.\nUse ",(0,n.kt)("inlineCode",{parentName:"p"},"ltrace")," and ",(0,n.kt)("inlineCode",{parentName:"p"},"strace"),"."),(0,n.kt)("p",{parentName:"li"},"Find explanations for the calls being made and the library call to system call mapping."))),(0,n.kt)("p",null,(0,n.kt)("a",{parentName:"p",href:"/operating-systems/Lab/Software-Stack/Libc/quiz/libcall-syscall"},"Quiz")))}m.isMDXComponent=!0}}]);