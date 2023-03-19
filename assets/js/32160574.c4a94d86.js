"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[28006],{3905:(e,t,r)=>{r.d(t,{Zo:()=>m,kt:()=>y});var n=r(67294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function i(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function o(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?i(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):i(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function l(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},i=Object.keys(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(n=0;n<i.length;n++)r=i[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var u=n.createContext({}),c=function(e){var t=n.useContext(u),r=t;return e&&(r="function"==typeof e?e(t):o(o({},t),e)),r},m=function(e){var t=c(e.components);return n.createElement(u.Provider,{value:t},e.children)},p="mdxType",s={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},f=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,i=e.originalType,u=e.parentName,m=l(e,["components","mdxType","originalType","parentName"]),p=c(r),f=a,y=p["".concat(u,".").concat(f)]||p[f]||s[f]||i;return r?n.createElement(y,o(o({ref:t},m),{},{components:r})):n.createElement(y,o({ref:t},m))}));function y(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var i=r.length,o=new Array(i);o[0]=f;var l={};for(var u in t)hasOwnProperty.call(t,u)&&(l[u]=t[u]);l.originalType=e,l[p]="string"==typeof e?e:a,o[1]=l;for(var c=2;c<i;c++)o[c]=r[c];return n.createElement.apply(null,o)}return n.createElement.apply(null,r)}f.displayName="MDXCreateElement"},58869:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>u,contentTitle:()=>o,default:()=>s,frontMatter:()=>i,metadata:()=>l,toc:()=>c});var n=r(87462),a=(r(67294),r(3905));const i={},o="`mmap()` file",l={unversionedId:"Lab/Data/Memory Security/quiz/mmap-file",id:"Lab/Data/Memory Security/quiz/mmap-file",title:"`mmap()` file",description:"Question Text",source:"@site/docs/Lab/Data/Memory Security/quiz/mmap-file.md",sourceDirName:"Lab/Data/Memory Security/quiz",slug:"/Lab/Data/Memory Security/quiz/mmap-file",permalink:"/operating-systems/Lab/Data/Memory Security/quiz/mmap-file",draft:!1,tags:[],version:"current",frontMatter:{}},u={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],m={toc:c},p="wrapper";function s(e){let{components:t,...r}=e;return(0,a.kt)(p,(0,n.Z)({},m,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"mmap-file"},(0,a.kt)("inlineCode",{parentName:"h1"},"mmap()")," file"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"What is one advantage of mapping a file in memory?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"It reduces interaction with the disk")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"Consumes less memory")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"It is faster because it does not uses the file API")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"Allows all threads to use the same memory area"))),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"After mapping a file in memory, all changes will be visible only in memory.\nWhen removing the mapping or explicitely calling ",(0,a.kt)("inlineCode",{parentName:"p"},"msync()")," the information from memory will be visible on disk."))}s.isMDXComponent=!0}}]);