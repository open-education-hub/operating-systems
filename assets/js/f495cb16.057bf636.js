"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[44861],{3905:(e,t,n)=>{n.d(t,{Zo:()=>p,kt:()=>y});var o=n(67294);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);t&&(o=o.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,o)}return n}function a(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function s(e,t){if(null==e)return{};var n,o,r=function(e,t){if(null==e)return{};var n,o,r={},i=Object.keys(e);for(o=0;o<i.length;o++)n=i[o],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(o=0;o<i.length;o++)n=i[o],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var l=o.createContext({}),c=function(e){var t=o.useContext(l),n=t;return e&&(n="function"==typeof e?e(t):a(a({},t),e)),n},p=function(e){var t=c(e.components);return o.createElement(l.Provider,{value:t},e.children)},u="mdxType",m={inlineCode:"code",wrapper:function(e){var t=e.children;return o.createElement(o.Fragment,{},t)}},f=o.forwardRef((function(e,t){var n=e.components,r=e.mdxType,i=e.originalType,l=e.parentName,p=s(e,["components","mdxType","originalType","parentName"]),u=c(n),f=r,y=u["".concat(l,".").concat(f)]||u[f]||m[f]||i;return n?o.createElement(y,a(a({ref:t},p),{},{components:n})):o.createElement(y,a({ref:t},p))}));function y(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var i=n.length,a=new Array(i);a[0]=f;var s={};for(var l in t)hasOwnProperty.call(t,l)&&(s[l]=t[l]);s.originalType=e,s[u]="string"==typeof e?e:r,a[1]=s;for(var c=2;c<i;c++)a[c]=n[c];return o.createElement.apply(null,a)}return o.createElement.apply(null,n)}f.displayName="MDXCreateElement"},53665:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>l,contentTitle:()=>a,default:()=>u,frontMatter:()=>i,metadata:()=>s,toc:()=>c});var o=n(87462),r=(n(67294),n(3905));const i={},a="Limitation of Anonymous Pipes",s={unversionedId:"Lab/I/O/Local I/O in Action/quiz/anonymous-pipes-limitation",id:"Lab/I/O/Local I/O in Action/quiz/anonymous-pipes-limitation",title:"Limitation of Anonymous Pipes",description:"Question Text",source:"@site/docs/Lab/I/O/Local I/O in Action/quiz/anonymous-pipes-limitation.md",sourceDirName:"Lab/I/O/Local I/O in Action/quiz",slug:"/Lab/I/O/Local I/O in Action/quiz/anonymous-pipes-limitation",permalink:"/operating-systems/Lab/I/O/Local I/O in Action/quiz/anonymous-pipes-limitation",draft:!1,tags:[],version:"current",frontMatter:{}},l={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:c};function u(e){let{components:t,...n}=e;return(0,r.kt)("wrapper",(0,o.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,r.kt)("h1",{id:"limitation-of-anonymous-pipes"},"Limitation of Anonymous Pipes"),(0,r.kt)("h2",{id:"question-text"},"Question Text"),(0,r.kt)("p",null,"What of the following is the largest drawback of using anonymous pipes (created with ",(0,r.kt)("inlineCode",{parentName:"p"},"pipe()"),") for inter-process communication?"),(0,r.kt)("h2",{id:"question-answers"},"Question Answers"),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},"they only allow unidirectional communication")),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},'they only allow IPC between "related" processes (parent - child - grandchild etc.)')),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("p",{parentName:"li"},"if more processes use the same end of the same pipe, there may be race conditions")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("p",{parentName:"li"},"a pipe only has 2 file descriptors, but some processes may need more channels to communicate"))),(0,r.kt)("h2",{id:"feedback"},"Feedback"),(0,r.kt)("p",null,"Out of the answers above, the only limitation that cannot be overcome by using pipes alone is the requirement for the processes using them to be related.\nThe parent must create the pipes so the children can inherit them.\nAll other downsides can be overcome by using more pipes."),(0,r.kt)("p",null,"The answer to this is to employ ",(0,r.kt)("em",{parentName:"p"},"some")," filesystem support."))}u.isMDXComponent=!0}}]);