"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[57321],{3905:(e,t,n)=>{n.d(t,{Zo:()=>s,kt:()=>h});var r=n(67294);function o(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function a(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function i(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?a(Object(n),!0).forEach((function(t){o(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):a(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},a=Object.keys(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);for(r=0;r<a.length;r++)n=a[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var u=r.createContext({}),c=function(e){var t=r.useContext(u),n=t;return e&&(n="function"==typeof e?e(t):i(i({},t),e)),n},s=function(e){var t=c(e.components);return r.createElement(u.Provider,{value:t},e.children)},d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},p=r.forwardRef((function(e,t){var n=e.components,o=e.mdxType,a=e.originalType,u=e.parentName,s=l(e,["components","mdxType","originalType","parentName"]),p=c(n),h=o,m=p["".concat(u,".").concat(h)]||p[h]||d[h]||a;return n?r.createElement(m,i(i({ref:t},s),{},{components:n})):r.createElement(m,i({ref:t},s))}));function h(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var a=n.length,i=new Array(a);i[0]=p;var l={};for(var u in t)hasOwnProperty.call(t,u)&&(l[u]=t[u]);l.originalType=e,l.mdxType="string"==typeof e?e:o,i[1]=l;for(var c=2;c<a;c++)i[c]=n[c];return r.createElement.apply(null,i)}return r.createElement.apply(null,n)}p.displayName="MDXCreateElement"},5585:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>u,contentTitle:()=>i,default:()=>d,frontMatter:()=>a,metadata:()=>l,toc:()=>c});var r=n(87462),o=(n(67294),n(3905));const a={},i="Both Condition and Mutex",l={unversionedId:"Lab/Compute/Scheduling/quiz/notify-only-with-mutex",id:"Lab/Compute/Scheduling/quiz/notify-only-with-mutex",title:"Both Condition and Mutex",description:"Question Text",source:"@site/docs/Lab/Compute/Scheduling/quiz/notify-only-with-mutex.md",sourceDirName:"Lab/Compute/Scheduling/quiz",slug:"/Lab/Compute/Scheduling/quiz/notify-only-with-mutex",permalink:"/operating-systems/Lab/Compute/Scheduling/quiz/notify-only-with-mutex",draft:!1,tags:[],version:"current",frontMatter:{}},u={},c=[{value:"Question Text",id:"question-text",level:2},{value:"Question Answers",id:"question-answers",level:2},{value:"Feedback",id:"feedback",level:2}],s={toc:c};function d(e){let{components:t,...n}=e;return(0,o.kt)("wrapper",(0,r.Z)({},s,n,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"both-condition-and-mutex"},"Both Condition and Mutex"),(0,o.kt)("h2",{id:"question-text"},"Question Text"),(0,o.kt)("p",null,"Can we only use a mutex when signalling an event from one thread to another in?"),(0,o.kt)("h2",{id:"question-answers"},"Question Answers"),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"No, because this would imply that the signalling thread would ",(0,o.kt)("inlineCode",{parentName:"li"},"unlock()")," the mutex, that the signalled thread attempts to ",(0,o.kt)("inlineCode",{parentName:"li"},"lock()"),", which is an undefined behaviour")),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},"No, because it will result in a deadlock where the both threads will be waiting for each other"),(0,o.kt)("li",{parentName:"ul"},"Yes, because only one thread can modify the shared variables in order to maintain their integrity"),(0,o.kt)("li",{parentName:"ul"},"Yes and this would yield better performance because the threads would only wait for one object: the mutex ")),(0,o.kt)("h2",{id:"feedback"},"Feedback"),(0,o.kt)("p",null,"In some implementations, such as ",(0,o.kt)("a",{parentName:"p",href:"https://pubs.opengroup.org/onlinepubs/9699919799/functions/pthread_mutex_lock.html"},"POSIX threads (pthreads)"),", calling ",(0,o.kt)("inlineCode",{parentName:"p"},"unlock()")," from another thread than that which called ",(0,o.kt)("inlineCode",{parentName:"p"},"lock()")," can result in an undefined behaviour.\nFor this reason, it is unsafe to only use a mutex as a notification mechanism.\nIn addition, a mutex cannot notify more than one thread at once, if we so desire.\nMutexes are only meant to be used to isolate a critical section within the same thread."))}d.isMDXComponent=!0}}]);