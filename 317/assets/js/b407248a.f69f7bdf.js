"use strict";(self.webpackChunkso=self.webpackChunkso||[]).push([[1101],{3905:(e,t,a)=>{a.d(t,{Zo:()=>p,kt:()=>u});var l=a(7294);function n(e,t,a){return t in e?Object.defineProperty(e,t,{value:a,enumerable:!0,configurable:!0,writable:!0}):e[t]=a,e}function o(e,t){var a=Object.keys(e);if(Object.getOwnPropertySymbols){var l=Object.getOwnPropertySymbols(e);t&&(l=l.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),a.push.apply(a,l)}return a}function i(e){for(var t=1;t<arguments.length;t++){var a=null!=arguments[t]?arguments[t]:{};t%2?o(Object(a),!0).forEach((function(t){n(e,t,a[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(a)):o(Object(a)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(a,t))}))}return e}function r(e,t){if(null==e)return{};var a,l,n=function(e,t){if(null==e)return{};var a,l,n={},o=Object.keys(e);for(l=0;l<o.length;l++)a=o[l],t.indexOf(a)>=0||(n[a]=e[a]);return n}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(l=0;l<o.length;l++)a=o[l],t.indexOf(a)>=0||Object.prototype.propertyIsEnumerable.call(e,a)&&(n[a]=e[a])}return n}var s=l.createContext({}),c=function(e){var t=l.useContext(s),a=t;return e&&(a="function"==typeof e?e(t):i(i({},t),e)),a},p=function(e){var t=c(e.components);return l.createElement(s.Provider,{value:t},e.children)},m="mdxType",d={inlineCode:"code",wrapper:function(e){var t=e.children;return l.createElement(l.Fragment,{},t)}},k=l.forwardRef((function(e,t){var a=e.components,n=e.mdxType,o=e.originalType,s=e.parentName,p=r(e,["components","mdxType","originalType","parentName"]),m=c(a),k=n,u=m["".concat(s,".").concat(k)]||m[k]||d[k]||o;return a?l.createElement(u,i(i({ref:t},p),{},{components:a})):l.createElement(u,i({ref:t},p))}));function u(e,t){var a=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var o=a.length,i=new Array(o);i[0]=k;var r={};for(var s in t)hasOwnProperty.call(t,s)&&(r[s]=t[s]);r.originalType=e,r[m]="string"==typeof e?e:n,i[1]=r;for(var c=2;c<o;c++)i[c]=a[c];return l.createElement.apply(null,i)}return l.createElement.apply(null,a)}k.displayName="MDXCreateElement"},565:(e,t,a)=>{a.r(t),a.d(t,{assets:()=>s,contentTitle:()=>i,default:()=>d,frontMatter:()=>o,metadata:()=>r,toc:()=>c});var l=a(7462),n=(a(7294),a(3905));const o={},i="Memory Allocator",r={unversionedId:"Assignments/Memory Allocator/README",id:"Assignments/Memory Allocator/README",title:"Memory Allocator",description:"Objectives",source:"@site/docs/Assignments/Memory Allocator/README.md",sourceDirName:"Assignments/Memory Allocator",slug:"/Assignments/Memory Allocator/",permalink:"/operating-systems/317/Assignments/Memory Allocator/",draft:!1,tags:[],version:"current",frontMatter:{},sidebar:"sidebar",previous:{title:"Mini-libc",permalink:"/operating-systems/317/Assignments/Mini Libc/"},next:{title:"Parallel Graph",permalink:"/operating-systems/317/Assignments/Parallel Graph/"}},s={},c=[{value:"Objectives",id:"objectives",level:2},{value:"Statement",id:"statement",level:2},{value:"Support Code",id:"support-code",level:2},{value:"API",id:"api",level:2},{value:"Implementation",id:"implementation",level:2},{value:"Memory Alignment",id:"memory-alignment",level:3},{value:"Block Reuse",id:"block-reuse",level:3},{value:"<code>struct block_meta</code>",id:"struct-block_meta",level:4},{value:"Split Block",id:"split-block",level:4},{value:"Coalesce Blocks",id:"coalesce-blocks",level:4},{value:"Find Best Block",id:"find-best-block",level:4},{value:"Heap Preallocation",id:"heap-preallocation",level:3},{value:"Building Memory Allocator",id:"building-memory-allocator",level:2},{value:"Testing and Grading",id:"testing-and-grading",level:2},{value:"Debugging",id:"debugging",level:3},{value:"Resources",id:"resources",level:2}],p={toc:c},m="wrapper";function d(e){let{components:t,...o}=e;return(0,n.kt)(m,(0,l.Z)({},p,o,{components:t,mdxType:"MDXLayout"}),(0,n.kt)("h1",{id:"memory-allocator"},"Memory Allocator"),(0,n.kt)("h2",{id:"objectives"},"Objectives"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},"Learn the basics of memory management by implementing minimal versions of ",(0,n.kt)("inlineCode",{parentName:"li"},"malloc()"),", ",(0,n.kt)("inlineCode",{parentName:"li"},"calloc()"),", ",(0,n.kt)("inlineCode",{parentName:"li"},"realloc()"),", and ",(0,n.kt)("inlineCode",{parentName:"li"},"free()"),"."),(0,n.kt)("li",{parentName:"ul"},"Accommodate with the memory management syscalls in Linux: ",(0,n.kt)("inlineCode",{parentName:"li"},"brk()"),", ",(0,n.kt)("inlineCode",{parentName:"li"},"mmap()"),", and ",(0,n.kt)("inlineCode",{parentName:"li"},"munmap()"),"."),(0,n.kt)("li",{parentName:"ul"},"Understand the bottlenecks of memory allocation and how to reduce them.")),(0,n.kt)("h2",{id:"statement"},"Statement"),(0,n.kt)("p",null,"Build a minimalistic memory allocator that can be used to manually manage virtual memory.\nThe goal is to have a reliable library that accounts for explicit allocation, reallocation, and initialization of memory."),(0,n.kt)("h2",{id:"support-code"},"Support Code"),(0,n.kt)("p",null,"The support code consists of three directories:"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"allocator/")," will contain your solution based on the ",(0,n.kt)("inlineCode",{parentName:"li"},"osmem.h")," header file"),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"tests/")," contains the test suite and a Python script to verify your work"),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("inlineCode",{parentName:"li"},"utils/")," contains an implementation for ",(0,n.kt)("inlineCode",{parentName:"li"},"printf()")," function that does ",(0,n.kt)("strong",{parentName:"li"},"not")," use the heap")),(0,n.kt)("p",null,"The test suite consists of ",(0,n.kt)("inlineCode",{parentName:"p"},".c")," files that will be dynamically linked to your library, ",(0,n.kt)("inlineCode",{parentName:"p"},"libosmem.so"),".\nYou can find the sources in the ",(0,n.kt)("inlineCode",{parentName:"p"},"tests/src/")," directory.\nThe results of the previous run can be found in the ",(0,n.kt)("inlineCode",{parentName:"p"},"tests/out/")," directory and the reference files are in the ",(0,n.kt)("inlineCode",{parentName:"p"},"tests/ref/")," directory."),(0,n.kt)("p",null,"The automated checking is performed using ",(0,n.kt)("inlineCode",{parentName:"p"},"checker.py")," that runs each test and compares the syscalls made by the ",(0,n.kt)("inlineCode",{parentName:"p"},"os_*")," functions with the reference file, providing a diff if the test failed."),(0,n.kt)("h2",{id:"api"},"API"),(0,n.kt)("ol",null,(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},(0,n.kt)("inlineCode",{parentName:"p"},"void *os_malloc(size_t size)")),(0,n.kt)("p",{parentName:"li"},"Allocates ",(0,n.kt)("inlineCode",{parentName:"p"},"size")," bytes and returns a pointer to the allocated memory."),(0,n.kt)("p",{parentName:"li"},"Chunks of memory smaller than ",(0,n.kt)("inlineCode",{parentName:"p"},"MMAP_THRESHOLD")," are allocated with ",(0,n.kt)("inlineCode",{parentName:"p"},"brk()"),".\nBigger chunks are allocated using ",(0,n.kt)("inlineCode",{parentName:"p"},"mmap()"),".\nThe memory is uninitialized."),(0,n.kt)("ul",{parentName:"li"},(0,n.kt)("li",{parentName:"ul"},"Passing ",(0,n.kt)("inlineCode",{parentName:"li"},"0")," as ",(0,n.kt)("inlineCode",{parentName:"li"},"size")," will return ",(0,n.kt)("inlineCode",{parentName:"li"},"NULL"),"."))),(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},(0,n.kt)("inlineCode",{parentName:"p"},"void *os_calloc(size_t nmemb, size_t size)")),(0,n.kt)("p",{parentName:"li"},"Allocates memory for an array of ",(0,n.kt)("inlineCode",{parentName:"p"},"nmemb")," elements of ",(0,n.kt)("inlineCode",{parentName:"p"},"size")," bytes each and returns a pointer to the allocated memory."),(0,n.kt)("p",{parentName:"li"},"Chunks of memory smaller than ",(0,n.kt)("a",{parentName:"p",href:"https://man7.org/linux/man-pages/man2/getpagesize.2.html"},(0,n.kt)("inlineCode",{parentName:"a"},"page_size"))," are allocated with ",(0,n.kt)("inlineCode",{parentName:"p"},"brk()"),".\nBigger chunks are allocated using ",(0,n.kt)("inlineCode",{parentName:"p"},"mmap()"),".\nThe memory is set to zero."),(0,n.kt)("ul",{parentName:"li"},(0,n.kt)("li",{parentName:"ul"},"Passing ",(0,n.kt)("inlineCode",{parentName:"li"},"0")," as ",(0,n.kt)("inlineCode",{parentName:"li"},"nmemb")," or ",(0,n.kt)("inlineCode",{parentName:"li"},"size")," will return ",(0,n.kt)("inlineCode",{parentName:"li"},"NULL"),"."))),(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},(0,n.kt)("inlineCode",{parentName:"p"},"void *os_realloc(void *ptr, size_t size)")),(0,n.kt)("p",{parentName:"li"},"Changes the size of the memory block pointed to by ",(0,n.kt)("inlineCode",{parentName:"p"},"ptr")," to ",(0,n.kt)("inlineCode",{parentName:"p"},"size")," bytes.\nIf the size is smaller than the previously allocated size, the memory block will be truncated."),(0,n.kt)("p",{parentName:"li"},"If ",(0,n.kt)("inlineCode",{parentName:"p"},"ptr")," points to a block on heap, ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()")," will first try to expand the block, rather than moving it.\nOtherwise, the block will be reallocated and its contents copied."),(0,n.kt)("p",{parentName:"li"},"When attempting to expand a block followed by multiple free blocks, ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()")," will coalesce them one at a time and verify the condition for each.\nBlocks will remain coalesced even if the resulting block will not be big enough for the new size."),(0,n.kt)("p",{parentName:"li"},"Calling ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()")," on a block that has ",(0,n.kt)("inlineCode",{parentName:"p"},"STATUS_FREE")," should return ",(0,n.kt)("inlineCode",{parentName:"p"},"NULL"),".\nThis is a measure to prevent undefined behavior and make the implementation robust, it should not be considered a valid use case of ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()"),"."),(0,n.kt)("ul",{parentName:"li"},(0,n.kt)("li",{parentName:"ul"},"Passing ",(0,n.kt)("inlineCode",{parentName:"li"},"NULL")," as ",(0,n.kt)("inlineCode",{parentName:"li"},"ptr")," will have the same effect as ",(0,n.kt)("inlineCode",{parentName:"li"},"os_malloc(size)"),"."),(0,n.kt)("li",{parentName:"ul"},"Passing ",(0,n.kt)("inlineCode",{parentName:"li"},"0")," as ",(0,n.kt)("inlineCode",{parentName:"li"},"size")," will have the same effect as ",(0,n.kt)("inlineCode",{parentName:"li"},"os_free(ptr)"),"."))),(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},(0,n.kt)("inlineCode",{parentName:"p"},"void os_free(void *ptr)")),(0,n.kt)("p",{parentName:"li"},"Frees memory previously allocated by ",(0,n.kt)("inlineCode",{parentName:"p"},"os_malloc()"),", ",(0,n.kt)("inlineCode",{parentName:"p"},"os_calloc()")," or ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()"),"."),(0,n.kt)("p",{parentName:"li"},(0,n.kt)("inlineCode",{parentName:"p"},"os_free()")," will not return memory from the heap to the OS by calling ",(0,n.kt)("inlineCode",{parentName:"p"},"brk()"),", but rather mark it as free and reuse it in future allocations.\nIn the case of mapped memory blocks, ",(0,n.kt)("inlineCode",{parentName:"p"},"os_free()")," will call ",(0,n.kt)("inlineCode",{parentName:"p"},"munmap()"),".")),(0,n.kt)("li",{parentName:"ol"},(0,n.kt)("p",{parentName:"li"},"General"),(0,n.kt)("ul",{parentName:"li"},(0,n.kt)("li",{parentName:"ul"},"Allocations that increase the heap size will only expand the last block if it is free."),(0,n.kt)("li",{parentName:"ul"},"You are allowed to use ",(0,n.kt)("inlineCode",{parentName:"li"},"sbrk()")," instead of ",(0,n.kt)("inlineCode",{parentName:"li"},"brk()"),", in view of the fact that ",(0,n.kt)("a",{parentName:"li",href:"https://man7.org/linux/man-pages/man2/brk.2.html#NOTES"},"on Linux")," ",(0,n.kt)("inlineCode",{parentName:"li"},"sbrk()")," is implemented using the ",(0,n.kt)("inlineCode",{parentName:"li"},"brk()"),"."),(0,n.kt)("li",{parentName:"ul"},"You must check the error code returned by every syscall.\nYou can use the ",(0,n.kt)("inlineCode",{parentName:"li"},"DIE()")," macro for this.")))),(0,n.kt)("h2",{id:"implementation"},"Implementation"),(0,n.kt)("p",null,"An efficient implementation must keep data aligned, keep track of memory blocks and reuse freed blocks.\nThis can be further improved by reducing the number of syscalls and block operations."),(0,n.kt)("h3",{id:"memory-alignment"},(0,n.kt)("a",{parentName:"h3",href:"https://stackoverflow.com/a/381368"},"Memory Alignment")),(0,n.kt)("p",null,"Allocated memory should be aligned (i.e. all addresses are multiple of a given size).\nThis is a space-time trade-off because memory blocks are padded so each can be read in one transaction.\nIt also allows for atomicity when interacting with a block of memory."),(0,n.kt)("p",null,"All memory allocations should be aligned to ",(0,n.kt)("strong",{parentName:"p"},"8 bytes")," as required by 64 bit systems."),(0,n.kt)("h3",{id:"block-reuse"},"Block Reuse"),(0,n.kt)("h4",{id:"struct-block_meta"},(0,n.kt)("inlineCode",{parentName:"h4"},"struct block_meta")),(0,n.kt)("p",null,"We will consider a ",(0,n.kt)("strong",{parentName:"p"},"block")," to be a continuous zone of memory, allocated and managed by our implementation.\nThe structure ",(0,n.kt)("inlineCode",{parentName:"p"},"block_meta")," will be used to manage the metadata of a block.\nEach allocated zone will comprise of a ",(0,n.kt)("inlineCode",{parentName:"p"},"block_meta")," structure placed at the start, followed by data (payload).\nFor all functions, the returned address will be that of the ",(0,n.kt)("strong",{parentName:"p"},"payload")," (not the ",(0,n.kt)("inlineCode",{parentName:"p"},"block_meta")," structure)."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-C"},"typedef struct block_meta {\n    size_t size;\n    int status;\n    struct block_meta *next;\n} block_meta;\n")),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": Both the ",(0,n.kt)("inlineCode",{parentName:"p"},"struct block_meta")," and the payload of a block should be aligned to ",(0,n.kt)("strong",{parentName:"p"},"8 bytes"),"."),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": The checker uses the ",(0,n.kt)("inlineCode",{parentName:"p"},"size")," from ",(0,n.kt)("inlineCode",{parentName:"p"},"struct block_meta"),".\nUse ",(0,n.kt)("inlineCode",{parentName:"p"},"size")," to store the ",(0,n.kt)("strong",{parentName:"p"},"aligned size of the payload"),"."),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": Most compilers will automatically pad the structure, but you should still align it for portability."),(0,n.kt)("p",null,(0,n.kt)("img",{alt:"memory-block",src:a(7565).Z,width:"641",height:"191"})),(0,n.kt)("h4",{id:"split-block"},"Split Block"),(0,n.kt)("p",null,"Reusing memory blocks improves the allocator's performance, but might lead to ",(0,n.kt)("a",{parentName:"p",href:"https://www.tutorialspoint.com/difference-between-internal-fragmentation-and-external-fragmentation#:~:text=What%20is%20Internal%20Fragmentation%3F"},"Internal Memory Fragmentation"),".\nThis happens when we allocate a size smaller than all available free blocks.\nIf we use one larger block the remaining size of that block will be wasted since it cannot be used for another allocation."),(0,n.kt)("p",null,"To avoid this, a block should be truncated to the required size and the remaining bytes should be used to create a new free block."),(0,n.kt)("p",null,(0,n.kt)("img",{alt:"Split Block",src:a(5019).Z,width:"662",height:"282"})),(0,n.kt)("p",null,"The resulting free block should be reusable.\nThe split will not be performed if the remaining size (after reserving space for ",(0,n.kt)("inlineCode",{parentName:"p"},"block_meta")," structure and payload) is not big enough to fit another block (",(0,n.kt)("inlineCode",{parentName:"p"},"block_meta")," structure and at least ",(0,n.kt)("strong",{parentName:"p"},"1 byte")," of usable memory)."),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": Do not forget the alignment!"),(0,n.kt)("h4",{id:"coalesce-blocks"},"Coalesce Blocks"),(0,n.kt)("p",null,"There are cases when there is enough free memory for an allocation, but it is spread across multiple blocks that cannot be used.\nThis is called ",(0,n.kt)("a",{parentName:"p",href:"https://www.tutorialspoint.com/difference-between-internal-fragmentation-and-external-fragmentation#:~:text=What%20is%20External%20Fragmentation%3F"},"External Memory Fragmentation"),"."),(0,n.kt)("p",null,"One technique to reduce external memory fragmentation is ",(0,n.kt)("strong",{parentName:"p"},"block coalescing")," which implies merging adjacent free blocks to form a contiguous chunk."),(0,n.kt)("p",null,(0,n.kt)("img",{alt:"Coalesce Block Image",src:a(8506).Z,width:"661",height:"281"})),(0,n.kt)("p",null,"Coalescing will be used before searching for a block and in ",(0,n.kt)("inlineCode",{parentName:"p"},"os_realloc()")," to expand the current block when possible."),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": You might still need to split the block after coalesce."),(0,n.kt)("h4",{id:"find-best-block"},"Find Best Block"),(0,n.kt)("p",null,"Our aim is to reuse a free block with a size closer to what we need in order to reduce the number of future operations on it.\nThis strategy is called ",(0,n.kt)("strong",{parentName:"p"},"find best"),".\nOn every allocation we need to search the whole list of blocks and choose the best fitting free block."),(0,n.kt)("p",null,"In practice, it also uses a list of free blocks to avoid parsing all blocks, but this is out of the scope of the assignment."),(0,n.kt)("p",null,(0,n.kt)("em",{parentName:"p"},"Note"),": For consistent results, coalesce all adjacent free blocks before searching."),(0,n.kt)("h3",{id:"heap-preallocation"},"Heap Preallocation"),(0,n.kt)("p",null,"Heap is used in most modern programs.\nThis hints at the possibility of preallocating a relatively big chunk of memory (i.e. ",(0,n.kt)("strong",{parentName:"p"},"128 kilobytes"),") when the heap is used for the first time.\nThis reduces the number of future ",(0,n.kt)("inlineCode",{parentName:"p"},"brk()")," syscalls."),(0,n.kt)("p",null,"For example, if we try to allocate 1000 bytes we should first allocate a block of 128 kilobytes and then split it.\nOn future small allocations, we should proceed to split the preallocated chunk."),(0,n.kt)("h2",{id:"building-memory-allocator"},"Building Memory Allocator"),(0,n.kt)("p",null,"To build ",(0,n.kt)("inlineCode",{parentName:"p"},"libosmem.so"),", run ",(0,n.kt)("inlineCode",{parentName:"p"},"make")," in the ",(0,n.kt)("inlineCode",{parentName:"p"},"allocator/")," directory:"),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../content/assignments/mem-alloc$ cd allocator/\n\nstudent@os:~/.../assignments/mem-alloc/allocator$ make\n")),(0,n.kt)("h2",{id:"testing-and-grading"},"Testing and Grading"),(0,n.kt)("p",null,"The testing is automated and performed with the ",(0,n.kt)("inlineCode",{parentName:"p"},"checker.py")," script from the ",(0,n.kt)("inlineCode",{parentName:"p"},"tests/")," directory."),(0,n.kt)("p",null,"Before running ",(0,n.kt)("inlineCode",{parentName:"p"},"checker.py"),", you first have to build ",(0,n.kt)("inlineCode",{parentName:"p"},"libosmem.so")," in the ",(0,n.kt)("inlineCode",{parentName:"p"},"allocator/")," directory and generate the test binaries in ",(0,n.kt)("inlineCode",{parentName:"p"},"tests/bin"),"."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../content/assignments/mem-alloc$ cd tests/\n\nstudent@os:~/.../assignments/mem-alloc/tests$ make\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-all src/test-all.c -L../allocator -losmem\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-calloc-arrays src/test-calloc-arrays.c -L../allocator -losmem\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-calloc-block-reuse src/test-calloc-block-reuse.c -L../allocator -losmem\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-calloc-coalesce-big src/test-calloc-coalesce-big.c -L../allocator -losmem\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-calloc-coalesce src/test-calloc-coalesce.c -L../allocator -losmem\ngcc -I../utils -fPIC -Wall -Wextra -g -o bin/test-calloc-expand-block src/test-calloc-expand-block.c -L../allocator -losmem\n[...]\n\nstudent@os:~/.../assignments/mem-alloc/tests$ python checker.py\ntest-malloc-no-preallocate       ........................ passed ...   2\ntest-malloc-preallocate          ........................ passed ...   3\ntest-malloc-arrays               ........................ passed ...   5\ntest-malloc-block-reuse          ........................ passed ...   3\ntest-malloc-expand-block         ........................ passed ...   2\ntest-malloc-no-split             ........................ passed ...   2\ntest-malloc-split-one-block      ........................ passed ...   3\ntest-malloc-split-first          ........................ passed ...   2\ntest-malloc-split-last           ........................ passed ...   2\ntest-malloc-split-middle         ........................ passed ...   3\ntest-malloc-split-vector         ........................ passed ...   2\ntest-malloc-coalesce             ........................ passed ...   3\ntest-malloc-coalesce-big         ........................ passed ...   3\ntest-calloc-no-preallocate       ........................ passed ...   1\ntest-calloc-preallocate          ........................ passed ...   1\ntest-calloc-arrays               ........................ passed ...   5\ntest-calloc-block-reuse          ........................ passed ...   1\ntest-calloc-expand-block         ........................ passed ...   1\ntest-calloc-no-split             ........................ passed ...   1\ntest-calloc-split-one-block      ........................ passed ...   1\ntest-calloc-split-first          ........................ passed ...   1\ntest-calloc-split-last           ........................ passed ...   1\ntest-calloc-split-middle         ........................ passed ...   1\ntest-calloc-split-vector         ........................ passed ...   2\ntest-calloc-coalesce             ........................ passed ...   2\ntest-calloc-coalesce-big         ........................ passed ...   2\ntest-realloc-no-preallocate      ........................ passed ...   1\ntest-realloc-preallocate         ........................ passed ...   1\ntest-realloc-arrays              ........................ passed ...   3\ntest-realloc-block-reuse         ........................ passed ...   3\ntest-realloc-expand-block        ........................ passed ...   2\ntest-realloc-no-split            ........................ passed ...   3\ntest-realloc-split-one-block     ........................ passed ...   3\ntest-realloc-split-first         ........................ passed ...   3\ntest-realloc-split-last          ........................ passed ...   3\ntest-realloc-split-middle        ........................ passed ...   2\ntest-realloc-split-vector        ........................ passed ...   2\ntest-realloc-coalesce            ........................ passed ...   3\ntest-realloc-coalesce-big        ........................ passed ...   1\ntest-all                         ........................ passed ...   5\n\nGrade                            .................................. 9.00\n")),(0,n.kt)("h3",{id:"debugging"},"Debugging"),(0,n.kt)("p",null,(0,n.kt)("inlineCode",{parentName:"p"},"checker.py")," uses ",(0,n.kt)("inlineCode",{parentName:"p"},"ltrace")," to capture all the libcalls and syscalls performed."),(0,n.kt)("p",null,"The output of ",(0,n.kt)("inlineCode",{parentName:"p"},"ltrace")," is formatted to show only top level library calls and nested system calls.\nFor consistency, the heap start and addresses returned by ",(0,n.kt)("inlineCode",{parentName:"p"},"mmap()")," are replaced with labels.\nEvery other address is displayed as ",(0,n.kt)("inlineCode",{parentName:"p"},"<label> + offset"),", where the label is the closest mapped address."),(0,n.kt)("p",null,"To run a single test use ",(0,n.kt)("inlineCode",{parentName:"p"},"checker.py <test>"),", where ",(0,n.kt)("inlineCode",{parentName:"p"},"<test>")," is the name of the test without path or extension.\nAppend ",(0,n.kt)("inlineCode",{parentName:"p"},"-v")," to see the diff between ",(0,n.kt)("inlineCode",{parentName:"p"},"out/<test>.out")," and ",(0,n.kt)("inlineCode",{parentName:"p"},"ref/<test>.ref"),"."),(0,n.kt)("pre",null,(0,n.kt)("code",{parentName:"pre",className:"language-console"},"student@os:~/.../assignments/mem-alloc/tests$ python checker.py test-malloc-split-one-block -v\ntest-malloc-split-one-block      ........................ failed ...   0\n--- out/test-malloc-split-one-block.out\n+++ ref/test-malloc-split-one-block.ref\n@@ -1,4 +1,23 @@\n-os_malloc (['131040'])                                                                    = 0\n-os_free (['0'])                                                                           = <void>\n-DBG: os_malloc returned NULL on valid size\n-+++ exited (status 6) +++\n+os_malloc (['131040'])                                                                    = HeapStart + 0x18\n+  brk (['0'])                                                                             = HeapStart + 0x0\n+  brk (['HeapStart + 0x20000'])                                                           = HeapStart + 0x20000\n+os_free (['HeapStart + 0x18'])                                                            = <void>\n+os_malloc (['65536'])                                                                     = HeapStart + 0x18\n+os_malloc (['32768'])                                                                     = HeapStart + 0x10030\n+os_malloc (['16384'])                                                                     = HeapStart + 0x18048\n+os_malloc (['8192'])                                                                      = HeapStart + 0x1c060\n+os_malloc (['4096'])                                                                      = HeapStart + 0x1e078\n+os_malloc (['2048'])                                                                      = HeapStart + 0x1f090\n+os_malloc (['1024'])                                                                      = HeapStart + 0x1f8a8\n+os_malloc (['512'])                                                                       = HeapStart + 0x1fcc0\n+os_malloc (['256'])                                                                       = HeapStart + 0x1fed8\n+os_free (['HeapStart + 0x18'])                                                            = <void>\n+os_free (['HeapStart + 0x10030'])                                                         = <void>\n+os_free (['HeapStart + 0x18048'])                                                         = <void>\n+os_free (['HeapStart + 0x1c060'])                                                         = <void>\n+os_free (['HeapStart + 0x1e078'])                                                         = <void>\n+os_free (['HeapStart + 0x1f090'])                                                         = <void>\n+os_free (['HeapStart + 0x1f8a8'])                                                         = <void>\n+os_free (['HeapStart + 0x1fcc0'])                                                         = <void>\n+os_free (['HeapStart + 0x1fed8'])                                                         = <void>\n++++ exited (status 0) +++\n\n\nGrade                            .................................. 0.00\n")),(0,n.kt)("h2",{id:"resources"},"Resources"),(0,n.kt)("ul",null,(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("a",{parentName:"li",href:"https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf"},'"Implementing malloc" slides by Michael Saelee')),(0,n.kt)("li",{parentName:"ul"},(0,n.kt)("a",{parentName:"li",href:"https://danluu.com/malloc-tutorial/"},"Malloc Tutorial"))))}d.isMDXComponent=!0},8506:(e,t,a)=>{a.d(t,{Z:()=>l});const l=a.p+"assets/images/coalesce-blocks-d56dae67c5b407080ddab19c660ca56d.svg"},7565:(e,t,a)=>{a.d(t,{Z:()=>l});const l=a.p+"assets/images/memory-block-27bcad65f280db00766c7a9824c624f2.svg"},5019:(e,t,a)=>{a.d(t,{Z:()=>l});const l=a.p+"assets/images/split-block-0e690e7363ed4af850595e15c0f8cd7e.svg"}}]);