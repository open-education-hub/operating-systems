"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[99744],{3905:(e,t,r)=>{r.d(t,{Zo:()=>p,kt:()=>f});var n=r(67294);function o(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function a(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function i(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?a(Object(r),!0).forEach((function(t){o(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):a(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function s(e,t){if(null==e)return{};var r,n,o=function(e,t){if(null==e)return{};var r,n,o={},a=Object.keys(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||(o[r]=e[r]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(o[r]=e[r])}return o}var c=n.createContext({}),l=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):i(i({},t),e)),r},p=function(e){var t=l(e.components);return n.createElement(c.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},m=n.forwardRef((function(e,t){var r=e.components,o=e.mdxType,a=e.originalType,c=e.parentName,p=s(e,["components","mdxType","originalType","parentName"]),m=l(r),f=o,d=m["".concat(c,".").concat(f)]||m[f]||u[f]||a;return r?n.createElement(d,i(i({ref:t},p),{},{components:r})):n.createElement(d,i({ref:t},p))}));function f(e,t){var r=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=r.length,i=new Array(a);i[0]=m;var s={};for(var c in t)hasOwnProperty.call(t,c)&&(s[c]=t[c]);s.originalType=e,s.mdxType="string"==typeof e?e:o,i[1]=s;for(var l=2;l<a;l++)i[l]=r[l];return n.createElement.apply(null,i)}return n.createElement.apply(null,r)}m.displayName="MDXCreateElement"},7678:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>u,frontMatter:()=>a,metadata:()=>s,toc:()=>l});var n=r(87462),o=(r(67294),r(3905));const a={},i="TLS `var` Copies",s={unversionedId:"Lab/Compute/Processes/quiz/tls-var-copies",id:"Lab/Compute/Processes/quiz/tls-var-copies",title:"TLS `var` Copies",description:"Question Text",source:"@site/docs/Lab/Compute/Processes/quiz/tls-var-copies.md",sourceDirName:"Lab/Compute/Processes/quiz",slug:"/Lab/Compute/Processes/quiz/tls-var-copies",permalink:"/operating-systems/Lab/Compute/Processes/quiz/tls-var-copies",draft:!1,tags:[],version:"current",frontMatter:{}},c={},l=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:l};function u(e){let{components:t,...r}=e;return(0,o.kt)("wrapper",(0,n.Z)({},p,r,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"tls-var-copies"},"TLS ",(0,o.kt)("inlineCode",{parentName:"h1"},"var")," Copies"),(0,o.kt)("h2",{id:"question-text"},"Question Text"),(0,o.kt)("p",null,"How many copies of the ",(0,o.kt)("inlineCode",{parentName:"p"},"var")," variable from ",(0,o.kt)("inlineCode",{parentName:"p"},"support/race-condition/c/race_condition_tls.c")," are there after each thread has modified it at leas once?"),(0,o.kt)("h2",{id:"question-answers"},"Question Answers"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"1"),(0,o.kt)("li",{parentName:"ul"},"2")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"3")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"5")),(0,o.kt)("h2",{id:"feedback"},"Feedback"),(0,o.kt)("p",null,"There are 3 copies one for the ",(0,o.kt)("inlineCode",{parentName:"p"},"main()")," thread, another one for ",(0,o.kt)("inlineCode",{parentName:"p"},"increment_var()")," and the third for ",(0,o.kt)("inlineCode",{parentName:"p"},"decrement_var()"),"."))}u.isMDXComponent=!0}}]);