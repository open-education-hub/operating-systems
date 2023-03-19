"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[76717],{3905:(e,t,r)=>{r.d(t,{Zo:()=>p,kt:()=>f});var n=r(67294);function o(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function a(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function l(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?a(Object(r),!0).forEach((function(t){o(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):a(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function s(e,t){if(null==e)return{};var r,n,o=function(e,t){if(null==e)return{};var r,n,o={},a=Object.keys(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||(o[r]=e[r]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(o[r]=e[r])}return o}var c=n.createContext({}),i=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):l(l({},t),e)),r},p=function(e){var t=i(e.components);return n.createElement(c.Provider,{value:t},e.children)},u="mdxType",m={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},d=n.forwardRef((function(e,t){var r=e.components,o=e.mdxType,a=e.originalType,c=e.parentName,p=s(e,["components","mdxType","originalType","parentName"]),u=i(r),d=o,f=u["".concat(c,".").concat(d)]||u[d]||m[d]||a;return r?n.createElement(f,l(l({ref:t},p),{},{components:r})):n.createElement(f,l({ref:t},p))}));function f(e,t){var r=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=r.length,l=new Array(a);l[0]=d;var s={};for(var c in t)hasOwnProperty.call(t,c)&&(s[c]=t[c]);s.originalType=e,s[u]="string"==typeof e?e:o,l[1]=s;for(var i=2;i<a;i++)l[i]=r[i];return n.createElement.apply(null,l)}return n.createElement.apply(null,r)}d.displayName="MDXCreateElement"},75787:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>l,default:()=>m,frontMatter:()=>a,metadata:()=>s,toc:()=>i});var n=r(87462),o=(r(67294),r(3905));const a={},l="Operator Overloading",s={unversionedId:"Lab/Data/Process Memory/quiz/operators",id:"Lab/Data/Process Memory/quiz/operators",title:"Operator Overloading",description:"Question Text",source:"@site/docs/Lab/Data/Process Memory/quiz/operators.md",sourceDirName:"Lab/Data/Process Memory/quiz",slug:"/Lab/Data/Process Memory/quiz/operators",permalink:"/operating-systems/Lab/Data/Process Memory/quiz/operators",draft:!1,tags:[],version:"current",frontMatter:{}},c={},i=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],p={toc:i},u="wrapper";function m(e){let{components:t,...r}=e;return(0,o.kt)(u,(0,n.Z)({},p,r,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"operator-overloading"},"Operator Overloading"),(0,o.kt)("h2",{id:"question-text"},"Question Text"),(0,o.kt)("p",null,"How many constructor calls, copy constructor calls, assignment operator calls and destructor calls does the following program issue?"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-d"},"Obj quiz(Obj o1, Obj o2)\n{\n    o2 = o1;\n    return o2;\n}\nvoid main()\n{\n    Obj b = quiz(o1, o2);\n}\n")),(0,o.kt)("h2",{id:"question-answers"},"Question Answers"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"constructor calls = 0, copy constructor calls = 3, assignment operator calls = 1, destructor calls = 3")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"constructor calls = 1, copy constructor calls = 2, assignment operator calls = 1, destructor calls = 2")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"constructor calls = 0, copy constructor calls = 2, assignment operator calls = 1, destructor calls = 2")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"constructor calls = 0, copy constructor calls = 3, assignment operator calls = 1, destructor calls = 1"))),(0,o.kt)("h2",{id:"feedback"},"Feedback"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"There are no constructor calls because there is no object construction when using ",(0,o.kt)("inlineCode",{parentName:"p"},"int"),".")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"There are 3 copy constructor calls: for passing ",(0,o.kt)("inlineCode",{parentName:"p"},"o1"),", for passing ",(0,o.kt)("inlineCode",{parentName:"p"},"o2"),", and for returning ",(0,o.kt)("inlineCode",{parentName:"p"},"o2"),".")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"There is 1 assignment operator call for ",(0,o.kt)("inlineCode",{parentName:"p"},"o2 = o1"),".")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"There are 3 destructor calls, because each constructed object needs to be destroyed."))))}m.isMDXComponent=!0}}]);