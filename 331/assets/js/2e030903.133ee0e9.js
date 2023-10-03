"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[2661],{3905:(e,t,r)=>{r.d(t,{Zo:()=>u,kt:()=>d});var n=r(7294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function o(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function i(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?o(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},o=Object.keys(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var c=n.createContext({}),s=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):i(i({},t),e)),r},u=function(e){var t=s(e.components);return n.createElement(c.Provider,{value:t},e.children)},p="mdxType",f={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},m=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,o=e.originalType,c=e.parentName,u=l(e,["components","mdxType","originalType","parentName"]),p=s(r),m=a,d=p["".concat(c,".").concat(m)]||p[m]||f[m]||o;return r?n.createElement(d,i(i({ref:t},u),{},{components:r})):n.createElement(d,i({ref:t},u))}));function d(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=r.length,i=new Array(o);i[0]=m;var l={};for(var c in t)hasOwnProperty.call(t,c)&&(l[c]=t[c]);l.originalType=e,l[p]="string"==typeof e?e:a,i[1]=l;for(var s=2;s<o;s++)i[s]=r[s];return n.createElement.apply(null,i)}return n.createElement.apply(null,r)}m.displayName="MDXCreateElement"},8580:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>f,frontMatter:()=>o,metadata:()=>l,toc:()=>s});var n=r(7462),a=(r(7294),r(3905));const o={},i="Stack Protector",l={unversionedId:"Lab/Data/quiz/memory-stack-protector",id:"Lab/Data/quiz/memory-stack-protector",title:"Stack Protector",description:"Question Text",source:"@site/docs/Lab/Data/quiz/memory-stack-protector.md",sourceDirName:"Lab/Data/quiz",slug:"/Lab/Data/quiz/memory-stack-protector",permalink:"/operating-systems/331/Lab/Data/quiz/memory-stack-protector",draft:!1,tags:[],version:"current",frontMatter:{}},c={},s=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],u={toc:s},p="wrapper";function f(e){let{components:t,...r}=e;return(0,a.kt)(p,(0,n.Z)({},u,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"stack-protector"},"Stack Protector"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"For the ",(0,a.kt)("inlineCode",{parentName:"p"},"support/memory-security/bo_write_practice")," executable we are not able overwrite the ",(0,a.kt)("inlineCode",{parentName:"p"},"s")," variable no matter the input.\nWhy is that?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"s")," needs to be declared after ",(0,a.kt)("inlineCode",{parentName:"li"},"buffer"),".")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"when using the stack canary, the buffer is always placed right below it.")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"due to ASLR, the address of ",(0,a.kt)("inlineCode",{parentName:"p"},"s")," is random.")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"the stack canary makes it impossible to overwrite local variables."))),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"When using the canary, to minimize the damage a buffer overflow could cause, the buffers are always placed right below the canary.\nBy doing so, a buffer overflow will not overwrite anything.\nHowever, it is still possible to overwrite other local buffers, provided that a function declares more than 1 array or if we use the pointer directly."))}f.isMDXComponent=!0}}]);