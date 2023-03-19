"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[57160],{3905:(e,t,n)=>{n.d(t,{Zo:()=>s,kt:()=>y});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var c=r.createContext({}),p=function(e){var t=r.useContext(c),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},s=function(e){var t=p(e.components);return r.createElement(c.Provider,{value:t},e.children)},u="mdxType",m={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,c=e.parentName,s=l(e,["components","mdxType","originalType","parentName"]),u=p(n),d=a,y=u["".concat(c,".").concat(d)]||u[d]||m[d]||o;return n?r.createElement(y,i(i({ref:t},s),{},{components:n})):r.createElement(y,i({ref:t},s))}));function y(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,i=new Array(o);i[0]=d;var l={};for(var c in t)hasOwnProperty.call(t,c)&&(l[c]=t[c]);l.originalType=e,l[u]="string"==typeof e?e:a,i[1]=l;for(var p=2;p<o;p++)i[p]=n[p];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},87218:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>c,contentTitle:()=>i,default:()=>m,frontMatter:()=>o,metadata:()=>l,toc:()=>p});var r=n(87462),a=(n(67294),n(3905));const o={},i="Page Allocation",l={unversionedId:"Lab/Data/Memory Security/quiz/page-allocation",id:"Lab/Data/Memory Security/quiz/page-allocation",title:"Page Allocation",description:"Question Text",source:"@site/docs/Lab/Data/Memory Security/quiz/page-allocation.md",sourceDirName:"Lab/Data/Memory Security/quiz",slug:"/Lab/Data/Memory Security/quiz/page-allocation",permalink:"/operating-systems/Lab/Data/Memory Security/quiz/page-allocation",draft:!1,tags:[],version:"current",frontMatter:{}},c={},p=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],s={toc:p},u="wrapper";function m(e){let{components:t,...n}=e;return(0,a.kt)(u,(0,r.Z)({},s,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"page-allocation"},"Page Allocation"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/static-dynamic$ size hello-static\ntext    data     bss     dec     hex filename\n893333   20996    7128  921457   e0f71 hello-static\n")),(0,a.kt)("p",null,"How many bytes should we add to the ",(0,a.kt)("inlineCode",{parentName:"p"},".data")," section to make its size ",(0,a.kt)("inlineCode",{parentName:"p"},"28 KB"),", instead of ",(0,a.kt)("inlineCode",{parentName:"p"},"24 KB"),"?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"1 KB")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"4 KB")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"3580 bytes"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"3581 bytes")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"The total size must be ",(0,a.kt)("inlineCode",{parentName:"p"},"1")," byte over the ",(0,a.kt)("inlineCode",{parentName:"p"},"24 KB")," threshold to cause a new page allocation.\nSo in order to get that past the current size of ",(0,a.kt)("inlineCode",{parentName:"p"},"20996"),", we need ",(0,a.kt)("inlineCode",{parentName:"p"},"3581")," bytes:"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-console"},'student@os:~$ echo "24 * 1024 + 1 - 20996" | bc\n3581\n')))}m.isMDXComponent=!0}}]);