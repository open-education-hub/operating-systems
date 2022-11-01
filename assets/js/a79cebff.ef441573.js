"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[75252],{3905:(e,t,r)=>{r.d(t,{Zo:()=>p,kt:()=>m});var n=r(67294);function o(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function a(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function i(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?a(Object(r),!0).forEach((function(t){o(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):a(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,o=function(e,t){if(null==e)return{};var r,n,o={},a=Object.keys(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||(o[r]=e[r]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(o[r]=e[r])}return o}var c=n.createContext({}),s=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):i(i({},t),e)),r},p=function(e){var t=s(e.components);return n.createElement(c.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},f=n.forwardRef((function(e,t){var r=e.components,o=e.mdxType,a=e.originalType,c=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),f=s(r),m=o,h=f["".concat(c,".").concat(m)]||f[m]||u[m]||a;return r?n.createElement(h,i(i({ref:t},p),{},{components:r})):n.createElement(h,i({ref:t},p))}));function m(e,t){var r=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=r.length,i=new Array(a);i[0]=f;var l={};for(var c in t)hasOwnProperty.call(t,c)&&(l[c]=t[c]);l.originalType=e,l.mdxType="string"==typeof e?e:o,i[1]=l;for(var s=2;s<a;s++)i[s]=r[s];return n.createElement.apply(null,i)}return n.createElement.apply(null,r)}f.displayName="MDXCreateElement"},43903:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>u,frontMatter:()=>a,metadata:()=>l,toc:()=>s});var n=r(87462),o=(r(67294),r(3905));const a={},i="Who Calls `execve` in the Log of the Parent Process?",l={unversionedId:"Lab/Compute/Copy-on-Write/quiz/who-calls-execve-parent",id:"Lab/Compute/Copy-on-Write/quiz/who-calls-execve-parent",title:"Who Calls `execve` in the Log of the Parent Process?",description:"Question Text",source:"@site/docs/Lab/Compute/Copy-on-Write/quiz/who-calls-execve-parent.md",sourceDirName:"Lab/Compute/Copy-on-Write/quiz",slug:"/Lab/Compute/Copy-on-Write/quiz/who-calls-execve-parent",permalink:"/operating-systems/Lab/Compute/Copy-on-Write/quiz/who-calls-execve-parent",draft:!1,tags:[],version:"current",frontMatter:{}},c={},s=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:s};function u(e){let{components:t,...r}=e;return(0,o.kt)("wrapper",(0,n.Z)({},p,r,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"who-calls-execve-in-the-log-of-the-parent-process"},"Who Calls ",(0,o.kt)("inlineCode",{parentName:"h1"},"execve")," in the Log of the Parent Process?"),(0,o.kt)("h2",{id:"question-text"},"Question Text"),(0,o.kt)("p",null,"Which process calls ",(0,o.kt)("inlineCode",{parentName:"p"},'execve("sleepy_creator", ["sleepy_creator"], ...)'),", that you found in the log of the parent process?"),(0,o.kt)("h2",{id:"question-answers"},"Question Answers"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"The kernel because that's where the loader is located"),(0,o.kt)("li",{parentName:"ul"},"The loader because it is the loader who creates new processes"),(0,o.kt)("li",{parentName:"ul"},"The C runtime because this is the C interpreter")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("inlineCode",{parentName:"li"},"bash")," because we run ",(0,o.kt)("inlineCode",{parentName:"li"},"sleepy_creator")," from terminal, i.e. from ",(0,o.kt)("inlineCode",{parentName:"li"},"bash"))),(0,o.kt)("h2",{id:"feedback"},"Feedback"),(0,o.kt)("p",null,"All processes spawned from the command-line are children of the current ",(0,o.kt)("inlineCode",{parentName:"p"},"bash")," process."))}u.isMDXComponent=!0}}]);