"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[65257],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>m});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function u(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),l=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},c=function(e){var t=l(e.components);return r.createElement(s.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},f=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,c=u(e,["components","mdxType","originalType","parentName"]),f=l(n),m=a,d=f["".concat(s,".").concat(m)]||f[m]||p[m]||o;return n?r.createElement(d,i(i({ref:t},c),{},{components:n})):r.createElement(d,i({ref:t},c))}));function m(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,i=new Array(o);i[0]=f;var u={};for(var s in t)hasOwnProperty.call(t,s)&&(u[s]=t[s]);u.originalType=e,u.mdxType="string"==typeof e?e:a,i[1]=u;for(var l=2;l<o;l++)i[l]=n[l];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}f.displayName="MDXCreateElement"},81876:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>i,default:()=>p,frontMatter:()=>o,metadata:()=>u,toc:()=>l});var r=n(87462),a=(n(67294),n(3905));const o={},i="State of new ULT",u={unversionedId:"Lab/Compute/Benchmarks/quiz/state-of-new-ult",id:"Lab/Compute/Benchmarks/quiz/state-of-new-ult",title:"State of new ULT",description:"Question Text",source:"@site/docs/Lab/Compute/Benchmarks/quiz/state-of-new-ult.md",sourceDirName:"Lab/Compute/Benchmarks/quiz",slug:"/Lab/Compute/Benchmarks/quiz/state-of-new-ult",permalink:"/operating-systems/Lab/Compute/Benchmarks/quiz/state-of-new-ult",draft:!1,tags:[],version:"current",frontMatter:{}},s={},l=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],c={toc:l};function p(e){let{components:t,...n}=e;return(0,a.kt)("wrapper",(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"state-of-new-ult"},"State of new ULT"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"What is the first state that is assigned to a newly created ULT?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"RUNNING"),(0,a.kt)("li",{parentName:"ul"},"READY"),(0,a.kt)("li",{parentName:"ul"},"COMPLETED")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"Inside the function ",(0,a.kt)("inlineCode",{parentName:"p"},"threads_create()"),", we can see the following snippet ",(0,a.kt)("inlineCode",{parentName:"p"},"queue_enqueue(ready, new)"),".\nEach new thread is thus added to the READY queue."))}p.isMDXComponent=!0}}]);