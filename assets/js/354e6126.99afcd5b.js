"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[93463],{3905:(e,t,a)=>{a.d(t,{Zo:()=>l,kt:()=>u});var n=a(67294);function r(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function o(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var n=Object.getOwnPropertySymbols(e);t&&(n=n.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,n)}return a}function i(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?o(Object(a),!0).forEach((function(t){r(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):o(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function s(e,t){if(null==e)return{};var a,n,r=function(e,t){if(null==e)return{};var a,n,r={},o=Object.keys(e);for(n=0;n<o.length;n++)a=o[n],t.indexOf(a)>=0||(r[a]=e[a]);return r}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(n=0;n<o.length;n++)a=o[n],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(r[a]=e[a])}return r}var p=n.createContext({}),c=function(e){var t=n.useContext(p),a=t;return e&&(a="function"==typeof e?e(t):i(i({},t),e)),a},l=function(e){var t=c(e.components);return n.createElement(p.Provider,{value:t},e.children)},m="mdxType",h={inlineCode:"code",wrapper:function(e){var t=e.children;return n.createElement(n.Fragment,{},t)}},d=n.forwardRef((function(e,t){var a=e.components,r=e.mdxType,o=e.originalType,p=e.parentName,l=s(e,["components","mdxType","originalType","parentName"]),m=c(a),d=r,u=m["".concat(p,".").concat(d)]||m[d]||h[d]||o;return a?n.createElement(u,i(i({ref:t},l),{},{components:a})):n.createElement(u,i({ref:t},l))}));function u(e,t){var a=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var o=a.length,i=new Array(o);i[0]=d;var s={};for(var p in t)hasOwnProperty.call(t,p)&&(s[p]=t[p]);s.originalType=e,s[m]="string"==typeof e?e:r,i[1]=s;for(var c=2;c<o;c++)i[c]=a[c];return n.createElement.apply(null,i)}return n.createElement.apply(null,a)}d.displayName="MDXCreateElement"},96028:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>p,contentTitle:()=>i,default:()=>h,frontMatter:()=>o,metadata:()=>s,toc:()=>c});var n=a(87462),r=(a(67294),a(3905));const o={},i="Copy-on-Write",s={unversionedId:"Lab/Compute/Hardware Perspective/content/copy-on-write",id:"Lab/Compute/Hardware Perspective/content/copy-on-write",title:"Copy-on-Write",description:"So far you know that the parent and child process have separate virtual address spaces.",source:"@site/docs/Lab/Compute/Hardware Perspective/content/copy-on-write.md",sourceDirName:"Lab/Compute/Hardware Perspective/content",slug:"/Lab/Compute/Hardware Perspective/content/copy-on-write",permalink:"/operating-systems/Lab/Compute/Hardware Perspective/content/copy-on-write",draft:!1,tags:[],version:"current",frontMatter:{}},p={},c=[{value:"Practice",id:"practice",level:2}],l={toc:c},m="wrapper";function h(e){let{components:t,...o}=e;return(0,r.kt)(m,(0,n.Z)({},l,o,{components:t,mdxType:"MDXLayout"}),(0,r.kt)("h1",{id:"copy-on-write"},"Copy-on-Write"),(0,r.kt)("p",null,'So far you know that the parent and child process have separate virtual address spaces.\nBut how are they created, namely how are they "separated"?\nAnd what about the ',(0,r.kt)("strong",{parentName:"p"},"PAS (physical address space)"),"?\nOf course we would like the stack of the parent, for example, to be physically distinct from that of the child so they can execute different functions and use different local variables."),(0,r.kt)("p",null,"But should ",(0,r.kt)("strong",{parentName:"p"},"all")," memory sections from the PAS of the parent be distinct from that of the child?\nWhat about some read-only memory sections, such as ",(0,r.kt)("inlineCode",{parentName:"p"},".text")," and ",(0,r.kt)("inlineCode",{parentName:"p"},".rodata"),"?\nAnd what about the heap, where the child ",(0,r.kt)("em",{parentName:"p"},"may")," use some data previously written by the parent and then override it with its own data."),(0,r.kt)("p",null,"The answer to all of these questions is a core mechanism of multi-process operating systems called ",(0,r.kt)("strong",{parentName:"p"},"Copy-on-Write"),".\nIt works according to one very simple principle:"),(0,r.kt)("blockquote",null,(0,r.kt)("p",{parentName:"blockquote"},"The VAS of the child process initially points to the same PAS as that of the parent.\nA (physical) frame is only duplicated by the child when it attempts to ",(0,r.kt)("strong",{parentName:"p"},"write")," data to it.")),(0,r.kt)("p",null,"This ensures that read-only sections remain shared, while writable sections are shared as long as their contents remain unchanged.\nWhen changes happen, the process making the change receives a unique frame as a modified copy of the original frame ",(0,r.kt)("em",{parentName:"p"},"on demand"),"."),(0,r.kt)("p",null,"In the image below we have the state of the child and parent processes right after ",(0,r.kt)("inlineCode",{parentName:"p"},"fork()")," returns in both of them.\nSee how each has its own VAS, both of them being mapped to (mostly) the same PAS."),(0,r.kt)("p",null,(0,r.kt)("img",{alt:"Copy-on-Write",src:a(5672).Z,width:"782",height:"402"})),(0,r.kt)("p",null,"When one process writes data to a writeable page (in our case, the child writes to a heap page), the frame to which it corresponds is first duplicated.\nThen the process' page table points the page to the newly copied frame, as you can see in the image below."),(0,r.kt)("p",null,(0,r.kt)("img",{alt:"Copy-on-Write",src:a(55495).Z,width:"821",height:"363"})),(0,r.kt)("p",null,(0,r.kt)("strong",{parentName:"p"},"Be careful!"),"\nDo not confuse ",(0,r.kt)("strong",{parentName:"p"},"copy-on-write")," with ",(0,r.kt)("strong",{parentName:"p"},"demand paging"),".\nRemember from the ",(0,r.kt)("a",{parentName:"p",href:"../../../data/"},"Data chapter")," that ",(0,r.kt)("strong",{parentName:"p"},"demand paging")," means that when you allocate memory the OS allocates virtual memory that remains unmapped to physical memory until it's used.\nOn the other hand, ",(0,r.kt)("strong",{parentName:"p"},"copy-on-write")," posits that the virtual memory is already mapped to some frames.\nThese frames are only duplicated when one of the processes attempts to write data to them."),(0,r.kt)("h2",{id:"practice"},"Practice"),(0,r.kt)("p",null,"Now let's see the copy-on-write mechanism in practice.\nKeep in mind that ",(0,r.kt)("inlineCode",{parentName:"p"},"fork()")," is a function used to create a process."),(0,r.kt)("p",null,"Open two terminals (or better: use ",(0,r.kt)("a",{parentName:"p",href:"https://github.com/tmux/tmux/wiki"},(0,r.kt)("inlineCode",{parentName:"a"},"tmux")),").\nIn one of them compile and run the code in ",(0,r.kt)("inlineCode",{parentName:"p"},"support/fork-faults/fork_faults.c"),".\nAfter each time you press ",(0,r.kt)("inlineCode",{parentName:"p"},"Enter")," in the first terminal window, run the following command in the second window:"),(0,r.kt)("pre",null,(0,r.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../lab/support/fork-faults$ ps -o min_flt,maj_flt -p $(pidof fork_faults)\n")),(0,r.kt)("p",null,"It will show you the number of minor and major page faults performed by the ",(0,r.kt)("inlineCode",{parentName:"p"},"fork_faults")," process and its child."),(0,r.kt)("p",null,(0,r.kt)("a",{parentName:"p",href:"/operating-systems/Lab/Compute/Hardware%20Perspective/quiz/parent-faults-before-fork"},"Quiz 1")),(0,r.kt)("p",null,"Note that after ",(0,r.kt)("inlineCode",{parentName:"p"},"fork()"),"-ing, there is a second row in the output of ",(0,r.kt)("inlineCode",{parentName:"p"},"ps"),".\nThat corresponds to the child process.\nThe first one still corresponds to the parent."),(0,r.kt)("p",null,(0,r.kt)("a",{parentName:"p",href:"/operating-systems/Lab/Compute/Hardware%20Perspective/quiz/child-faults-after-write"},"Quiz 2")),(0,r.kt)("p",null,"Now it should be clear how demand paging differs from copy-on-write.\nShared memory is a similar concept.\nIt's a way of marking certain allocated pages so that copy-on-write is disabled.\nAs you may imagine, changes made by the parent to this memory are visible to the child and vice-versa.\nYou can learn more about it ",(0,r.kt)("a",{parentName:"p",href:"/operating-systems/Lab/Compute/Hardware%20Perspective/content/arena#shared-memory"},"its dedicated section in the Arena"),"."))}h.isMDXComponent=!0},55495:(e,t,a)=>{a.d(t,{Z:()=>n});const n=a.p+"assets/images/copy-on-write-final-2dfe1835636c0b38b11fed42b5b690d2.svg"},5672:(e,t,a)=>{a.d(t,{Z:()=>n});const n=a.p+"assets/images/copy-on-write-initial-a3673d26b2087aaacf630bc556e0a6a8.svg"}}]);