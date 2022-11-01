"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[68463],{3905:(e,t,r)=>{r.d(t,{Zo:()=>u,kt:()=>f});var n=r(67294);function a(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function o(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,n)}return r}function s(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?o(Object(r),!0).forEach((function(t){a(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function i(e,t){if(null==e)return{};var r,n,a=function(e,t){if(null==e)return{};var r,n,a={},o=Object.keys(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||(a[r]=e[r]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(n=0;n<o.length;n++)r=o[n],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(a[r]=e[r])}return a}var c=n.createContext({}),l=function(e){var t=n.useContext(c),r=t;return e&&(r="function"==typeof e?e(t):s(s({},t),e)),r},u=function(e){var t=l(e.components);return n.createElement(c.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},d=n.forwardRef((function(e,t){var r=e.components,a=e.mdxType,o=e.originalType,c=e.parentName,u=i(e,["components","mdxType","originalType","parentName"]),d=l(r),f=a,h=d["".concat(c,".").concat(f)]||d[f]||p[f]||o;return r?n.createElement(h,s(s({ref:t},u),{},{components:r})):n.createElement(h,s({ref:t},u))}));function f(e,t){var r=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=r.length,s=new Array(o);s[0]=d;var i={};for(var c in t)hasOwnProperty.call(t,c)&&(i[c]=t[c]);i.originalType=e,i.mdxType="string"==typeof e?e:a,s[1]=i;for(var l=2;l<o;l++)s[l]=r[l];return n.createElement.apply(null,s)}return n.createElement.apply(null,r)}d.displayName="MDXCreateElement"},4061:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>c,contentTitle:()=>s,default:()=>p,frontMatter:()=>o,metadata:()=>i,toc:()=>l});var n=r(87462),a=(r(67294),r(3905));const o={},s="Seg Fault Exit Code",i={unversionedId:"Lab/Compute/Processes-threads-apache2/quiz/seg-fault-exit-code",id:"Lab/Compute/Processes-threads-apache2/quiz/seg-fault-exit-code",title:"Seg Fault Exit Code",description:"Question Text",source:"@site/docs/Lab/Compute/Processes-threads-apache2/quiz/seg-fault-exit-code.md",sourceDirName:"Lab/Compute/Processes-threads-apache2/quiz",slug:"/Lab/Compute/Processes-threads-apache2/quiz/seg-fault-exit-code",permalink:"/operating-systems/Lab/Compute/Processes-threads-apache2/quiz/seg-fault-exit-code",draft:!1,tags:[],version:"current",frontMatter:{}},c={},l=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],u={toc:l};function p(e){let{components:t,...r}=e;return(0,a.kt)("wrapper",(0,n.Z)({},u,r,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"seg-fault-exit-code"},"Seg Fault Exit Code"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"What is the exit code of the faulty child process spawned by ",(0,a.kt)("inlineCode",{parentName:"p"},"support/sum-array-bugs/seg-fault/sum_array_processes.d")," with more than 2 processes?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"11 because this is the code of the ",(0,a.kt)("inlineCode",{parentName:"li"},"SIGSEGV")," signal")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"11 because this code is always returned when a process ends with an error"),(0,a.kt)("li",{parentName:"ul"},"11 because this is the value of the least significant 4 bytes of the partial array sum calculated by the process"),(0,a.kt)("li",{parentName:"ul"},"6 because the child process was aborted")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"We can obtain the number of the signal that killed a child process via the second argument of the ",(0,a.kt)("inlineCode",{parentName:"p"},"waitpid")," syscall.\nWe can use the ",(0,a.kt)("inlineCode",{parentName:"p"},"WIFSIGNALED()")," and ",(0,a.kt)("inlineCode",{parentName:"p"},"WTERMSIG()")," marcros.\nBy doing so, we see the exit code of the faulty child process is 11.\nWe can then use the ",(0,a.kt)("inlineCode",{parentName:"p"},"kill -l")," command to view the code of each signal and ",(0,a.kt)("inlineCode",{parentName:"p"},"SIGSEGV")," has the code 11."))}p.isMDXComponent=!0}}]);