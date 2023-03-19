"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[66312],{3905:(e,t,n)=>{n.d(t,{Zo:()=>s,kt:()=>f});var a=n(67294);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},o=Object.keys(e);for(a=0;a<o.length;a++)n=o[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(a=0;a<o.length;a++)n=o[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var c=a.createContext({}),p=function(e){var t=a.useContext(c),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},s=function(e){var t=p(e.components);return a.createElement(c.Provider,{value:t},e.children)},u="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},m=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,o=e.originalType,c=e.parentName,s=l(e,["components","mdxType","originalType","parentName"]),u=p(n),m=r,f=u["".concat(c,".").concat(m)]||u[m]||d[m]||o;return n?a.createElement(f,i(i({ref:t},s),{},{components:n})):a.createElement(f,i({ref:t},s))}));function f(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var o=n.length,i=new Array(o);i[0]=m;var l={};for(var c in t)hasOwnProperty.call(t,c)&&(l[c]=t[c]);l.originalType=e,l[u]="string"==typeof e?e:r,i[1]=l;for(var p=2;p<o;p++)i[p]=n[p];return a.createElement.apply(null,i)}return a.createElement.apply(null,n)}m.displayName="MDXCreateElement"},909:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>d,frontMatter:()=>o,metadata:()=>l,toc:()=>p});var a=n(87462),r=(n(67294),n(3905));const o={},i="Page Allocation",l={unversionedId:"Lab/Data/Overview/quiz/page-allocation",id:"Lab/Data/Overview/quiz/page-allocation",title:"Page Allocation",description:"Question Text",source:"@site/docs/Lab/Data/Overview/quiz/page-allocation.md",sourceDirName:"Lab/Data/Overview/quiz",slug:"/Lab/Data/Overview/quiz/page-allocation",permalink:"/operating-systems/Lab/Data/Overview/quiz/page-allocation",draft:!1,tags:[],version:"current",frontMatter:{}},c={},p=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],s={toc:p},u="wrapper";function d(e){let{components:t,...n}=e;return(0,r.kt)(u,(0,a.Z)({},s,n,{components:t,mdxType:"MDXLayout"}),(0,r.kt)("h1",{id:"page-allocation"},"Page Allocation"),(0,r.kt)("h2",{id:"question-text"},"Question Text"),(0,r.kt)("pre",null,(0,r.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/static-dynamic$ size hello-static\ntext    data     bss     dec     hex filename\n893333   20996    7128  921457   e0f71 hello-static\n")),(0,r.kt)("p",null,"How many bytes should we add to the ",(0,r.kt)("inlineCode",{parentName:"p"},".data")," section to make its size ",(0,r.kt)("inlineCode",{parentName:"p"},"28 KB"),", instead of ",(0,r.kt)("inlineCode",{parentName:"p"},"24 KB"),"?"),(0,r.kt)("h2",{id:"question-answers"},"Question Answers"),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("p",{parentName:"li"},"1 KB")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("p",{parentName:"li"},"4 KB")),(0,r.kt)("li",{parentName:"ul"},(0,r.kt)("p",{parentName:"li"},"3580 bytes"))),(0,r.kt)("ul",null,(0,r.kt)("li",{parentName:"ul"},"3581 bytes")),(0,r.kt)("h2",{id:"feedback"},"Feedback"),(0,r.kt)("p",null,"The total size must be ",(0,r.kt)("inlineCode",{parentName:"p"},"1")," byte over the ",(0,r.kt)("inlineCode",{parentName:"p"},"24 KB")," threshold to cause a new page allocation.\nSo in order to get that past the current size of ",(0,r.kt)("inlineCode",{parentName:"p"},"20996"),", we need ",(0,r.kt)("inlineCode",{parentName:"p"},"3581")," bytes:"),(0,r.kt)("pre",null,(0,r.kt)("code",{parentName:"pre",className:"language-console"},'student@os:~$ echo "24 * 1024 + 1 - 20996" | bc\n3581\n')))}d.isMDXComponent=!0}}]);