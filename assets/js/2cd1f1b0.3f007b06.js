"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[40236],{3905:(e,t,r)=>{r.d(t,{Zo:()=>u,kt:()=>f});var n=r(67294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function i(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function o(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?i(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):i(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},i=Object.keys(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var s=n.createContext({}),p=function(e){var t=n.useContext(s),r=t;return e&&(r="function"==typeof e?e(t):o(o({},t),e)),r},u=function(e){var t=p(e.components);return n.createElement(s.Provider,{value:t},e.children)},c={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},d=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,i=e.originalType,s=e.parentName,u=l(e,["components","mdxType","originalType","parentName"]),d=p(r),f=a,m=d["".concat(s,".").concat(f)]||d[f]||c[f]||i;return r?n.createElement(m,o(o({ref:t},u),{},{components:r})):n.createElement(m,o({ref:t},u))}));function f(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var i=r.length,o=new Array(i);o[0]=d;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l.mdxType="string"==typeof e?e:a,o[1]=l;for(var p=2;p<i;p++)o[p]=r[p];return n.createElement.apply(null,o)}return n.createElement.apply(null,r)}d.displayName="MDXCreateElement"},52362:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>s,contentTitle:()=>o,default:()=>c,frontMatter:()=>i,metadata:()=>l,toc:()=>p});var n=r(87462),a=(r(67294),r(3905));const i={},o="File Descriptor of `stderr`",l={unversionedId:"Lab/I/O/Arena/quiz/stderr-fd",id:"Lab/I/O/Arena/quiz/stderr-fd",title:"File Descriptor of `stderr`",description:"Question Text",source:"@site/docs/Lab/I/O/Arena/quiz/stderr-fd.md",sourceDirName:"Lab/I/O/Arena/quiz",slug:"/Lab/I/O/Arena/quiz/stderr-fd",permalink:"/operating-systems/Lab/I/O/Arena/quiz/stderr-fd",draft:!1,tags:[],version:"current",frontMatter:{}},s={},p=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedaback",id:"feedaback",level:2}],u={toc:p};function c(e){let{components:t,...r}=e;return(0,a.kt)("wrapper",(0,n.Z)({},u,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"file-descriptor-of-stderr"},"File Descriptor of ",(0,a.kt)("inlineCode",{parentName:"h1"},"stderr")),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"Which file descriptor is associated by default to ",(0,a.kt)("inlineCode",{parentName:"p"},"stderr"),"?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"it varies from process to process")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"it varies from one Linux distribution to another")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},(0,a.kt)("inlineCode",{parentName:"p"},"stderr")," has no associated file descriptor"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"2")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"0")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"1"))),(0,a.kt)("h2",{id:"feedaback"},"Feedaback"),(0,a.kt)("p",null,"You would type ",(0,a.kt)("inlineCode",{parentName:"p"},"ls 2> /dev/null")," to ignore ",(0,a.kt)("inlineCode",{parentName:"p"},"ls"),"'s errors.\nThis equates to ",(0,a.kt)("strong",{parentName:"p"},"redirecting")," ",(0,a.kt)("inlineCode",{parentName:"p"},"stderr")," to ",(0,a.kt)("inlineCode",{parentName:"p"},"/dev/null"),".\nThe number 2 in ",(0,a.kt)("inlineCode",{parentName:"p"},"2>")," hints that ",(0,a.kt)("inlineCode",{parentName:"p"},"stderr")," is by default associated with file descriptor 2."))}c.isMDXComponent=!0}}]);