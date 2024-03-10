"use strict";(self.webpackChunkos=self.webpackChunkos||[]).push([[2213],{5680:(e,t,n)=>{n.d(t,{xA:()=>u,yg:()=>d});var a=n(6540);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function l(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},i=Object.keys(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var s=a.createContext({}),p=function(e){var t=a.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):l(l({},t),e)),n},u=function(e){var t=p(e.components);return a.createElement(s.Provider,{value:t},e.children)},h="mdxType",c={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},m=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,i=e.originalType,s=e.parentName,u=o(e,["components","mdxType","originalType","parentName"]),h=p(n),m=r,d=h["".concat(s,".").concat(m)]||h[m]||c[m]||i;return n?a.createElement(d,l(l({ref:t},u),{},{components:n})):a.createElement(d,l({ref:t},u))}));function d(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var i=n.length,l=new Array(i);l[0]=m;var o={};for(var s in t)hasOwnProperty.call(t,s)&&(o[s]=t[s]);o.originalType=e,o[h]="string"==typeof e?e:r,l[1]=o;for(var p=2;p<i;p++)l[p]=n[p];return a.createElement.apply(null,l)}return a.createElement.apply(null,n)}m.displayName="MDXCreateElement"},6139:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>l,default:()=>c,frontMatter:()=>i,metadata:()=>o,toc:()=>p});var a=n(8168),r=(n(6540),n(5680));const i={},l="Minishell",o={unversionedId:"Assignments/Mini Shell/README",id:"Assignments/Mini Shell/README",title:"Minishell",description:"Objectives",source:"@site/docs/Assignments/Mini Shell/README.md",sourceDirName:"Assignments/Mini Shell",slug:"/Assignments/Mini Shell/",permalink:"/operating-systems/Assignments/Mini Shell/",draft:!1,tags:[],version:"current",frontMatter:{},sidebar:"sidebar",previous:{title:"Parallel Graph",permalink:"/operating-systems/Assignments/Parallel Graph/"},next:{title:"Asynchronous Web Server",permalink:"/operating-systems/Assignments/Asynchronous Web Server/"}},s={},p=[{value:"Objectives",id:"objectives",level:2},{value:"Statement",id:"statement",level:2},{value:"Introduction",id:"introduction",level:3},{value:"Shell Functionalities",id:"shell-functionalities",level:3},{value:"Changing the Current Directory",id:"changing-the-current-directory",level:4},{value:"Closing the Shell",id:"closing-the-shell",level:4},{value:"Running an Application",id:"running-an-application",level:4},{value:"Environment Variables",id:"environment-variables",level:4},{value:"Operators",id:"operators",level:4},{value:"Sequential Operator",id:"sequential-operator",level:5},{value:"Parallel Operator",id:"parallel-operator",level:5},{value:"Pipe Operator",id:"pipe-operator",level:5},{value:"Chain Operators for Conditional Execution",id:"chain-operators-for-conditional-execution",level:5},{value:"Operator Priority",id:"operator-priority",level:5},{value:"I/O Redirection",id:"io-redirection",level:4},{value:"Testing",id:"testing",level:2},{value:"Debug",id:"debug",level:3},{value:"Memory leaks",id:"memory-leaks",level:3},{value:"Checkpatch",id:"checkpatch",level:3}],u={toc:p},h="wrapper";function c(e){let{components:t,...n}=e;return(0,r.yg)(h,(0,a.A)({},u,n,{components:t,mdxType:"MDXLayout"}),(0,r.yg)("h1",{id:"minishell"},"Minishell"),(0,r.yg)("h2",{id:"objectives"},"Objectives"),(0,r.yg)("ul",null,(0,r.yg)("li",{parentName:"ul"},"Learn how shells create new child processes and connect the I/O to the terminal."),(0,r.yg)("li",{parentName:"ul"},"Gain a better understanding of the ",(0,r.yg)("inlineCode",{parentName:"li"},"fork()")," function wrapper."),(0,r.yg)("li",{parentName:"ul"},"Learn to correctly execute commands written by the user and treat errors.")),(0,r.yg)("h2",{id:"statement"},"Statement"),(0,r.yg)("h3",{id:"introduction"},"Introduction"),(0,r.yg)("p",null,"A shell is a command-line interpreter that provides a text-based user interface for operating systems.\nBash is both an interactive command language and a scripting language.\nIt is used to interact with the file system, applications, operating system and more."),(0,r.yg)("p",null,"For this assignment you will build a Bash-like shell with minimal functionalities like traversing the file system, running applications, redirecting their output or piping the output from one application into the input of another.\nThe details of the functionalities that must be implemented will be further explained."),(0,r.yg)("h3",{id:"shell-functionalities"},"Shell Functionalities"),(0,r.yg)("h4",{id:"changing-the-current-directory"},"Changing the Current Directory"),(0,r.yg)("p",null,"The shell will support a built-in command for navigating the file system, called ",(0,r.yg)("inlineCode",{parentName:"p"},"cd"),".\nTo implement this feature you will need to store the current directory path because the user can provide either relative or absolute paths as arguments to the ",(0,r.yg)("inlineCode",{parentName:"p"},"cd")," command."),(0,r.yg)("p",null,"The built-in ",(0,r.yg)("inlineCode",{parentName:"p"},"pwd")," command will show the current directory path."),(0,r.yg)("p",null,"Check the following examples below to understand these functionalities."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},"> pwd\n/home/student\n> cd operating-systems/assignments/minishell\n> pwd\n/home/student/operating-systems/assignments/minishell\n> cd inexitent\nno such file or directory\n> cd /usr/lib\n> pwd\n/usr/lib\n")),(0,r.yg)("blockquote",null,(0,r.yg)("p",{parentName:"blockquote"},(0,r.yg)("strong",{parentName:"p"},(0,r.yg)("em",{parentName:"strong"},"NOTE:"))," Using the ",(0,r.yg)("inlineCode",{parentName:"p"},"cd")," command without any arguments or with more than one argument doesn't affect the current directory path.\nMake sure this edge case is handled in a way that prevents crashes.")),(0,r.yg)("h4",{id:"closing-the-shell"},"Closing the Shell"),(0,r.yg)("p",null,"Inputting either ",(0,r.yg)("inlineCode",{parentName:"p"},"quit")," or ",(0,r.yg)("inlineCode",{parentName:"p"},"exit")," should close the minishell."),(0,r.yg)("h4",{id:"running-an-application"},"Running an Application"),(0,r.yg)("p",null,"Suppose you have an executable named ",(0,r.yg)("inlineCode",{parentName:"p"},"sum")," in the current directory.\nIt takes arbitrarily many numbers as arguments and prints their sum to ",(0,r.yg)("inlineCode",{parentName:"p"},"stdout"),".\nThe following example shows how the minishell implemented by you should behave."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},"> ./sum 2 4 1\n7\n")),(0,r.yg)("p",null,"If the executable is located at the ",(0,r.yg)("inlineCode",{parentName:"p"},"/home/student/sum")," absolute path, the following example should also be valid."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},"> /home/student/sum 2 4 1\n7\n")),(0,r.yg)("p",null,"Each application will run in a separate child process of the minishell created using ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/fork.2.html"},"fork"),"."),(0,r.yg)("h4",{id:"environment-variables"},"Environment Variables"),(0,r.yg)("p",null,"Your shell will support using environment variables.\nThe environment variables will be initially inherited from the ",(0,r.yg)("inlineCode",{parentName:"p"},"bash")," process that started your minishell application."),(0,r.yg)("p",null,"If an undefined variable is used, its value is the empty string: ",(0,r.yg)("inlineCode",{parentName:"p"},'""'),"."),(0,r.yg)("blockquote",null,(0,r.yg)("p",{parentName:"blockquote"},(0,r.yg)("strong",{parentName:"p"},(0,r.yg)("em",{parentName:"strong"},"NOTE:"))," The following examples contain comments which don't need to be supported by the minishell.\nThey are present here only to give a better understanding of the minishell's functionalities.")),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'> NAME="John Doe"                    # Will assign the value "John Doe" to the NAME variable\n> AGE=27                             # Will assign the value 27 to the AGE variable\n> ./identify $NAME $LOCATION $AGE    # Will translate to ./identify "John Doe" "" 27 because $LOCATION is not defined\n')),(0,r.yg)("p",null,"A variable can be assigned to another variable."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},"> OLD_NAME=$NAME    # Will assign the value of the NAME variable to OLD_NAME\n")),(0,r.yg)("h4",{id:"operators"},"Operators"),(0,r.yg)("h5",{id:"sequential-operator"},"Sequential Operator"),(0,r.yg)("p",null,"By using the ",(0,r.yg)("inlineCode",{parentName:"p"},";")," operator, you can chain multiple commands that will run sequentially, one after another.\nIn the command ",(0,r.yg)("inlineCode",{parentName:"p"},"expr1; expr2")," it is guaranteed that ",(0,r.yg)("inlineCode",{parentName:"p"},"expr1")," will finish before ",(0,r.yg)("inlineCode",{parentName:"p"},"expr2")," is be evaluated."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'> echo "Hello"; echo "world!"; echo "Bye!"\nHello\nworld!\nBye!\n')),(0,r.yg)("h5",{id:"parallel-operator"},"Parallel Operator"),(0,r.yg)("p",null,"By using the ",(0,r.yg)("inlineCode",{parentName:"p"},"&")," operator you can chain multiple commands that will run in parallel.\nWhen running the command ",(0,r.yg)("inlineCode",{parentName:"p"},"expr1 & expr2"),", both expressions are evaluated at the same time (by different processes).\nThe order in which the two commands finish is not guaranteed."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'> echo "Hello" & echo "world!" & echo "Bye!"  # The words may be printed in any order\nworld!\nBye!\nHello\n')),(0,r.yg)("h5",{id:"pipe-operator"},"Pipe Operator"),(0,r.yg)("p",null,"With the ",(0,r.yg)("inlineCode",{parentName:"p"},"|")," operator you can chain multiple commands so that the standard output of the first command is redirected to the standard input of the second command."),(0,r.yg)("p",null,"Hint: Look into ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/pipe.2.html"},"anonymous pipes")," and file descriptor inheritance while using ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/fork.2.html"},"fork"),"."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'> echo "Bye"                      # command outputs "Bye"\nBye\n> ./reverse_input\nHello                             # command reads input "Hello"\nolleH                             # outputs the reversed string "olleH"\n> echo "world" | ./reverse_input  # the output generated by the echo command will be used as input for the reverse_input executable\ndlrow\n')),(0,r.yg)("h5",{id:"chain-operators-for-conditional-execution"},"Chain Operators for Conditional Execution"),(0,r.yg)("p",null,"The ",(0,r.yg)("inlineCode",{parentName:"p"},"&&")," operator allows chaining commands that are executed sequentially, from left to right.\nThe chain of execution stops at the first command ",(0,r.yg)("strong",{parentName:"p"},"that exits with an error (return code not 0)"),"."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'# throw_error always exits with a return code different than 0 and outputs to stderr "ERROR: I always fail"\n> echo "H" && echo "e" && echo "l" && ./throw_error && echo "l" && echo "o"\nH\ne\nl\nERROR: I always fail\n')),(0,r.yg)("p",null,"The ",(0,r.yg)("inlineCode",{parentName:"p"},"||")," operator allows chaining commands that are executed sequentially, from left to right.\nThe chain of execution stops at the first command ",(0,r.yg)("strong",{parentName:"p"},"that exits successfully (return code is 0)"),"."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},'# throw_error always exits with a return code different than 0 and outputs to stderr "ERROR: I always fail"\n> ./throw_error || ./throw_error || echo "Hello" || echo "world!" || echo "Bye!"\nERROR: I always fail\nERROR: I always fail\nHello\n')),(0,r.yg)("h5",{id:"operator-priority"},"Operator Priority"),(0,r.yg)("p",null,"The priority of the available operators is the following.\nThe lower the number, the ",(0,r.yg)("strong",{parentName:"p"},"higher")," the priority:"),(0,r.yg)("ol",null,(0,r.yg)("li",{parentName:"ol"},"Pipe operator (",(0,r.yg)("inlineCode",{parentName:"li"},"|"),")"),(0,r.yg)("li",{parentName:"ol"},"Conditional execution operators (",(0,r.yg)("inlineCode",{parentName:"li"},"&&")," or ",(0,r.yg)("inlineCode",{parentName:"li"},"||"),")"),(0,r.yg)("li",{parentName:"ol"},"Parallel operator (",(0,r.yg)("inlineCode",{parentName:"li"},"&"),")"),(0,r.yg)("li",{parentName:"ol"},"Sequential operator (",(0,r.yg)("inlineCode",{parentName:"li"},";"),")")),(0,r.yg)("h4",{id:"io-redirection"},"I/O Redirection"),(0,r.yg)("p",null,"The shell must support the following redirection options:"),(0,r.yg)("ul",null,(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},"< filename")," - redirects ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")," to standard input"),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},"> filename")," - redirects standard output to ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},"2> filename")," - redirects standard error to ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},"&> filename")," - redirects standard output and standard error to ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},">> filename")," - redirects standard output to ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")," in append mode"),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("inlineCode",{parentName:"li"},"2>> filename")," - redirects standard error to ",(0,r.yg)("inlineCode",{parentName:"li"},"filename")," in append mode")),(0,r.yg)("p",null,"Hint: Look into ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/open.2.html"},"open"),", ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/dup.2.html"},"dup2")," and ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/close.2.html"},"close"),"."),(0,r.yg)("h2",{id:"testing"},"Testing"),(0,r.yg)("p",null,"The testing is automated.\nTests are located in the ",(0,r.yg)("inlineCode",{parentName:"p"},"inputs/")," directory."),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../assignments/minishell/checker/_test/inputs$ ls -F\ntest_01.txt  test_03.txt  test_05.txt  test_07.txt  test_09.txt  test_11.txt  test_13.txt  test_15.txt  test_17.txt\ntest_02.txt  test_04.txt  test_06.txt  test_08.txt  test_10.txt  test_12.txt  test_14.txt  test_16.txt  test_18.txt\n")),(0,r.yg)("p",null,"To execute tests you need to run:"),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../assignments/minishell/checker$ ./run_all.sh\n")),(0,r.yg)("h3",{id:"debug"},"Debug"),(0,r.yg)("p",null,"To inspect the differences between the output of the mini-shell and the reference binary set ",(0,r.yg)("inlineCode",{parentName:"p"},"DO_CLEANUP=no")," in ",(0,r.yg)("inlineCode",{parentName:"p"},"_test/run_test.sh"),".\nTo see the results of the tests, you can check ",(0,r.yg)("inlineCode",{parentName:"p"},"_test/outputs/")," directory."),(0,r.yg)("h3",{id:"memory-leaks"},"Memory leaks"),(0,r.yg)("p",null,"To inspect the unreleased resources (memory leaks, file descriptors) set ",(0,r.yg)("inlineCode",{parentName:"p"},"USE_VALGRIND=yes")," and ",(0,r.yg)("inlineCode",{parentName:"p"},"DO_CLEANUP=no")," in ",(0,r.yg)("inlineCode",{parentName:"p"},"_test/run_test.sh"),".\nYou can modify both the path to the Valgrind log file and the command parameters.\nTo see the results of the tests, you can check ",(0,r.yg)("inlineCode",{parentName:"p"},"_test/outputs/")," directory."),(0,r.yg)("h3",{id:"checkpatch"},"Checkpatch"),(0,r.yg)("p",null,(0,r.yg)("inlineCode",{parentName:"p"},"checkpatch.pl")," is a script used in the development of the Linux kernel.\nIt is used to check patches that are submitted to the kernel mailing list for adherence to the coding style guidelines of the Linux kernel."),(0,r.yg)("p",null,"The script checks the code for common coding style issues, such as indentation, spacing, line length, function and variable naming conventions, and other formatting rules.\nIt also checks for some common errors, such as uninitialized variables, memory leaks, and other potential bugs."),(0,r.yg)("p",null,"You can ",(0,r.yg)("a",{parentName:"p",href:"https://github.com/torvalds/linux/blob/master/scripts/checkpatch.pl"},"download")," the ",(0,r.yg)("inlineCode",{parentName:"p"},"checkpatch.pl")," script from the official Linux kernel repository."),(0,r.yg)("p",null,"Running the following command will show you linting warnings and errors:"),(0,r.yg)("pre",null,(0,r.yg)("code",{parentName:"pre",className:"language-sh"},"./checkpatch.pl --no-tree --terse -f /path/to/your/code.c\n")))}c.isMDXComponent=!0}}]);