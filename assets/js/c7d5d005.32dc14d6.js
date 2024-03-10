"use strict";(self.webpackChunkos=self.webpackChunkos||[]).push([[37],{5680:(e,t,n)=>{n.d(t,{xA:()=>c,yg:()=>h});var a=n(6540);function r(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,a)}return n}function o(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){r(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function s(e,t){if(null==e)return{};var n,a,r=function(e,t){if(null==e)return{};var n,a,r={},i=Object.keys(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||(r[n]=e[n]);return r}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(a=0;a<i.length;a++)n=i[a],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(r[n]=e[n])}return r}var l=a.createContext({}),p=function(e){var t=a.useContext(l),n=t;return e&&(n="function"==typeof e?e(t):o(o({},t),e)),n},c=function(e){var t=p(e.components);return a.createElement(l.Provider,{value:t},e.children)},m="mdxType",g={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},d=a.forwardRef((function(e,t){var n=e.components,r=e.mdxType,i=e.originalType,l=e.parentName,c=s(e,["components","mdxType","originalType","parentName"]),m=p(n),d=r,h=m["".concat(l,".").concat(d)]||m[d]||g[d]||i;return n?a.createElement(h,o(o({ref:t},c),{},{components:n})):a.createElement(h,o({ref:t},c))}));function h(e,t){var n=arguments,r=t&&t.mdxType;if("string"==typeof e||r){var i=n.length,o=new Array(i);o[0]=d;var s={};for(var l in t)hasOwnProperty.call(t,l)&&(s[l]=t[l]);s.originalType=e,s[m]="string"==typeof e?e:r,o[1]=s;for(var p=2;p<i;p++)o[p]=n[p];return a.createElement.apply(null,o)}return a.createElement.apply(null,n)}d.displayName="MDXCreateElement"},5846:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>l,contentTitle:()=>o,default:()=>g,frontMatter:()=>i,metadata:()=>s,toc:()=>p});var a=n(8168),r=(n(6540),n(5680));const i={},o="Client-Server Model",s={unversionedId:"Lab/IO/client-server-model",id:"Lab/IO/client-server-model",title:"Client-Server Model",description:"Up to now, we've avoided code snippets using TCP.",source:"@site/docs/Lab/IO/client-server-model.md",sourceDirName:"Lab/IO",slug:"/Lab/IO/client-server-model",permalink:"/operating-systems/Lab/IO/client-server-model",draft:!1,tags:[],version:"current",frontMatter:{},sidebar:"sidebar",previous:{title:"Networking 101",permalink:"/operating-systems/Lab/IO/networking-101"},next:{title:"Beyond Network Sockets",permalink:"/operating-systems/Lab/IO/beyond-network-sockets"}},l={},p=[{value:"Server vs Client",id:"server-vs-client",level:2},{value:"Establishing the Connection",id:"establishing-the-connection",level:2},{value:"Steps Taken by the Server",id:"steps-taken-by-the-server",level:3},{value:"Steps Taken by the Client",id:"steps-taken-by-the-client",level:3},{value:"Practice: Client",id:"practice-client",level:3},{value:"Practice: Just a Little Bit More Deluge",id:"practice-just-a-little-bit-more-deluge",level:2}],c={toc:p},m="wrapper";function g(e){let{components:t,...i}=e;return(0,r.yg)(m,(0,a.A)({},c,i,{components:t,mdxType:"MDXLayout"}),(0,r.yg)("h1",{id:"client-server-model"},"Client-Server Model"),(0,r.yg)("p",null,"Up to now, we've avoided code snippets using TCP.\nNot anymore.\nKeep in mind that all socket functions in the Berkeley API have very detailed and informative ",(0,r.yg)("inlineCode",{parentName:"p"},"man")," pages.\nFor example, here are the ",(0,r.yg)("inlineCode",{parentName:"p"},"man")," pages for ",(0,r.yg)("a",{parentName:"p",href:"https://linux.die.net/man/2/sendto"},(0,r.yg)("inlineCode",{parentName:"a"},"sendto()"))," and ",(0,r.yg)("a",{parentName:"p",href:"https://linux.die.net/man/2/recvfrom"},(0,r.yg)("inlineCode",{parentName:"a"},"recvfrom()"))," that are used with UDP sockets."),(0,r.yg)("p",null,"Going back to our ",(0,r.yg)("a",{parentName:"p",href:"/operating-systems/Lab/IO/remote-io#one-browser---many-connections"},"initial example")," with how the browser gets data from ",(0,r.yg)("a",{parentName:"p",href:"https://open-education-hub.github.io/operating-systems/"},"https://open-education-hub.github.io/operating-systems/"),", by now we know the preferred method for transferring text is TCP."),(0,r.yg)("p",null,"Unlike UDP, TCP is ",(0,r.yg)("strong",{parentName:"p"},"connection-oriented"),".\nThis is why, in the example with the browser, we kept using the word ",(0,r.yg)("strong",{parentName:"p"},"connection"),".\nWhat's different from UDP is that this connection is ",(0,r.yg)("strong",{parentName:"p"},"bidirectional"),", so we can both ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/send.2.html"},(0,r.yg)("inlineCode",{parentName:"a"},"send()"))," and receive (",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/recv.2.html"},(0,r.yg)("inlineCode",{parentName:"a"},"recv()")),") data from it.\nNotice that the syscalls have changed.\nWe were using ",(0,r.yg)("inlineCode",{parentName:"p"},"sendto()")," and ",(0,r.yg)("inlineCode",{parentName:"p"},"recvfrom()")," for UDP, and now we're using ",(0,r.yg)("inlineCode",{parentName:"p"},"send()")," and ",(0,r.yg)("inlineCode",{parentName:"p"},"recv()")," for TCP.\nAnd yes, despite the fact that we're using Python, these are syscalls.\nYou saw them in C when you solved the ",(0,r.yg)("a",{parentName:"p",href:"/operating-systems/Lab/IO/remote-io#practice-network-sockets-challenge"},"challenge"),"."),(0,r.yg)("h2",{id:"server-vs-client"},"Server vs Client"),(0,r.yg)("p",null,"When discussing servers and clients, the server is the passive actor.\nIt may have some data and wait for clients to ask for this data.\nOr it may require some data and wait for clients to send it.\nEither way, it is ",(0,r.yg)("strong",{parentName:"p"},"listening")," for connections."),(0,r.yg)("p",null,"The client is the active actor, being the one who initiates the connection."),(0,r.yg)("p",null,(0,r.yg)("a",{parentName:"p",href:"/operating-systems/Lab/IO/quiz/client-server-sender-receiver"},"Quiz")),(0,r.yg)("h2",{id:"establishing-the-connection"},"Establishing the Connection"),(0,r.yg)("p",null,"There is a series of steps that a client and most importantly a server must take to establish a TCP connection."),(0,r.yg)("h3",{id:"steps-taken-by-the-server"},"Steps Taken by the Server"),(0,r.yg)("ol",null,(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Call ",(0,r.yg)("inlineCode",{parentName:"p"},"socket()")," to create a socket.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},(0,r.yg)("inlineCode",{parentName:"p"},"bind()")," this socket to an IP and a port.\nUp to now, this is nothing new.\nHowever, with TCP sockets, ",(0,r.yg)("inlineCode",{parentName:"p"},"bind()")," doesn't automatically make them listen for connections.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Call ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/listen.2.html"},(0,r.yg)("inlineCode",{parentName:"a"},"listen()"))," to make the socket ready to receive connections.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Call ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/accept.2.html"},(0,r.yg)("inlineCode",{parentName:"a"},"accept()"))," to set up one connection initiated by a client.\nFrom now, the connection is established.\n",(0,r.yg)("inlineCode",{parentName:"p"},"accept()")," returns a new socket, which will be further used for communication between the server and the client.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Exchange messages with the client.\nThe server can both read messages from the client and send responses back using the same socket returned by ",(0,r.yg)("inlineCode",{parentName:"p"},"accept()"),".\nWhen done, ",(0,r.yg)("inlineCode",{parentName:"p"},"close()")," the socket returned by accept and repeat from step ",(0,r.yg)("inlineCode",{parentName:"p"},"4"),"."))),(0,r.yg)("h3",{id:"steps-taken-by-the-client"},"Steps Taken by the Client"),(0,r.yg)("ol",null,(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Call ",(0,r.yg)("inlineCode",{parentName:"p"},"socket()")," to create a socket.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Use ",(0,r.yg)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/connect.2.html"},(0,r.yg)("inlineCode",{parentName:"a"},"connect()")),' to... you guessed it: connect to the server.\nThis step is like an "answer" to step ',(0,r.yg)("inlineCode",{parentName:"p"},"4")," from the server.\nWe can say that the server ",(0,r.yg)("inlineCode",{parentName:"p"},"accept()"),"s a ",(0,r.yg)("inlineCode",{parentName:"p"},"connect()")," request from the client.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Exchange messages with the server.\nThe client can both send messages to the server and read responses from it using the same socket created during step ",(0,r.yg)("inlineCode",{parentName:"p"},"1"),"."))),(0,r.yg)("p",null,"Below is an image summarising the steps above:"),(0,r.yg)("p",null,(0,r.yg)("img",{alt:"Steps to Establish a Connection",src:n(5339).A})),(0,r.yg)("h3",{id:"practice-client"},"Practice: Client"),(0,r.yg)("p",null,"Navigate to ",(0,r.yg)("inlineCode",{parentName:"p"},"support/client-server/"),".\nHere you will find a minimalistic server implementation in ",(0,r.yg)("inlineCode",{parentName:"p"},"server.py"),"."),(0,r.yg)("ol",null,(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Read the code and identify the steps outlined above.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Now fill in the code in ",(0,r.yg)("inlineCode",{parentName:"p"},"client.c")," or ",(0,r.yg)("inlineCode",{parentName:"p"},"client.py")," to be able to send messages to the server and receive responses from it.\nRun multiple clients.")),(0,r.yg)("li",{parentName:"ol"},(0,r.yg)("p",{parentName:"li"},"Run the code, then run ",(0,r.yg)("inlineCode",{parentName:"p"},"lsof")," and ",(0,r.yg)("inlineCode",{parentName:"p"},"netstat")," in other terminals to identify the file descriptor corresponding to the listening file descriptor."))),(0,r.yg)("h2",{id:"practice-just-a-little-bit-more-deluge"},"Practice: Just a Little Bit More Deluge"),(0,r.yg)("p",null,"We've already said that Deluge uses an ",(0,r.yg)("a",{parentName:"p",href:"/operating-systems/Lab/IO/networking-101#practice-encapsulation-example-deluge-revived"},"abstraction over TCP"),' to handle socket operations, so we don\'t have the luxury of seeing it perform remote I/O "manually".\nHowever, there are a few instances where Deluge uses socket operations itself, mostly for testing purposes.'),(0,r.yg)("p",null,"Deluge saves its PIDs (it can spawn multiple processes) and ports in a file.\nFind the ",(0,r.yg)("inlineCode",{parentName:"p"},"is_daemon_running()")," method.\nThis method uses the aforementioned file to check if a given process is Deluge or some other process.\nTo do this, it ",(0,r.yg)("inlineCode",{parentName:"p"},"connect()"),"s to that process's socket.\nIf it can't, then that process is not Deluge.\nOtherwise, it is Deluge and that connection is immediately closed :))\nThis may sound like a stupid way of checking whether a process is Deluge or not, but ",(0,r.yg)("em",{parentName:"p"},"if it's stupid and it works, then it's not stupid!")))}g.isMDXComponent=!0},5339:(e,t,n)=>{n.d(t,{A:()=>a});const a=n.p+"assets/images/connection-establishment-05ca0959a59f3204b866855631182875.svg"}}]);