"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[80922],{3905:(e,t,n)=>{n.d(t,{Zo:()=>c,kt:()=>f});var r=n(67294);function o(e,t,n){return t in e?Object.defineProperty(e,t,{value:n,enumerable:!0,configurable:!0,writable:!0}):e[t]=n,e}function i(e,t){var n=Object.keys(e);if(Object.getOwnPropertySymbols){var r=Object.getOwnPropertySymbols(e);t&&(r=r.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),n.push.apply(n,r)}return n}function a(e){for(var t=1;t<arguments.length;t++){var n=null!=arguments[t]?arguments[t]:{};t%2?i(Object(n),!0).forEach((function(t){o(e,t,n[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(n)):i(Object(n)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(n,t))}))}return e}function l(e,t){if(null==e)return{};var n,r,o=function(e,t){if(null==e)return{};var n,r,o={},i=Object.keys(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||(o[n]=e[n]);return o}(e,t);if(Object.getOwnPropertySymbols){var i=Object.getOwnPropertySymbols(e);for(r=0;r<i.length;r++)n=i[r],t.indexOf(n)>=0||Object.prototype.propertyIsEnumerable.call(e,n)&&(o[n]=e[n])}return o}var s=r.createContext({}),p=function(e){var t=r.useContext(s),n=t;return e&&(n="function"==typeof e?e(t):a(a({},t),e)),n},c=function(e){var t=p(e.components);return r.createElement(s.Provider,{value:t},e.children)},h="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return r.createElement(r.Fragment,{},t)}},u=r.forwardRef((function(e,t){var n=e.components,o=e.mdxType,i=e.originalType,s=e.parentName,c=l(e,["components","mdxType","originalType","parentName"]),h=p(n),u=o,f=h["".concat(s,".").concat(u)]||h[u]||d[u]||i;return n?r.createElement(f,a(a({ref:t},c),{},{components:n})):r.createElement(f,a({ref:t},c))}));function f(e,t){var n=arguments,o=t&&t.mdxType;if("string"==typeof e||o){var i=n.length,a=new Array(i);a[0]=u;var l={};for(var s in t)hasOwnProperty.call(t,s)&&(l[s]=t[s]);l.originalType=e,l[h]="string"==typeof e?e:o,a[1]=l;for(var p=2;p<i;p++)a[p]=n[p];return r.createElement.apply(null,a)}return r.createElement.apply(null,n)}u.displayName="MDXCreateElement"},11988:(e,t,n)=>{n.r(t),n.d(t,{assets:()=>s,contentTitle:()=>a,default:()=>h,frontMatter:()=>i,metadata:()=>l,toc:()=>p});var r=n(87462),o=(n(67294),n(3905));const i={},a="Local I/O in Action",l={unversionedId:"Lab/I/O/Beyond Network Sockets/content/local-io-in-action",id:"Lab/I/O/Beyond Network Sockets/content/local-io-in-action",title:"Local I/O in Action",description:"Most of the time, file handling is a simple operation from the perspective of the application.",source:"@site/docs/Lab/I/O/Beyond Network Sockets/content/local-io-in-action.md",sourceDirName:"Lab/I/O/Beyond Network Sockets/content",slug:"/Lab/I/O/Beyond Network Sockets/content/local-io-in-action",permalink:"/operating-systems/Lab/I/O/Beyond Network Sockets/content/local-io-in-action",draft:!1,tags:[],version:"current",frontMatter:{}},s={},p=[{value:"Local I/O in Deluge",id:"local-io-in-deluge",level:2},{value:"Writing Data to Files",id:"writing-data-to-files",level:3},{value:"Error Handling",id:"error-handling",level:3},{value:"Reading Data from Files",id:"reading-data-from-files",level:3}],c={toc:p};function h(e){let{components:t,...i}=e;return(0,o.kt)("wrapper",(0,r.Z)({},c,i,{components:t,mdxType:"MDXLayout"}),(0,o.kt)("h1",{id:"local-io-in-action"},"Local I/O in Action"),(0,o.kt)("p",null,"Most of the time, file handling is a simple operation from the perspective of the application.\nWe've already looked at the ",(0,o.kt)("a",{parentName:"p",href:"https://www.deluge-torrent.org/"},"Deluge"),' Bittorrent client written during the Data lab.\nWe\'ll examine it once more, but this time from the perspective of its I/O operations.\nBeing a Bittorrent client, we expect it to deal with I/O in 4 ways.\nThere are 2 "local" types of operations:'),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"reading local files from the disk to be sent to other clients")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"writing the previously downloaded files to the disk"))),(0,o.kt)("p",null,'Simple, right?\nNow we\'ll only look at the "local" part: reading and writing data to/from the disk.\nThe remaining 2 actions are about network-related operations.'),(0,o.kt)("ul",null,(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"requesting files from other stations on the Web.\nThose files are then retained in Deluge's memory while they're being downloaded")),(0,o.kt)("li",{parentName:"ul"},(0,o.kt)("p",{parentName:"li"},"sending (parts of) files to other clients.\nThose files are first read from the disk, retained in memory for a while, and then sent over the internet."))),(0,o.kt)("p",null,"Networking is complementary to local I/O and we'll discuss it starting from a ",(0,o.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/Beyond%20Network%20Sockets/content/remote-io"},"future section"),"."),(0,o.kt)("h2",{id:"local-io-in-deluge"},"Local I/O in Deluge"),(0,o.kt)("p",null,"If you haven't done so in the Data lab, clone the ",(0,o.kt)("a",{parentName:"p",href:"https://github.com/deluge-torrent/deluge"},"Deluge repository"),"."),(0,o.kt)("h3",{id:"writing-data-to-files"},"Writing Data to Files"),(0,o.kt)("p",null,"Now find the ",(0,o.kt)("inlineCode",{parentName:"p"},"write_torrentfile()")," function in the repository."),(0,o.kt)("p",null,"It defines an inner function called ",(0,o.kt)("inlineCode",{parentName:"p"},"write_file()"),", which does the actual writing.\nNotice that is's very similar to the example we saw in ",(0,o.kt)("inlineCode",{parentName:"p"},"support/simple-file-operations/file_operations.py"),":"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-Python"},"with open(filepath, 'wb') as save_file:\n    save_file.write(filedump)\n")),(0,o.kt)("p",null,"The code above is the same as:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-Python"},"save_file = open(filepath, 'wb')\nsave_file.write(filedump)\nsave_file.close()\n")),(0,o.kt)("p",null,"The ",(0,o.kt)("inlineCode",{parentName:"p"},"with")," keyword is just a ",(0,o.kt)("em",{parentName:"p"},"context manager")," that makes sure ",(0,o.kt)("inlineCode",{parentName:"p"},"save_file"),' is also closed when its "body" finished.\nWriting the data is done simply by calling the ',(0,o.kt)("inlineCode",{parentName:"p"},"write()")," function.\nAs you've probably figured out, there's an entire ",(0,o.kt)("strong",{parentName:"p"},"sofware stack")," beneath this ",(0,o.kt)("inlineCode",{parentName:"p"},"write()")," function that sends the data first to libc and then to the kernel.\nFurthemore, the kernel itself has its own separate stack for handling I/O requests."),(0,o.kt)("p",null,(0,o.kt)("img",{alt:"Software Stacks Everywhere",src:n(21336).Z,width:"888",height:"500"})),(0,o.kt)("h3",{id:"error-handling"},"Error Handling"),(0,o.kt)("p",null,"What is noteworthy about this short snippet is the (slightly) bigger picture - the error handling:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-Python"},"try:\n    with open(filepath, 'wb') as save_file:\n        save_file.write(filedump)\nexcept OSError as ex:\n    log.error('Unable to save torrent file to: %s', ex)\n")),(0,o.kt)("p",null,"This is similar to the ",(0,o.kt)("a",{parentName:"p",href:"https://github.com/open-education-hub/operating-systems/blob/6c5082600239e5a6bfcb612f41986cf2660323bb/content/common/utils/utils.h#L23-L30"},(0,o.kt)("inlineCode",{parentName:"a"},"DIE()")," macro")," you have seen ",(0,o.kt)("strong",{parentName:"p"},"(and used, right?)")," throughout the labs, but less brutal.\nWhile the ",(0,o.kt)("inlineCode",{parentName:"p"},"DIE()")," macro kills the program upon encountering an error, Deluge's ",(0,o.kt)("inlineCode",{parentName:"p"},"try - except")," approach simply logs an error and continues.\nAs you might imagine, there is no silver bullet when it comes to error handling.\nWhat is important is that errors are somehow accounted for and not ignored."),(0,o.kt)("p",null,"This is especially true for I/O-related errors.\nBecause I/O handling means dealing with peripherals or devices outside the typical CPU-RAM interaction.\nThe more devices, the higher the complexity.\nThe higher the complexity, the higher the likelyhood of errors."),(0,o.kt)("p",null,(0,o.kt)("a",{parentName:"p",href:"/operating-systems/Lab/I/O/Beyond%20Network%20Sockets/quiz/local-io-errors"},"Quiz")),(0,o.kt)("h3",{id:"reading-data-from-files"},"Reading Data from Files"),(0,o.kt)("p",null,"Now find the ",(0,o.kt)("inlineCode",{parentName:"p"},"load_resume_data_file()")," function in the Deluge source code.\nIt is used when (re)starting to seed existing files to peers."),(0,o.kt)("p",null,'The function looks through all possible copies and backups of the file and loads them to a "torrent" format given by ',(0,o.kt)("a",{parentName:"p",href:"https://www.libtorrent.org/"},(0,o.kt)("inlineCode",{parentName:"a"},"libtorrent")),".\nFor this, it calls ",(0,o.kt)("inlineCode",{parentName:"p"},"lt.bdecode()"),"."),(0,o.kt)("p",null,"As before, error handling is important:"),(0,o.kt)("pre",null,(0,o.kt)("code",{parentName:"pre",className:"language-Python"},"try:\n    with open(_filepath, 'rb') as _file:\n        resume_data = lt.bdecode(_file.read())\nexcept (OSError, EOFError, RuntimeError) as ex:\n    if self.torrents:\n        log.warning('Unable to load %s: %s', _filepath, ex)\n    resume_data = None\n")),(0,o.kt)("p",null,"So now we know how Deluge handles local files.\nBut we still don't know how it gets those files from peers.\nWe'll find out how in the following sections."))}h.isMDXComponent=!0},21336:(e,t,n)=>{n.d(t,{Z:()=>r});const r=n.p+"assets/images/software-stacks-everywhere-3f33e8d01bec7787cdaad5752d91a4b4.jpeg"}}]);