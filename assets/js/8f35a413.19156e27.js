"use strict";(self.webpackChunkos=self.webpackChunkos||[]).push([[7778],{5680:(e,t,n)=>{n.d(t,{xA:()=>s,yg:()=>m});var a=n(6540);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function o(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},i=Object.keys(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var p=a.createContext({}),u=function(e){var t=a.useContext(p),n=t;return e&&(n="function"==typeof e?e(t):o(o({},t),e)),n},s=function(e){var t=u(e.components);return a.createElement(p.Provider,{value:t},e.children)},c="mdxType",y={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},d=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,i=e.originalType,p=e.parentName,s=l(e,["components","mdxType","originalType","parentName"]),c=u(n),d=r,m=c["".concat(p,".").concat(d)]||c[d]||y[d]||i;return n?a.createElement(m,o(o({ref:t},s),{},{components:n})):a.createElement(m,o({ref:t},s))}));function m(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var i=n.length,o=new Array(i);o[0]=d;var l={};for(var p in t)hasOwnProperty.call(t,p)&&(l[p]=t[p]);l.originalType=e,l[c]="string"==typeof e?e:r,o[1]=l;for(var u=2;u<i;u++)o[u]=n[u];return a.createElement.apply(null,o)}return a.createElement.apply(null,n)}d.displayName="MDXCreateElement"},8248:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>p,contentTitle:()=>o,default:()=>y,frontMatter:()=>i,metadata:()=>l,toc:()=>u});var a=n(8168),r=(n(6540),n(5680));const i={},o="Stack layout",l={unversionedId:"Lab/Data/quiz/stack-layout",id:"Lab/Data/quiz/stack-layout",title:"Stack layout",description:"Question Text",source:"@site/docs/Lab/Data/quiz/stack-layout.md",sourceDirName:"Lab/Data/quiz",slug:"/Lab/Data/quiz/stack-layout",permalink:"/operating-systems/Lab/Data/quiz/stack-layout",draft:!1,tags:[],version:"current",frontMatter:{}},p={},u=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],s={toc:u},c="wrapper";function y(e){let{components:t,...n}=e;return(0,r.yg)(c,(0,a.A)({},s,n,{components:t,mdxType:"MDXLayout"}),(0,r.yg)("h1",{id:"stack-layout"},"Stack layout"),(0,r.yg)("h2",{id:"question-text"},"Question Text"),(0,r.yg)("p",null,"What is the stack layout for the ",(0,r.yg)("inlineCode",{parentName:"p"},"fun")," function in the ",(0,r.yg)("inlineCode",{parentName:"p"},"bo_write.c")," program (starting from a high address)?"),(0,r.yg)("h2",{id:"question-answers"},"Question Answers"),(0,r.yg)("ul",null,(0,r.yg)("li",{parentName:"ul"},"return address, old ",(0,r.yg)("inlineCode",{parentName:"li"},"rbp"),", maybe some padding, variable ",(0,r.yg)("inlineCode",{parentName:"li"},"a"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[0]"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[1]"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[2]"))),(0,r.yg)("ul",null,(0,r.yg)("li",{parentName:"ul"},"return address, old ",(0,r.yg)("inlineCode",{parentName:"li"},"rbp"),", maybe some padding, variable ",(0,r.yg)("inlineCode",{parentName:"li"},"a"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[2]"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[1]"),", ",(0,r.yg)("inlineCode",{parentName:"li"},"b[0]"))),(0,r.yg)("ul",null,(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("p",{parentName:"li"},"return address, maybe some padding, variable ",(0,r.yg)("inlineCode",{parentName:"p"},"a"),", ",(0,r.yg)("inlineCode",{parentName:"p"},"b[0]"),", ",(0,r.yg)("inlineCode",{parentName:"p"},"b[1]"),", ",(0,r.yg)("inlineCode",{parentName:"p"},"b[2]"))),(0,r.yg)("li",{parentName:"ul"},(0,r.yg)("p",{parentName:"li"},"return address, old ",(0,r.yg)("inlineCode",{parentName:"p"},"rbp"),", maybe some padding, ",(0,r.yg)("inlineCode",{parentName:"p"},"b[0]"),", ",(0,r.yg)("inlineCode",{parentName:"p"},"b[1]"),", ",(0,r.yg)("inlineCode",{parentName:"p"},"b[2]"),", variable ",(0,r.yg)("inlineCode",{parentName:"p"},"a")))),(0,r.yg)("h2",{id:"feedback"},"Feedback"),(0,r.yg)("p",null,"Look at the assembly code and notice the exact layout."))}y.isMDXComponent=!0}}]);