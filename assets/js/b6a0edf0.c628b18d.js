"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[34782],{3905:(e,t,r)=>{r.d(t,{Zo:()=>l,kt:()=>O});var n=r(67294);function o(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function a(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function s(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?a(Object(r),!0).forEach((function(t){o(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):a(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function i(e,t){if(null==e)return{};var r,n,o=function(e,t){if(null==e)return{};var r,n,o={},a=Object.keys(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||(o[r]=e[r]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(n=0;n<a.length;n++)r=a[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(o[r]=e[r])}return o}var c=n.createContext({}),p=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):s(s({},t),e)),r},l=function(e){var t=p(e.components);return n.createElement(c.Provider,{value:t},e.children)},f="mdxType",u={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},y=n.forwardRef((function(e,t){var r=e.components,o=e.mdxType,a=e.originalType,c=e.parentName,l=i(e,["components","mdxType","originalType","parentName"]),f=p(r),y=o,O=f["".concat(c,".").concat(y)]||f[y]||u[y]||a;return r?n.createElement(O,s(s({ref:t},l),{},{components:r})):n.createElement(O,s({ref:t},l))}));function O(e,t){var r=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=r.length,s=new Array(a);s[0]=y;var i={};for(var c in t)hasOwnProperty.call(t,c)&&(i[c]=t[c]);i.originalType=e,i[f]="string"==typeof e?e:o,s[1]=i;for(var p=2;p<a;p++)s[p]=r[p];return n.createElement.apply(null,s)}return n.createElement.apply(null,r)}y.displayName="MDXCreateElement"},64132:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>s,default:()=>f,frontMatter:()=>a,metadata:()=>i,toc:()=>p});var n=r(87462),o=(r(67294),r(3905));const a={},s="Sparse File",i={unversionedId:"Lab/I/O/Local I/O in Action/support/sparse-file/README",id:"Lab/I/O/Local I/O in Action/support/sparse-file/README",title:"Sparse File",description:"The swiss_cheese.sparse file is a sparse file.",source:"@site/docs/Lab/I/O/Local I/O in Action/support/sparse-file/README.md",sourceDirName:"Lab/I/O/Local I/O in Action/support/sparse-file",slug:"/Lab/I/O/Local I/O in Action/support/sparse-file/",permalink:"/operating-systems/Lab/I/O/Local I/O in Action/support/sparse-file/",draft:!1,tags:[],version:"current",frontMatter:{}},c={},p=[],l={toc:p};function f(e){let{components:t,...r}=e;return(0,o.kt)("wrapper",(0,n.Z)({},l,r,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"sparse-file"},"Sparse File"),(0,o.kt)("p",null,"The ",(0,o.kt)("inlineCode",{parentName:"p"},"swiss_cheese.sparse")," file is a sparse file.\nIt stores 1 character of useful data followed by 10 bytes of spaces.\nThen another characters, then another 10 bytes of spaces, and so on."),(0,o.kt)("p",null,"Fill in the blanks in ",(0,o.kt)("inlineCode",{parentName:"p"},"solve.c")," to read the characters, concatenate them together and get the flag."))}f.isMDXComponent=!0}}]);