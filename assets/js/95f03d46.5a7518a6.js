"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[77384],{3905:(e,t,n)=>{n.d(t,{Zo:()=>p,kt:()=>k});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function o(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),u=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):o(o({},t),e)),n},p=function(e){var t=u(e.components);return r.createElement(s.Provider,{value:t},e.children)},c="mdxType",m={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,i=e.originalType,s=e.parentName,p=l(e,["components","mdxType","originalType","parentName"]),c=u(n),d=a,k=c["".concat(s,".").concat(d)]||c[d]||m[d]||i;return n?r.createElement(k,o(o({ref:t},p),{},{components:n})):r.createElement(k,o({ref:t},p))}));function k(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var i=n.length,o=new Array(i);o[0]=d;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l[c]="string"==typeof e?e:a,o[1]=l;for(var u=2;u<i;u++)o[u]=n[u];return r.createElement.apply(null,o)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},40082:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>o,default:()=>m,frontMatter:()=>i,metadata:()=>l,toc:()=>u});var r=n(87462),a=(n(67294),n(3905));const i={},o="Valgrind Leaks",l={unversionedId:"Lab/Data/Working with Memory/quiz/valgrind-leaks",id:"Lab/Data/Working with Memory/quiz/valgrind-leaks",title:"Valgrind Leaks",description:"Question Text",source:"@site/docs/Lab/Data/Working with Memory/quiz/valgrind-leaks.md",sourceDirName:"Lab/Data/Working with Memory/quiz",slug:"/Lab/Data/Working with Memory/quiz/valgrind-leaks",permalink:"/operating-systems/Lab/Data/Working with Memory/quiz/valgrind-leaks",draft:!1,tags:[],version:"current",frontMatter:{}},s={},u=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:u},c="wrapper";function m(e){let{components:t,...n}=e;return(0,a.kt)(c,(0,r.Z)({},p,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"valgrind-leaks"},"Valgrind Leaks"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("pre",null,(0,a.kt)("code",{parentName:"pre",className:"language-c"},'struct student {\n    char *name;\n    int age;\n}\n\nstruct student *s = malloc(sizeof(*s));\ns->name = strdup("Reginald");\n// ...\nfree(s);\n')),(0,a.kt)("p",null,"What are the leaks in the above c program?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},"There are no leaks")),(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("p",{parentName:"li"},(0,a.kt)("inlineCode",{parentName:"p"},"s->name")," is ",(0,a.kt)("strong",{parentName:"p"},"definitely lost")))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"s->name")," is ",(0,a.kt)("strong",{parentName:"li"},"indirectly lost"))),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},(0,a.kt)("inlineCode",{parentName:"li"},"s->name")," is ",(0,a.kt)("strong",{parentName:"li"},"still reachable"))),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,(0,a.kt)("inlineCode",{parentName:"p"},"strdup()")," allocates memory for a string so the returned pointer must be freed.\nFreeing ",(0,a.kt)("inlineCode",{parentName:"p"},"s")," will leave us unable to free ",(0,a.kt)("inlineCode",{parentName:"p"},"s->name"),", so ",(0,a.kt)("inlineCode",{parentName:"p"},"s->name")," is ",(0,a.kt)("strong",{parentName:"p"},"indirectly lost"),".\nFind more about valgrind leak categories ",(0,a.kt)("a",{parentName:"p",href:"https://valgrind.org/docs/manual/faq.html#faq.deflost"},"here"),"."))}m.isMDXComponent=!0}}]);