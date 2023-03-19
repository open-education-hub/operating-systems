"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[93085],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>f});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function l(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function i(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),u=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):l(l({},t),e)),n},c=function(e){var t=u(e.components);return r.createElement(s.Provider,{value:t},e.children)},p="mdxType",m={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,c=i(e,["components","mdxType","originalType","parentName"]),p=u(n),d=a,f=p["".concat(s,".").concat(d)]||p[d]||m[d]||o;return n?r.createElement(f,l(l({ref:t},c),{},{components:n})):r.createElement(f,l({ref:t},c))}));function f(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,l=new Array(o);l[0]=d;var i={};for(var s in t)hasOwnProperty.call(t,s)&&(i[s]=t[s]);i.originalType=e,i[p]="string"==typeof e?e:a,l[1]=i;for(var u=2;u<o;u++)l[u]=n[u];return r.createElement.apply(null,l)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},88430:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>l,default:()=>m,frontMatter:()=>o,metadata:()=>i,toc:()=>u});var r=n(87462),a=(n(67294),n(3905));const o={},l="Valgrind Leaks",i={unversionedId:"Lab/Data/Process Memory/quiz/valgrind-leaks",id:"Lab/Data/Process Memory/quiz/valgrind-leaks",title:"Valgrind Leaks",description:"Question Text",source:"@site/docs/Lab/Data/Process Memory/quiz/valgrind-leaks.md",sourceDirName:"Lab/Data/Process Memory/quiz",slug:"/Lab/Data/Process Memory/quiz/valgrind-leaks",permalink:"/operating-systems/Lab/Data/Process Memory/quiz/valgrind-leaks",draft:!1,tags:[],version:"current",frontMatter:{}},s={},u=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],c={toc:u},p="wrapper";function m(e){let{components:t,...n}=e;return(0,a.kt)(p,(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"valgrind-leaks"},"Valgrind Leaks"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-c"},'struct student {\n    char *name;\n    int age;\n}\n\nstruct student *s = malloc(sizeof(*s));\ns->name = strdup("Reginald");\n// ...\nfree(s);\n')),(0,a.kt)("p",null,"What are the leaks in the above c program?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"There are no leaks")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},(0,a.kt)("inlineCode",{parentName:"p"},"s->name")," is ",(0,a.kt)("strong",{parentName:"p"},"definitely lost")))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"s->name")," is ",(0,a.kt)("strong",{parentName:"li"},"indirectly lost"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"s->name")," is ",(0,a.kt)("strong",{parentName:"li"},"still reachable"))),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,(0,a.kt)("inlineCode",{parentName:"p"},"strdup()")," allocates memory for a string so the returned pointer must be freed.\nFreeing ",(0,a.kt)("inlineCode",{parentName:"p"},"s")," will leave us unable to free ",(0,a.kt)("inlineCode",{parentName:"p"},"s->name"),", so ",(0,a.kt)("inlineCode",{parentName:"p"},"s->name")," is ",(0,a.kt)("strong",{parentName:"p"},"indirectly lost"),".\nFind more about valgrind leak categories ",(0,a.kt)("a",{parentName:"p",href:"https://valgrind.org/docs/manual/faq.html#faq.deflost"},"here"),"."))}m.isMDXComponent=!0}}]);