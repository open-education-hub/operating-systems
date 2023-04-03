"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[31825],{3905:(e,t,r)=>{r.d(t,{Zo:()=>s,kt:()=>m});var n=r(67294);function i(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function o(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function a(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?o(Object(r),!0).forEach((function(t){i(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,i=function(e,t){if(null==e)return{};var r,n,i={},o=Object.keys(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||(i[r]=e[r]);return i}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(i[r]=e[r])}return i}var u=n.createContext({}),p=function(e){var t=n.useContext(u),r=t;return e&&(r="function"==typeof e?e(t):a(a({},t),e)),r},s=function(e){var t=p(e.components);return n.createElement(u.Provider,{value:t},e.children)},c="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},f=n.forwardRef((function(e,t){var r=e.components,i=e.mdxType,o=e.originalType,u=e.parentName,s=l(e,["components","mdxType","originalType","parentName"]),c=p(r),f=i,m=c["".concat(u,".").concat(f)]||c[f]||d[f]||o;return r?n.createElement(m,a(a({ref:t},s),{},{components:r})):n.createElement(m,a({ref:t},s))}));function m(e,t){var r=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var o=r.length,a=new Array(o);a[0]=f;var l={};for(var u in t)hasOwnProperty.call(t,u)&&(l[u]=t[u]);l.originalType=e,l[c]="string"==typeof e?e:i,a[1]=l;for(var p=2;p<o;p++)a[p]=r[p];return n.createElement.apply(null,a)}return n.createElement.apply(null,r)}f.displayName="MDXCreateElement"},85465:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>u,contentTitle:()=>a,default:()=>d,frontMatter:()=>o,metadata:()=>l,toc:()=>p});var n=r(87462),i=(r(67294),r(3905));const o={},a="Type of Scheduler in `libult.so`",l={unversionedId:"Lab/Compute/Hardware Perspective/quiz/type-of-scheduler-in-libult",id:"Lab/Compute/Hardware Perspective/quiz/type-of-scheduler-in-libult",title:"Type of Scheduler in `libult.so`",description:"Question Text",source:"@site/docs/Lab/Compute/Hardware Perspective/quiz/type-of-scheduler-in-libult.md",sourceDirName:"Lab/Compute/Hardware Perspective/quiz",slug:"/Lab/Compute/Hardware Perspective/quiz/type-of-scheduler-in-libult",permalink:"/operating-systems/Lab/Compute/Hardware Perspective/quiz/type-of-scheduler-in-libult",draft:!1,tags:[],version:"current",frontMatter:{}},u={},p=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],s={toc:p},c="wrapper";function d(e){let{components:t,...r}=e;return(0,i.kt)(c,(0,n.Z)({},s,r,{components:t,mdxType:"MDXLayout"}),(0,i.kt)("h1",{id:"type-of-scheduler-in-libultso"},"Type of Scheduler in ",(0,i.kt)("inlineCode",{parentName:"h1"},"libult.so")),(0,i.kt)("h2",{id:"question-text"},"Question Text"),(0,i.kt)("p",null,"Inspect the code in ",(0,i.kt)("inlineCode",{parentName:"p"},"support/libult/threads.c")," further.\nWhich type of scheduler does ",(0,i.kt)("inlineCode",{parentName:"p"},"libult.so")," use?"),(0,i.kt)("h2",{id:"question-answers"},"Question Answers"),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},"It uses a preemptive scheduler")),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},(0,i.kt)("p",{parentName:"li"},"It uses a cooperative scheduler")),(0,i.kt)("li",{parentName:"ul"},(0,i.kt)("p",{parentName:"li"},"It uses both a cooperative and a preemptive scheduler"))),(0,i.kt)("h2",{id:"feedback"},"Feedback"),(0,i.kt)("p",null,(0,i.kt)("inlineCode",{parentName:"p"},"libult.so")," uses a preemptive scheduler.\nIts timer is initialised in the ",(0,i.kt)("inlineCode",{parentName:"p"},"init_profiling_timer()")," function.\nThe context switch is performed in the ",(0,i.kt)("inlineCode",{parentName:"p"},"handle_sigprof()")," function."))}d.isMDXComponent=!0}}]);