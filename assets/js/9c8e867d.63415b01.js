"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[82488],{3905:(e,t,n)=>{n.d(t,{Zo:()=>p,kt:()=>m});var r=n(67294);function o(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function a(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){o(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var u=r.createContext({}),c=function(e){var t=r.useContext(u),n=t;return e&&(n="function"==typeof e?e(t):a(a({},t),e)),n},p=function(e){var t=c(e.components);return r.createElement(u.Provider,{value:t},e.children)},s="mdxType",f={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,o=e.mdxType,i=e.originalType,u=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),s=c(n),d=o,m=s["".concat(u,".").concat(d)]||s[d]||f[d]||i;return n?r.createElement(m,a(a({ref:t},p),{},{components:n})):r.createElement(m,a({ref:t},p))}));function m(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var i=n.length,a=new Array(i);a[0]=d;var l={};for(var u in t)hasOwnProperty.call(t,u)&&(l[u]=t[u]);l.originalType=e,l[s]="string"==typeof e?e:o,a[1]=l;for(var c=2;c<i;c++)a[c]=n[c];return r.createElement.apply(null,a)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},3796:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>u,contentTitle:()=>a,default:()=>s,frontMatter:()=>i,metadata:()=>l,toc:()=>c});var r=n(87462),o=(n(67294),n(3905));const i={},a="`O_TRUNC` Flag Behaviour",l={unversionedId:"Lab/I/O/Local I/O in Action/quiz/o-trunc",id:"Lab/I/O/Local I/O in Action/quiz/o-trunc",title:"`O_TRUNC` Flag Behaviour",description:"Question Text",source:"@site/docs/Lab/I/O/Local I/O in Action/quiz/o-trunc.md",sourceDirName:"Lab/I/O/Local I/O in Action/quiz",slug:"/Lab/I/O/Local I/O in Action/quiz/o-trunc",permalink:"/operating-systems/Lab/I/O/Local I/O in Action/quiz/o-trunc",draft:!1,tags:[],version:"current",frontMatter:{}},u={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:c};function s(e){let{components:t,...n}=e;return(0,o.kt)("wrapper",(0,r.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"o_trunc-flag-behaviour"},(0,o.kt)("inlineCode",{parentName:"h1"},"O_TRUNC")," Flag Behaviour"),(0,o.kt)("h2",{id:"question-text"},"Question Text"),(0,o.kt)("p",null,"How does the ",(0,o.kt)("inlineCode",{parentName:"p"},"O_TRUNC")," flag change the behaviour of ",(0,o.kt)("inlineCode",{parentName:"p"},"open()"),"?"),(0,o.kt)("h2",{id:"question-answers"},"Question Answers"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"the previous content of the file is deleted")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"new data will be appended to the file")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"newly written data will be ignored"))),(0,o.kt)("h2",{id:"feedback"},"Feedback"),(0,o.kt)("p",null,"The man page provides us with unlimited wisdon:"),(0,o.kt)("blockquote",null,(0,o.kt)("p",{parentName:"blockquote"},"If the file already exists and is a regular file and the access mode allows writing (i.e., is ",(0,o.kt)("inlineCode",{parentName:"p"},"O_RDWR")," or ",(0,o.kt)("inlineCode",{parentName:"p"},"O_WRONLY"),") it will be truncated to length 0.")),(0,o.kt)("p",null,"Setting the length of the file to 0 is equivalent to deleting the previous content of the file."))}s.isMDXComponent=!0}}]);