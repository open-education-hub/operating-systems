"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[45316],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>f});var r=n(67294);function i(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function l(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){i(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function a(e,t){if(null==e)return{};var n,r,i=function(e,t){if(null==e)return{};var n,r,i={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(i[n]=e[n]);return i}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var u=r.createContext({}),s=function(e){var t=r.useContext(u),n=t;return e&&(n="function"==typeof e?e(t):l(l({},t),e)),n},c=function(e){var t=s(e.components);return r.createElement(u.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,i=e.mdxType,o=e.originalType,u=e.parentName,c=a(e,["components","mdxType","originalType","parentName"]),d=s(n),f=i,m=d["".concat(u,".").concat(f)]||d[f]||p[f]||o;return n?r.createElement(m,l(l({ref:t},c),{},{components:n})):r.createElement(m,l({ref:t},c))}));function f(e,t){var n=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var o=n.length,l=new Array(o);l[0]=d;var a={};for(var u in t)hasOwnProperty.call(t,u)&&(a[u]=t[u]);a.originalType=e,a.mdxType="string"==typeof e?e:i,l[1]=a;for(var s=2;s<o;s++)l[s]=n[s];return r.createElement.apply(null,l)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},25296:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>u,contentTitle:()=>l,default:()=>p,frontMatter:()=>o,metadata:()=>a,toc:()=>s});var r=n(87462),i=(n(67294),n(3905));const o={},l="Type of Scheduler in `libult.so`",a={unversionedId:"Lab/Compute/Benchmarks/quiz/type-of-scheduler-in-libult",id:"Lab/Compute/Benchmarks/quiz/type-of-scheduler-in-libult",title:"Type of Scheduler in `libult.so`",description:"Question Text",source:"@site/docs/Lab/Compute/Benchmarks/quiz/type-of-scheduler-in-libult.md",sourceDirName:"Lab/Compute/Benchmarks/quiz",slug:"/Lab/Compute/Benchmarks/quiz/type-of-scheduler-in-libult",permalink:"/operating-systems/Lab/Compute/Benchmarks/quiz/type-of-scheduler-in-libult",draft:!1,tags:[],version:"current",frontMatter:{}},u={},s=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],c={toc:s};function p(e){let{components:t,...n}=e;return(0,i.kt)("wrapper",(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,i.kt)("h1",{id:"type-of-scheduler-in-libultso"},"Type of Scheduler in ",(0,i.kt)("inlineCode",{parentName:"h1"},"libult.so")),(0,i.kt)("h2",{id:"question-text"},"Question Text"),(0,i.kt)("p",null,"Inspect the code in ",(0,i.kt)("inlineCode",{parentName:"p"},"support/libult/threads.c")," further.\nWhich type of scheduler does ",(0,i.kt)("inlineCode",{parentName:"p"},"libult.so")," use?"),(0,i.kt)("h2",{id:"question-answers"},"Question Answers"),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},"It uses a preemptive scheduler")),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},"It uses a cooperative scheduler"),(0,i.kt)("li",{parentName:"ul"},"It uses both a cooperative and a preemptive scheduler")),(0,i.kt)("h2",{id:"feedback"},"Feedback"),(0,i.kt)("p",null,(0,i.kt)("inlineCode",{parentName:"p"},"libult.so")," uses a preemptive scheduler.\nIts timer is initialised in the ",(0,i.kt)("inlineCode",{parentName:"p"},"init_profiling_timer()")," function.\nThe context switch is performed in the ",(0,i.kt)("inlineCode",{parentName:"p"},"handle_sigprof()")," function."))}p.isMDXComponent=!0}}]);