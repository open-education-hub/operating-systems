"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[76438],{3905:(e,t,n)=>{n.d(t,{Zo:()=>u,kt:()=>d});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function l(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?l(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):l(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},l=Object.keys(e);for(r=0;r<l.length;r++)n=l[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);for(r=0;r<l.length;r++)n=l[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var c=r.createContext({}),s=function(e){var t=r.useContext(c),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},u=function(e){var t=s(e.components);return r.createElement(c.Provider,{value:t},e.children)},p="mdxType",f={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},m=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,l=e.originalType,c=e.parentName,u=o(e,["components","mdxType","originalType","parentName"]),p=s(n),m=a,d=p["".concat(c,".").concat(m)]||p[m]||f[m]||l;return n?r.createElement(d,i(i({ref:t},u),{},{components:n})):r.createElement(d,i({ref:t},u))}));function d(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var l=n.length,i=new Array(l);i[0]=m;var o={};for(var c in t)hasOwnProperty.call(t,c)&&(o[c]=t[c]);o.originalType=e,o[p]="string"==typeof e?e:a,i[1]=o;for(var s=2;s<l;s++)i[s]=n[s];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}m.displayName="MDXCreateElement"},54836:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>p,frontMatter:()=>l,metadata:()=>o,toc:()=>s});var r=n(87462),a=(n(67294),n(3905));const l={},i="Effect of `execve()` Syscall",o={unversionedId:"Lab/I/O/Client-Server Model/quiz/execve",id:"Lab/I/O/Client-Server Model/quiz/execve",title:"Effect of `execve()` Syscall",description:"Question Text",source:"@site/docs/Lab/I/O/Client-Server Model/quiz/execve.md",sourceDirName:"Lab/I/O/Client-Server Model/quiz",slug:"/Lab/I/O/Client-Server Model/quiz/execve",permalink:"/operating-systems/Lab/I/O/Client-Server Model/quiz/execve",draft:!1,tags:[],version:"current",frontMatter:{}},c={},s=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],u={toc:s};function p(e){let{components:t,...n}=e;return(0,a.kt)("wrapper",(0,r.Z)({},u,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"effect-of-execve-syscall"},"Effect of ",(0,a.kt)("inlineCode",{parentName:"h1"},"execve()")," Syscall"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"What is the effect of the ",(0,a.kt)("inlineCode",{parentName:"p"},"execve()")," syscall?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"it spawns a new process as the child of the current one")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"it executes a given shell command"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"it replaces the VAS of the current process with that of the file given as argument")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"it spawns a new shell and executes the given command")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"The ",(0,a.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/execve.2.html"},(0,a.kt)("inlineCode",{parentName:"a"},"man")," page")," says it all:"),(0,a.kt)("blockquote",null,(0,a.kt)("p",{parentName:"blockquote"},"execve() executes the program referred to by pathname.  This\ncauses the program that is currently being run by the calling\nprocess to be replaced with a new program, with newly initialized\nstack, heap, and (initialized and uninitialized) data segments.")),(0,a.kt)("p",null,"Simply put, we can say that ",(0,a.kt)("inlineCode",{parentName:"p"},"execve()")," replaces the VAS of the current process with that of the program given as argument."))}p.isMDXComponent=!0}}]);