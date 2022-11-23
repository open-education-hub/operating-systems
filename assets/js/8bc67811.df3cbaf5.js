"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[11054],{3905:(e,t,n)=>{n.d(t,{Zo:()=>p,kt:()=>f});var r=n(67294);function i(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function a(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){i(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,i=function(e,t){if(null==e)return{};var n,r,i={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(i[n]=e[n]);return i}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(i[n]=e[n])}return i}var s=r.createContext({}),c=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):a(a({},t),e)),n},p=function(e){var t=c(e.components);return r.createElement(s.Provider,{value:t},e.children)},u={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,i=e.mdxType,o=e.originalType,s=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),d=c(n),f=i,m=d["".concat(s,".").concat(f)]||d[f]||u[f]||o;return n?r.createElement(m,a(a({ref:t},p),{},{components:n})):r.createElement(m,a({ref:t},p))}));function f(e,t){var n=arguments,i=t&&t.mdxType;if("string"==typeof e||i){var o=n.length,a=new Array(o);a[0]=d;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l.mdxType="string"==typeof e?e:i,a[1]=l;for(var c=2;c<o;c++)a[c]=n[c];return r.createElement.apply(null,a)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},78069:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>a,default:()=>u,frontMatter:()=>o,metadata:()=>l,toc:()=>c});var r=n(87462),i=(n(67294),n(3905));const o={},a="Prints Working after Closing `stdio`",l={unversionedId:"Lab/I/O/Introduction/quiz/prints-work-no-stdio",id:"Lab/I/O/Introduction/quiz/prints-work-no-stdio",title:"Prints Working after Closing `stdio`",description:"Question Text",source:"@site/docs/Lab/I/O/Introduction/quiz/prints-work-no-stdio.md",sourceDirName:"Lab/I/O/Introduction/quiz",slug:"/Lab/I/O/Introduction/quiz/prints-work-no-stdio",permalink:"/operating-systems/Lab/I/O/Introduction/quiz/prints-work-no-stdio",draft:!1,tags:[],version:"current",frontMatter:{}},s={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:c};function u(e){let{components:t,...n}=e;return(0,i.kt)("wrapper",(0,r.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,i.kt)("h1",{id:"prints-working-after-closing-stdio"},"Prints Working after Closing ",(0,i.kt)("inlineCode",{parentName:"h1"},"stdio")),(0,i.kt)("h2",{id:"question-text"},"Question Text"),(0,i.kt)("p",null,"Why does ",(0,i.kt)("inlineCode",{parentName:"p"},"support/redirect/redirect.c"),", still print messages to the console after closing file descriptor 1 (",(0,i.kt)("inlineCode",{parentName:"p"},"stdout"),")?"),(0,i.kt)("h2",{id:"question-answers"},"Question Answers"),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},"because ",(0,i.kt)("inlineCode",{parentName:"li"},"wait_for_input()")," calls ",(0,i.kt)("inlineCode",{parentName:"li"},"fprintf(stderr, ...)"),", which prints to ",(0,i.kt)("inlineCode",{parentName:"li"},"stderr")," (file descriptor 2)")),(0,i.kt)("ul",null,(0,i.kt)("li",{parentName:"ul"},(0,i.kt)("p",{parentName:"li"},'because the default file descriptors cannot be "truly" closed')),(0,i.kt)("li",{parentName:"ul"},(0,i.kt)("p",{parentName:"li"},"because the other two default file descriptors are still linked to the console")),(0,i.kt)("li",{parentName:"ul"},(0,i.kt)("p",{parentName:"li"},"because the ",(0,i.kt)("inlineCode",{parentName:"p"},"wait_for_input()")," function started printed before closing the ",(0,i.kt)("inlineCode",{parentName:"p"},"stdout")," file descriptor"))),(0,i.kt)("h2",{id:"feedback"},"Feedback"),(0,i.kt)("p",null,"If you look at ",(0,i.kt)("inlineCode",{parentName:"p"},"wait_for_input()")," closely, you'll notice it calls ",(0,i.kt)("inlineCode",{parentName:"p"},"fprintf(stderr, ...)"),".\n",(0,i.kt)("inlineCode",{parentName:"p"},"stderr")," is liked to file descriptor 2, which is left unchanged so we can still write data to it."))}u.isMDXComponent=!0}}]);