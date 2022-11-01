"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[13090],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>f});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function u(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var i=r.createContext({}),s=function(e){var t=r.useContext(i),n=t;return e&&(n="function"==typeof e?e(t):u(u({},t),e)),n},c=function(e){var t=s(e.components);return r.createElement(i.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},m=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,i=e.parentName,c=l(e,["components","mdxType","originalType","parentName"]),m=s(n),f=a,d=m["".concat(i,".").concat(f)]||m[f]||p[f]||o;return n?r.createElement(d,u(u({ref:t},c),{},{components:n})):r.createElement(d,u({ref:t},c))}));function f(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,u=new Array(o);u[0]=m;var l={};for(var i in t)hasOwnProperty.call(t,i)&&(l[i]=t[i]);l.originalType=e,l.mdxType="string"==typeof e?e:a,u[1]=l;for(var s=2;s<o;s++)u[s]=n[s];return r.createElement.apply(null,u)}return r.createElement.apply(null,n)}m.displayName="MDXCreateElement"},31831:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>i,contentTitle:()=>u,default:()=>p,frontMatter:()=>o,metadata:()=>l,toc:()=>s});var r=n(87462),a=(n(67294),n(3905));const o={},u="Number of RUNNING User-Level Threads",l={unversionedId:"Lab/Compute/Arena/quiz/number-of-running-ults",id:"Lab/Compute/Arena/quiz/number-of-running-ults",title:"Number of RUNNING User-Level Threads",description:"Question Text",source:"@site/docs/Lab/Compute/Arena/quiz/number-of-running-ults.md",sourceDirName:"Lab/Compute/Arena/quiz",slug:"/Lab/Compute/Arena/quiz/number-of-running-ults",permalink:"/operating-systems/Lab/Compute/Arena/quiz/number-of-running-ults",draft:!1,tags:[],version:"current",frontMatter:{}},i={},s=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],c={toc:s};function p(e){let{components:t,...n}=e;return(0,a.kt)("wrapper",(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"number-of-running-user-level-threads"},"Number of RUNNING User-Level Threads"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"How many threads can be RUNNING simultaneously if we only create them using the API exposed by ",(0,a.kt)("inlineCode",{parentName:"p"},"libult.so"),"? "),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"Equal to the number of cores on the CPU")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"1")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"None"),(0,a.kt)("li",{parentName:"ul"},"2: the main thread and another one for the created threads")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"Only kernel-level threads can run in parallel.\nSince all ",(0,a.kt)("inlineCode",{parentName:"p"},"libult.so")," threads are user-level threads, they run within the same kernel-level thread, so only one of them can run at any time."))}p.isMDXComponent=!0}}]);