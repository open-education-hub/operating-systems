"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[45801],{3905:(e,t,r)=>{r.d(t,{Zo:()=>c,kt:()=>m});var n=r(67294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function o(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function i(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?o(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function s(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},o=Object.keys(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var p=n.createContext({}),l=function(e){var t=n.useContext(p),r=t;return e&&(r="function"==typeof e?e(t):i(i({},t),e)),r},c=function(e){var t=l(e.components);return n.createElement(p.Provider,{value:t},e.children)},u="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},h=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,o=e.originalType,p=e.parentName,c=s(e,["components","mdxType","originalType","parentName"]),u=l(r),h=a,m=u["".concat(p,".").concat(h)]||u[h]||d[h]||o;return r?n.createElement(m,i(i({ref:t},c),{},{components:r})):n.createElement(m,i({ref:t},c))}));function m(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=r.length,i=new Array(o);i[0]=h;var s={};for(var p in t)hasOwnProperty.call(t,p)&&(s[p]=t[p]);s.originalType=e,s[u]="string"==typeof e?e:a,i[1]=s;for(var l=2;l<o;l++)i[l]=r[l];return n.createElement.apply(null,i)}return n.createElement.apply(null,r)}h.displayName="MDXCreateElement"},17961:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>p,contentTitle:()=>i,default:()=>u,frontMatter:()=>o,metadata:()=>s,toc:()=>l});var n=r(87462),a=(r(67294),r(3905));const o={},i=void 0,s={unversionedId:"Lab/Application-Interaction/Time Server/content/password-cracker",id:"Lab/Application-Interaction/Time Server/content/password-cracker",title:"password-cracker",description:"Password Cracker",source:"@site/docs/Lab/Application-Interaction/Time Server/content/password-cracker.md",sourceDirName:"Lab/Application-Interaction/Time Server/content",slug:"/Lab/Application-Interaction/Time Server/content/password-cracker",permalink:"/operating-systems/Lab/Application-Interaction/Time Server/content/password-cracker",draft:!1,tags:[],version:"current",frontMatter:{}},p={},l=[{value:"Password Cracker",id:"password-cracker",level:2},{value:"Multiprocess Version",id:"multiprocess-version",level:3},{value:"Practice",id:"practice",level:4},{value:"Multithreaded Version",id:"multithreaded-version",level:3},{value:"Multiprocess Version in Python (1)",id:"multiprocess-version-in-python-1",level:3},{value:"Multiprocess Version in Python (2)",id:"multiprocess-version-in-python-2",level:3},{value:"Practice",id:"practice-1",level:4},{value:"Multithreaded Version in Python",id:"multithreaded-version-in-python",level:3}],c={toc:l};function u(e){let{components:t,...r}=e;return(0,a.kt)("wrapper",(0,n.Z)({},c,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h2",{id:"password-cracker"},"Password Cracker"),(0,a.kt)("p",null,"In this example we will solve the following problem: given the sha512 hash of a password, we want to obtain the password that generated the hash."),(0,a.kt)("p",null,"Since a hash function is not reversible, one way to solve this problem is by brute-force: generate all possible word combinations, compute the hash for each word, and compare it with our desired hash value.\nThis is not feasible for long passwords, so for our example we will consider only passwords containing lowercase letters and having the length of 4."),(0,a.kt)("p",null,"In order to speed up the entire process, we want to parallelize the solution.\nInstead of one process checking all combinations, we'll split the work among multiple processes or threads."),(0,a.kt)("h3",{id:"multiprocess-version"},"Multiprocess Version"),(0,a.kt)("p",null,"The code for this version is in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/password-cracker/password-cracker-multiprocess.c"),"."),(0,a.kt)("p",null,"The idea is the following: we create 26 worker processes, where each process will consider passwords that start with one particular letter (the first process will brute-force passwords starting with ",(0,a.kt)("inlineCode",{parentName:"p"},"a"),", second with ",(0,a.kt)("inlineCode",{parentName:"p"},"b"),", and so on)."),(0,a.kt)("p",null,"Since we are using processes, which are naturally isolated, we need a method of communication.\nThe main process should be able to send data to the workers and read back results from them.\nFor this purpose we will use pipes: a pair of 2 pipes between the main process and each worker, one pipe for each direction of communication."),(0,a.kt)("p",null,"In summary, the flow will look like this:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"main process"),(0,a.kt)("ul",{parentName:"li"},(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"create worker processes, along with 2 pipes for each worker (one pipe for requests, one for results)")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"send the 'a' character to the first process request pipe, 'b' to the second, etc.")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"read the results from each result pipe")))),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"worker process"),(0,a.kt)("ul",{parentName:"li"},(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"read one character from the request pipe")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"generate all words of length 4 that begin with that character")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"for each generated word, compute the sha512 hash and compare it with the desired hash")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"if there is a match, write it to the result pipe"))))),(0,a.kt)("p",null,"Let's build and run the program:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../support/password-cracker$ make\ngcc -Wall -o password-cracker-multiprocess password-cracker-multiprocess.c -lcrypto\ngcc -Wall -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -o password-cracker-multithread password-cracker-multithread.c -lcrypto -lpthread\n\nstudent@os:~/.../support/password-cracker$ ./password-cracker-multiprocess\nworker 7 found haxx\n")),(0,a.kt)("h4",{id:"practice"},"Practice"),(0,a.kt)("p",null,"Creating 26 processes is not very realistic, since it's unlikely that a usual machine has that many cores."),(0,a.kt)("p",null,"Modify the program so that it only creates 4 workers.\nEach worker will receive 2 characters instead of one, defining an interval to search.\nFor example, the first worker will receive ",(0,a.kt)("inlineCode",{parentName:"p"},"a")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"f"),", meaning it will brute-force passwords starting with ",(0,a.kt)("inlineCode",{parentName:"p"},"a"),", ",(0,a.kt)("inlineCode",{parentName:"p"},"b"),", ",(0,a.kt)("inlineCode",{parentName:"p"},"c"),", ",(0,a.kt)("inlineCode",{parentName:"p"},"d"),", ",(0,a.kt)("inlineCode",{parentName:"p"},"e"),", or ",(0,a.kt)("inlineCode",{parentName:"p"},"f"),", the second ",(0,a.kt)("inlineCode",{parentName:"p"},"g")," - ",(0,a.kt)("inlineCode",{parentName:"p"},"l"),", and so on."),(0,a.kt)("h3",{id:"multithreaded-version"},"Multithreaded Version"),(0,a.kt)("p",null,"Check out the code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/password-cracker/password-cracker-multithread.c"),"."),(0,a.kt)("p",null,"The core idea of the program is the same, but now we're using threads instead of processes."),(0,a.kt)("p",null,"This makes the communication easier: we'll use the thread function argument to send the first character of the password to each thread.\nAs for the result, each thread will return it as the return value of the thread function."),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../support/password-cracker$ ./password-cracker-multithread\nworker 7 found haxx\n")),(0,a.kt)("h3",{id:"multiprocess-version-in-python-1"},"Multiprocess Version in Python (1)"),(0,a.kt)("p",null,"Code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/password-cracker/python/password-cracker-multiprocess-1.py"),"."),(0,a.kt)("p",null,"This is the Python equivalent of the previous multiprocess version. The program structure is the same, but Python has a few nice features that make our life easier:"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"there is a ",(0,a.kt)("inlineCode",{parentName:"p"},"Process")," object that takes a function argument and spawns a new process that begins execution from that function.\nNo need to call ",(0,a.kt)("inlineCode",{parentName:"p"},"fork")," manually.")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"the ",(0,a.kt)("inlineCode",{parentName:"p"},"Pipe")," object in Python is already bidirectional, unlike the OS pipes, which are unidirectional.\nSo we don't need to create 2 pipes for each direction.")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"we don't have to write the code that generates all the password combinations, ",(0,a.kt)("inlineCode",{parentName:"p"},"itertools.product")," will do it for us"))),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../support/password-cracker$ python3 python/password-cracker-multiprocess-1.py\nworker 7 found haxx\n")),(0,a.kt)("h3",{id:"multiprocess-version-in-python-2"},"Multiprocess Version in Python (2)"),(0,a.kt)("p",null,"Code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/password-cracker/python/password-cracker-multiprocess-2.py"),"."),(0,a.kt)("p",null,"In this case, the code looks different than in the previous examples.\nNow we are taking advantage of some Python constructs, namely ",(0,a.kt)("inlineCode",{parentName:"p"},"process pools"),", which are a collection of worker processes."),(0,a.kt)("p",null,"A ",(0,a.kt)("inlineCode",{parentName:"p"},"Pool")," object has, among others, a function called ",(0,a.kt)("inlineCode",{parentName:"p"},"map"),".\n",(0,a.kt)("inlineCode",{parentName:"p"},"map")," takes a function, together with an array of values, and applies this function on each value from the array.\nAt the first glance it might look like the usual ",(0,a.kt)("inlineCode",{parentName:"p"},"map")," function, but with the key difference that the function application is done by the processes from the pool."),(0,a.kt)("p",null,"In other words, the work is distributed to the worker processes from the pool, and all the communication that we had to handle in the previous examples is done behind the scenes, greatly simplifying the code."),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../support/password-cracker$ python3 python/password-cracker-multiprocess-2.py\nworker 7 found haxx\n")),(0,a.kt)("h4",{id:"practice-1"},"Practice"),(0,a.kt)("p",null,"Check that the ",(0,a.kt)("inlineCode",{parentName:"p"},"worker")," function is indeed called from different worker processes.\nOne simple way to do this is to print out the current process ID at the beginning of the function.\nTo get the current process ID, use the ",(0,a.kt)("inlineCode",{parentName:"p"},"getpid")," function from the ",(0,a.kt)("inlineCode",{parentName:"p"},"os")," module."),(0,a.kt)("h3",{id:"multithreaded-version-in-python"},"Multithreaded Version in Python"),(0,a.kt)("p",null,"Code in ",(0,a.kt)("inlineCode",{parentName:"p"},"support/password-cracker/python/password-cracker-multithread.py"),"."),(0,a.kt)("p",null,"The Python equivalent of the previous multithreaded version."),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../support/password-cracker$ python3 python/password-cracker-multithread.py\nworker 7 found haxx\n")),(0,a.kt)("p",null,"This example is given only to provide an idea of how a multithreaded program is written.\nRemember that CPU-bound threads in python don't actually run in parallel, due to the Global Interpreter Lock."))}u.isMDXComponent=!0}}]);