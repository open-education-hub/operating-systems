"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[48398],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>h});var r=n(67294);function a(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function o(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function u(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?o(Object(n),!0).forEach((function(t){a(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):o(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function i(e,t){if(null==e)return{};var n,r,a=function(e,t){if(null==e)return{};var n,r,a={},o=Object.keys(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||(a[n]=e[n]);return a}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(r=0;r<o.length;r++)n=o[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(a[n]=e[n])}return a}var s=r.createContext({}),l=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):u(u({},t),e)),n},c=function(e){var t=l(e.components);return r.createElement(s.Provider,{value:t},e.children)},p={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},d=r.forwardRef((function(e,t){var n=e.components,a=e.mdxType,o=e.originalType,s=e.parentName,c=i(e,["components","mdxType","originalType","parentName"]),d=l(n),h=a,m=d["".concat(s,".").concat(h)]||d[h]||p[h]||o;return n?r.createElement(m,u(u({ref:t},c),{},{components:n})):r.createElement(m,u({ref:t},c))}));function h(e,t){var n=arguments,a=t&&t.mdxType;if("string"==typeof e||a){var o=n.length,u=new Array(o);u[0]=d;var i={};for(var s in t)hasOwnProperty.call(t,s)&&(i[s]=t[s]);i.originalType=e,i.mdxType="string"==typeof e?e:a,u[1]=i;for(var l=2;l<o;l++)u[l]=n[l];return r.createElement.apply(null,u)}return r.createElement.apply(null,n)}d.displayName="MDXCreateElement"},52851:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>u,default:()=>p,frontMatter:()=>o,metadata:()=>i,toc:()=>l});var r=n(87462),a=(n(67294),n(3905));const o={},u="The Need for a COMPLETED Queue",i={unversionedId:"Lab/Compute/Processes/quiz/why-use-completed-queue",id:"Lab/Compute/Processes/quiz/why-use-completed-queue",title:"The Need for a COMPLETED Queue",description:"Question Text",source:"@site/docs/Lab/Compute/Processes/quiz/why-use-completed-queue.md",sourceDirName:"Lab/Compute/Processes/quiz",slug:"/Lab/Compute/Processes/quiz/why-use-completed-queue",permalink:"/operating-systems/Lab/Compute/Processes/quiz/why-use-completed-queue",draft:!1,tags:[],version:"current",frontMatter:{}},s={},l=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],c={toc:l};function p(e){let{components:t,...n}=e;return(0,a.kt)("wrapper",(0,r.Z)({},c,n,{components:t,mdxType:"MDXLayout"}),(0,a.kt)("h1",{id:"the-need-for-a-completed-queue"},"The Need for a COMPLETED Queue"),(0,a.kt)("h2",{id:"question-text"},"Question Text"),(0,a.kt)("p",null,"Why does the scheduler need a COMPLETED queue and not simply terminate one thread once its function finishes?"),(0,a.kt)("h2",{id:"question-answers"},"Question Answers"),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"The COMPLETED queue is an implementation preference.\nThe scheduler can expose the same functions without it"),(0,a.kt)("li",{parentName:"ul"},"Because the OS's scheduler may kill the main kernel-level thread unless we keep the user-level thread in a queue")),(0,a.kt)("ul",null,(0,a.kt)("li",{parentName:"ul"},"The COMPLETED queue is needed to save the value returned by the thread so that it can later be retrieved by ",(0,a.kt)("inlineCode",{parentName:"li"},"threads_join()"),".")),(0,a.kt)("h2",{id:"feedback"},"Feedback"),(0,a.kt)("p",null,"Take a look at the ",(0,a.kt)("inlineCode",{parentName:"p"},"handle_thread_start()")," function.\nIt is used by ",(0,a.kt)("inlineCode",{parentName:"p"},"threads_create()")," to start executing the given function.\nThis is a wrapper that calls the function associated with the thread (",(0,a.kt)("inlineCode",{parentName:"p"},"this->start_routine"),"), saves its result and then calls ",(0,a.kt)("inlineCode",{parentName:"p"},"threads_exit()"),"\nto store this result in the COMPLETED queue."))}p.isMDXComponent=!0}}]);