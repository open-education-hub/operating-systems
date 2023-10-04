"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[9836],{3905:(e,t,a)=>{a.d(t,{Zo:()=>p,kt:()=>d});var r=a(7294);function n(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function s(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,r)}return a}function o(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?s(Object(a),!0).forEach((function(t){n(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):s(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function i(e,t){if(null==e)return{};var a,r,n=function(e,t){if(null==e)return{};var a,r,n={},s=Object.keys(e);for(r=0;r<s.length;r++)a=s[r],t.indexOf(a)>=0||(n[a]=e[a]);return n}(e,t);if(Object.getOwnPropertySymbols){var s=Object.getOwnPropertySymbols(e);for(r=0;r<s.length;r++)a=s[r],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(n[a]=e[a])}return n}var l=r.createContext({}),c=function(e){var t=r.useContext(l),a=t;return e&&(a="function"==typeof e?e(t):o(o({},t),e)),a},p=function(e){var t=c(e.components);return r.createElement(l.Provider,{value:t},e.children)},m="mdxType",u={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},f=r.forwardRef((function(e,t){var a=e.components,n=e.mdxType,s=e.originalType,l=e.parentName,p=i(e,["components","mdxType","originalType","parentName"]),m=c(a),f=n,d=m["".concat(l,".").concat(f)]||m[f]||u[f]||s;return a?r.createElement(d,o(o({ref:t},p),{},{components:a})):r.createElement(d,o({ref:t},p))}));function d(e,t){var a=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var s=a.length,o=new Array(s);o[0]=f;var i={};for(var l in t)hasOwnProperty.call(t,l)&&(i[l]=t[l]);i.originalType=e,i[m]="string"==typeof e?e:n,o[1]=i;for(var c=2;c<s;c++)o[c]=a[c];return r.createElement.apply(null,o)}return r.createElement.apply(null,a)}f.displayName="MDXCreateElement"},8020:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>l,contentTitle:()=>o,default:()=>u,frontMatter:()=>s,metadata:()=>i,toc:()=>c});var r=a(7462),n=(a(7294),a(3905));const s={},o="Modern Software Stacks",i={unversionedId:"Lab/Software Stack/modern-sw-stack",id:"Lab/Software Stack/modern-sw-stack",title:"Modern Software Stacks",description:"Most modern computing systems use a software stack such as the one in the figure below:",source:"@site/docs/Lab/Software Stack/modern-sw-stack.md",sourceDirName:"Lab/Software Stack",slug:"/Lab/Software Stack/modern-sw-stack",permalink:"/operating-systems/325/Lab/Software Stack/modern-sw-stack",draft:!1,tags:[],version:"current",frontMatter:{},sidebar:"sidebar",previous:{title:"Software Stack",permalink:"/operating-systems/325/Lab/Software Stack/overview"},next:{title:"Analyzing the Software Stack",permalink:"/operating-systems/325/Lab/Software Stack/basic-syscall"}},l={},c=[],p={toc:c},m="wrapper";function u(e){let{components:t,...s}=e;return(0,n.kt)(m,(0,r.Z)({},p,s,{components:t,mdxType:"MDXLayout"}),(0,n.kt)("h1",{id:"modern-software-stacks"},"Modern Software Stacks"),(0,n.kt)("p",null,"Most modern computing systems use a software stack such as the one in the figure below:"),(0,n.kt)("p",null,(0,n.kt)("img",{alt:"Modern Software Stack",src:a(2148).Z,width:"542",height:"512"})),(0,n.kt)("p",null,"This modern software stack allows fast development and provides a rich set of applications to the user."),(0,n.kt)("p",null,"The basic software component is the ",(0,n.kt)("strong",{parentName:"p"},"operating system")," (OS) (technically the operating system ",(0,n.kt)("strong",{parentName:"p"},"kernel"),").\nThe OS provides the fundamental primitives to interact with hardware (read and write data) and to manage the running of applications (such as memory allocation, thread creation, scheduling).\nThese primitives form the ",(0,n.kt)("strong",{parentName:"p"},"system call API")," or ",(0,n.kt)("strong",{parentName:"p"},"system API"),".\nAn item in the system call API, i.e. the equivalent of a function call that triggers the execution of a functionality in the operating system, is a ",(0,n.kt)("strong",{parentName:"p"},"system call"),"."),(0,n.kt)("p",null,"The system call API is well-defined, stable and complete: it exposes the entire functionality of the operating system and hardware.\nHowever, it is also minimalistic with respect to features, and it provides a low-level (close to hardware) specification, making it cumbersome to use and ",(0,n.kt)("strong",{parentName:"p"},"not portable"),"."),(0,n.kt)("p",null,"Due to the downsides of the system call API, a basic library, the ",(0,n.kt)("strong",{parentName:"p"},"standard C library")," (also called ",(0,n.kt)("strong",{parentName:"p"},"libc"),"), is built on top of it.\nBecause the system call API uses an OS-specific calling convention, the standard C library typically wraps each system call into an equivalent function call, following a portable calling convention.\nMore than these wrappers, the standard C library provides its own API that is typically portable.\nPart of the API exposed by the standard C library is the ",(0,n.kt)("strong",{parentName:"p"},"standard C API"),", also called ",(0,n.kt)("strong",{parentName:"p"},"ANSI C")," or ",(0,n.kt)("strong",{parentName:"p"},"ISO C"),";\nthis API is typically portable across all platforms (operating systems and hardware).\nThis API, going beyond system call wrappers, has several advantages:"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},"portability: irrespective of the underlying operating system (and system call API), the API is the same"),(0,n.kt)("li",{parentName:"ul"},"extensive features: string management, I/O formatting"),(0,n.kt)("li",{parentName:"ul"},"possibility of increased efficiency with techniques such as buffering, as we show later")))}u.isMDXComponent=!0},2148:(e,t,a)=>{a.d(t,{Z:()=>r});const r=a.p+"assets/images/modern-sw-stack-4a2427d07a59c3a6599305b8eedc43dd.svg"}}]);