"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[43506],{3905:(e,t,n)=>{n.d(t,{Zo:()=>p,kt:()=>m});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function l(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function i(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),c=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):l(l({},t),e)),n},p=function(e){var t=c(e.components);return r.createElement(s.Provider,{value:t},e.children)},u="mdxType",f={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,p=i(e,["components","mdxType","originalType","parentName"]),u=c(n),d=a,m=u["".concat(s,".").concat(d)]||u[d]||f[d]||o;return n?r.createElement(m,l(l({ref:t},p),{},{components:n})):r.createElement(m,l({ref:t},p))}));function m(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,l=new Array(o);l[0]=d;var i={};for(var s in t)hasOwnProperty.call(t,s)&&(i[s]=t[s]);i.originalType=e,i[u]="string"==typeof e?e:a,l[1]=i;for(var c=2;c<o;c++)l[c]=n[c];return r.createElement.apply(null,l)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},87938:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>l,default:()=>u,frontMatter:()=>o,metadata:()=>i,toc:()=>c});var r=n(87462),a=(n(67294),n(3905));const o={},l="Syscall Used by `fopen()`",i={unversionedId:"Lab/I/O/Local I/O in Action/quiz/fopen-syscall",id:"Lab/I/O/Local I/O in Action/quiz/fopen-syscall",title:"Syscall Used by `fopen()`",description:"Question Text",source:"@site/docs/Lab/I/O/Local I/O in Action/quiz/fopen-syscall.md",sourceDirName:"Lab/I/O/Local I/O in Action/quiz",slug:"/Lab/I/O/Local I/O in Action/quiz/fopen-syscall",permalink:"/operating-systems/Lab/I/O/Local I/O in Action/quiz/fopen-syscall",draft:!1,tags:[],version:"current",frontMatter:{}},s={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedaback",id:"feedaback",level:2}],p={toc:c};function u(e){let{components:t,...n}=e;return(0,a.kt)("wrapper",(0,r.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"syscall-used-by-fopen"},"Syscall Used by ",(0,a.kt)("inlineCode",{parentName:"h1"},"fopen()")),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"Use ",(0,a.kt)("inlineCode",{parentName:"p"},"strace")," to determine the syscall called by ",(0,a.kt)("inlineCode",{parentName:"p"},"fopen()")," to access the file.\nWhich one is it?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"read()"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"openat()"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},(0,a.kt)("inlineCode",{parentName:"p"},"write()"))),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},(0,a.kt)("inlineCode",{parentName:"p"},"fstat()")))),(0,a.kt)("h2",{id:"feedaback"},"Feedaback"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},'student@os:~/.../lab/support/simple-file-handling$ strace ./file_operations\n[...]\nopenat(AT_FDCWD, "file.txt", O_RDONLY)  = 3\nfstat(3, {st_mode=S_IFREG|0664, st_size=11, ...}) = 0\nread(3, "C was here!", 4096)            = 11\n[...]\n')),(0,a.kt)("p",null,"So ",(0,a.kt)("inlineCode",{parentName:"p"},"fopen()"),"'s (main) underlying syscall is ",(0,a.kt)("inlineCode",{parentName:"p"},"openat()"),"."))}u.isMDXComponent=!0}}]);