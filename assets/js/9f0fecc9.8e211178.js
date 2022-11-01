"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[50325],{3905:(e,t,n)=>{n.d(t,{Zo:()=>s,kt:()=>m});var r=n(67294);function l(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function a(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?a(Object(n),!0).forEach((function(t){l(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):a(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function o(e,t){if(null==e)return{};var n,r,l=function(e,t){if(null==e)return{};var n,r,l={},a=Object.keys(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||(l[n]=e[n]);return l}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(l[n]=e[n])}return l}var c=r.createContext({}),u=function(e){var t=r.useContext(c),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},s=function(e){var t=u(e.components);return r.createElement(c.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,l=e.mdxType,a=e.originalType,c=e.parentName,s=o(e,["components","mdxType","originalType","parentName"]),d=u(n),m=l,f=d["".concat(c,".").concat(m)]||d[m]||p[m]||a;return n?r.createElement(f,i(i({ref:t},s),{},{components:n})):r.createElement(f,i({ref:t},s))}));function m(e,t){var n=arguments,l=t&&t.mdxType;if("string"==typeof e||l){var a=n.length,i=new Array(a);i[0]=d;var o={};for(var c in t)hasOwnProperty.call(t,c)&&(o[c]=t[c]);o.originalType=e,o.mdxType="string"==typeof e?e:l,i[1]=o;for(var u=2;u<a;u++)i[u]=n[u];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},57159:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>p,frontMatter:()=>a,metadata:()=>o,toc:()=>u});var r=n(87462),l=(n(67294),n(3905));const a={},i="malloc",o={unversionedId:"Lab/Software-Stack/Lybcall-Syscall/quiz/libc",id:"Lab/Software-Stack/Lybcall-Syscall/quiz/libc",title:"malloc",description:"Question Text",source:"@site/docs/Lab/Software-Stack/Lybcall-Syscall/quiz/libc.md",sourceDirName:"Lab/Software-Stack/Lybcall-Syscall/quiz",slug:"/Lab/Software-Stack/Lybcall-Syscall/quiz/libc",permalink:"/operating-systems/Lab/Software-Stack/Lybcall-Syscall/quiz/libc",draft:!1,tags:[],version:"current",frontMatter:{}},c={},u=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2},{value:"Question Text",id:"question-text-1",level:2},{value:"Question Answers",id:"question-answers-1",level:2},{value:"Feedback",id:"feedback-1",level:2}],s={toc:u};function p(e){let{components:t,...n}=e;return(0,l.kt)("wrapper",(0,r.Z)({},s,n,{components:t,mdxType:"MDXLayout"}),(0,l.kt)("h1",{id:"malloc"},"malloc"),(0,l.kt)("h2",{id:"question-text"},"Question Text"),(0,l.kt)("p",null,"What system calls are invoked by the ",(0,l.kt)("inlineCode",{parentName:"p"},"malloc()")," library call for Linux libc? (choose 2 answers)"),(0,l.kt)("h2",{id:"question-answers"},"Question Answers"),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},(0,l.kt)("inlineCode",{parentName:"li"},"brk"))),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},(0,l.kt)("inlineCode",{parentName:"li"},"free")),(0,l.kt)("li",{parentName:"ul"},(0,l.kt)("inlineCode",{parentName:"li"},"dup"))),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},(0,l.kt)("inlineCode",{parentName:"li"},"mmap"))),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},(0,l.kt)("inlineCode",{parentName:"li"},"copy"))),(0,l.kt)("h2",{id:"feedback"},"Feedback"),(0,l.kt)("p",null,"Depending on the allocation size, ",(0,l.kt)("inlineCode",{parentName:"p"},"malloc()")," invokes ",(0,l.kt)("inlineCode",{parentName:"p"},"brk")," or ",(0,l.kt)("inlineCode",{parentName:"p"},"mmap"),"."),(0,l.kt)("h1",{id:"syscall-tool"},"Syscall Tool"),(0,l.kt)("h2",{id:"question-text-1"},"Question Text"),(0,l.kt)("p",null,"Which of following is ",(0,l.kt)("strong",{parentName:"p"},"not")," and advantage of using libc for programs?"),(0,l.kt)("h2",{id:"question-answers-1"},"Question Answers"),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},"increased portability")),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},"reduced executable size")),(0,l.kt)("ul",null,(0,l.kt)("li",{parentName:"ul"},"richer set of features"),(0,l.kt)("li",{parentName:"ul"},"easier development")),(0,l.kt)("h2",{id:"feedback-1"},"Feedback"),(0,l.kt)("p",null,"When using libc, because we add a new software component, the size of the resulting executable increases."))}p.isMDXComponent=!0}}]);