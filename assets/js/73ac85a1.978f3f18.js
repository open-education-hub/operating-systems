"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[1532],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>k});var a=n(67294);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function l(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?l(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):l(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function s(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},l=Object.keys(e);for(a=0;a<l.length;a++)n=l[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);for(a=0;a<l.length;a++)n=l[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var o=a.createContext({}),u=function(e){var t=a.useContext(o),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},c=function(e){var t=u(e.components);return a.createElement(o.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},d=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,l=e.originalType,o=e.parentName,c=s(e,["components","mdxType","originalType","parentName"]),d=u(n),k=r,m=d["".concat(o,".").concat(k)]||d[k]||p[k]||l;return n?a.createElement(m,i(i({ref:t},c),{},{components:n})):a.createElement(m,i({ref:t},c))}));function k(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var l=n.length,i=new Array(l);i[0]=d;var s={};for(var o in t)hasOwnProperty.call(t,o)&&(s[o]=t[o]);s.originalType=e,s.mdxType="string"==typeof e?e:r,i[1]=s;for(var u=2;u<l;u++)i[u]=n[u];return a.createElement.apply(null,i)}return a.createElement.apply(null,n)}d.displayName="MDXCreateElement"},15991:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>o,contentTitle:()=>i,default:()=>p,frontMatter:()=>l,metadata:()=>s,toc:()=>u});var a=n(87462),r=(n(67294),n(3905));const l={},i="Syscall ID",s={unversionedId:"Lab/Software-Stack/Static-dynamic/quiz/syscalls",id:"Lab/Software-Stack/Static-dynamic/quiz/syscalls",title:"Syscall ID",description:"Question Text",source:"@site/docs/Lab/Software-Stack/Static-dynamic/quiz/syscalls.md",sourceDirName:"Lab/Software-Stack/Static-dynamic/quiz",slug:"/Lab/Software-Stack/Static-dynamic/quiz/syscalls",permalink:"/operating-systems/Lab/Software-Stack/Static-dynamic/quiz/syscalls",draft:!1,tags:[],version:"current",frontMatter:{}},o={},u=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2},{value:"Question Text",id:"question-text-1",level:2},{value:"Question Answers",id:"question-answers-1",level:2},{value:"Feedback",id:"feedback-1",level:2},{value:"Question Text",id:"question-text-2",level:2},{value:"Question Answers",id:"question-answers-2",level:2},{value:"Feedback",id:"feedback-2",level:2}],c={toc:u};function p(e){let{components:t,...n}=e;return(0,r.kt)("wrapper",(0,a.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,r.kt)("h1",{id:"syscall-id"},"Syscall ID"),(0,r.kt)("h2",{id:"question-text"},"Question Text"),(0,r.kt)("p",null,"What register stores the system call ID on x86_64?"),(0,r.kt)("h2",{id:"question-answers"},"Question Answers"),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"RIP")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"RSP"))),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"RAX"))),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"RDX"))),(0,r.kt)("h2",{id:"feedback"},"Feedback"),(0,r.kt)("p",null,(0,r.kt)("inlineCode",{parentName:"p"},"RAX")," is the register used for passing the syscall ID and the result code."),(0,r.kt)("h1",{id:"syscall-tool"},"Syscall Tool"),(0,r.kt)("h2",{id:"question-text-1"},"Question Text"),(0,r.kt)("p",null,"What tool do we use to capture system calls?"),(0,r.kt)("h2",{id:"question-answers-1"},"Question Answers"),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"strace"))),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"make")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"gcc")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("inlineCode",{parentName:"li"},"./exec"))),(0,r.kt)("h2",{id:"feedback-1"},"Feedback"),(0,r.kt)("p",null,(0,r.kt)("inlineCode",{parentName:"p"},"strace")," is used to trace system calls invoked by a running program."),(0,r.kt)("h1",{id:"syscall-numbers"},"Syscall Numbers"),(0,r.kt)("h2",{id:"question-text-2"},"Question Text"),(0,r.kt)("p",null,"What is the approximate number of system call numbers in Linux?"),(0,r.kt)("h2",{id:"question-answers-2"},"Question Answers"),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},"3"),(0,r.kt)("li",{parentName:"ul"},"30")),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},"300")),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},"3000")),(0,r.kt)("h2",{id:"feedback-2"},"Feedback"),(0,r.kt)("p",null,"As show ",(0,r.kt)("a",{parentName:"p",href:"https://x64.syscall.sh/"},"here"),", they're about 300 system calls in Linux."))}p.isMDXComponent=!0}}]);