(()=>{"use strict";var e,c,a,d,b={},f={};function t(e){var c=f[e];if(void 0!==c)return c.exports;var a=f[e]={id:e,loaded:!1,exports:{}};return b[e].call(a.exports,a,a.exports,t),a.loaded=!0,a.exports}t.m=b,t.c=f,e=[],t.O=(c,a,d,b)=>{if(!a){var f=1/0;for(i=0;i<e.length;i++){a=e[i][0],d=e[i][1],b=e[i][2];for(var r=!0,o=0;o<a.length;o++)(!1&b||f>=b)&&Object.keys(t.O).every((e=>t.O[e](a[o])))?a.splice(o--,1):(r=!1,b<f&&(f=b));if(r){e.splice(i--,1);var n=d();void 0!==n&&(c=n)}}return c}b=b||0;for(var i=e.length;i>0&&e[i-1][2]>b;i--)e[i]=e[i-1];e[i]=[a,d,b]},t.n=e=>{var c=e&&e.__esModule?()=>e.default:()=>e;return t.d(c,{a:c}),c},a=Object.getPrototypeOf?e=>Object.getPrototypeOf(e):e=>e.__proto__,t.t=function(e,d){if(1&d&&(e=this(e)),8&d)return e;if("object"==typeof e&&e){if(4&d&&e.__esModule)return e;if(16&d&&"function"==typeof e.then)return e}var b=Object.create(null);t.r(b);var f={};c=c||[null,a({}),a([]),a(a)];for(var r=2&d&&e;"object"==typeof r&&!~c.indexOf(r);r=a(r))Object.getOwnPropertyNames(r).forEach((c=>f[c]=()=>e[c]));return f.default=()=>e,t.d(b,f),b},t.d=(e,c)=>{for(var a in c)t.o(c,a)&&!t.o(e,a)&&Object.defineProperty(e,a,{enumerable:!0,get:c[a]})},t.f={},t.e=e=>Promise.all(Object.keys(t.f).reduce(((c,a)=>(t.f[a](e,c),c)),[])),t.u=e=>"assets/js/"+({13:"463aadd7",24:"6b326dfe",53:"935f2afb",180:"c7d5d005",213:"c92640ae",214:"03dc0c9b",373:"f808e6c0",488:"96a31749",556:"577dcf4c",675:"98c71577",820:"7f023807",842:"95637cbd",937:"4e29cae1",968:"62966fbb",983:"04d8a21d",1018:"0277d735",1101:"b407248a",1118:"fbc1cab8",1157:"91ac0728",1265:"f54b55c1",1329:"997e6ee2",1482:"c4d6228b",1487:"2330fd66",1625:"fbacb3d5",1746:"60905a9d",1758:"8de34314",1765:"374a2386",1771:"d2f41667",1786:"918b3e21",1901:"3c30233f",1967:"0fa0bebd",2055:"18331331",2202:"14ee73ae",2232:"e4b3f4c8",2279:"1dccb566",2417:"c2609098",2456:"ac5c3a27",2472:"d309dd16",2590:"bd909c58",2661:"2e030903",2713:"8f35a413",2736:"d2954435",2764:"1ef36804",2815:"0438abee",2827:"8ca589d3",2838:"6e6dee7f",2845:"2828cd91",3004:"f6eb4965",3063:"32839693",3068:"0c19000f",3085:"1f391b9e",3126:"e46ccb2a",3320:"a7bc80c4",3334:"eae0e5d1",3425:"a315d4d8",3470:"6e95b748",3540:"2c270c24",3675:"31a6b50d",3684:"5b1b8bbd",3711:"a8d01eab",3742:"68eeb637",3788:"a0ac5395",3807:"b95e0710",3851:"ab4aa734",3866:"fdef1607",3867:"4931bb70",3920:"d509b9f5",4006:"2bde47d5",4126:"487d1817",4148:"89d3ad7d",4207:"59897f9f",4222:"81b85611",4272:"1548d5c7",4346:"cc8fb1fa",4350:"692011d4",4379:"1ffc5c5f",4426:"5d7f8186",4461:"59ad4d8f",4470:"ade537b6",4823:"d754500f",4881:"3e3393a3",4980:"56fa2c9d",5139:"15f618ea",5220:"6e77dc18",5330:"34746f8c",5428:"0f51dda5",5430:"625a19b4",5468:"23c6ae47",5475:"7e98c1d8",5616:"1b1148a8",5737:"144ccec8",5782:"0275a3b2",5899:"232c749b",5935:"b672ac57",6074:"8209a29d",6078:"5ebe6805",6397:"65ab3714",6429:"62a2c47b",6492:"aecc3d85",6512:"94458749",6632:"14580385",6723:"8ec866b0",6901:"5e10bb01",7089:"924f80ad",7105:"97b00277",7156:"65687b6f",7327:"3e478533",7383:"ca6b73ec",7387:"d6e5c209",7414:"393be207",7674:"8d5b82ca",7841:"a191e07d",7914:"09e11287",7915:"1891e676",7918:"17896441",7986:"87bfa638",8028:"b5c587af",8211:"0f890721",8245:"4c341edc",8322:"5894dc17",8351:"392776e2",8411:"267b5415",8421:"23374ca6",8446:"e0921ae2",8448:"50ed9da3",8459:"5c4ba3bf",8482:"cbc996c5",8631:"007cf997",8650:"3e17b32d",8684:"f4dcab90",8788:"9f99d3fc",8986:"2641b427",9041:"0bbd68f9",9052:"ddc3a2ab",9085:"ce181f15",9095:"ce0d7f6c",9152:"1e0b7734",9158:"fe11e54c",9173:"70ad9ac2",9197:"e88d4a6f",9386:"fecbe7cc",9514:"1be78505",9667:"fc7881a9",9671:"35edd654",9701:"5b157b4b",9724:"4c165629",9735:"c54826dc",9796:"7931b02c",9817:"14eb3368",9836:"9dd394c3",9837:"092edce8",9856:"49cee3f0",9859:"432299a8",9944:"928d0c11",9984:"6bda9475",9995:"97fe4cb3"}[e]||e)+"."+{13:"f227cffd",24:"a9207055",53:"dcc6f105",180:"4295a694",213:"942b47a5",214:"7d3607c4",373:"054d8290",488:"e337e8cd",556:"8399c80e",675:"806d0cd6",820:"04c09cb0",842:"5e69ce03",937:"95c2c010",968:"608ba77b",983:"ee9af4c3",1018:"96866aa0",1101:"cebd5fa6",1118:"93b744eb",1157:"c043483e",1265:"c9eec9a8",1329:"3666967d",1482:"eb515b3b",1487:"f24739d8",1625:"f3ceda29",1746:"fece8761",1758:"5989243b",1765:"c24f096c",1771:"b53fe2d2",1786:"d9fee0be",1901:"2531d9e8",1967:"6e38b4aa",2055:"91bdb813",2202:"44cc7dcf",2232:"37954fa1",2279:"844a51d7",2417:"5c4fcba5",2456:"7c0d4cdc",2472:"cb661de9",2590:"77280f16",2661:"24cceee5",2666:"5efb0c03",2713:"e8431348",2736:"7edf666c",2764:"d55baee4",2815:"1cee93c1",2827:"b9a01bc8",2838:"850a0462",2845:"4412ab31",3004:"724ed3c9",3063:"af5f997f",3068:"96eec70c",3085:"b2d53f92",3126:"1c0fd27b",3320:"36b15a12",3334:"51e731a0",3425:"a74a4ed5",3470:"29381fcc",3540:"ea03ddad",3675:"34c43715",3684:"cd2743ae",3711:"25d8e5f0",3742:"aca19497",3788:"34da6531",3807:"62359ffb",3851:"f2cd2d59",3866:"979503a4",3867:"a7093604",3920:"e61f68be",4006:"7c4f99e7",4126:"d1e79b73",4148:"31e21bfa",4207:"4221ff56",4222:"13076fd9",4272:"ba6382a8",4346:"8c6ac66f",4350:"da0af264",4379:"92135108",4426:"6be57b8f",4461:"846c9990",4470:"52ea304a",4823:"d78cb443",4881:"37340cbd",4972:"d4c24351",4980:"179eef05",5139:"a4903377",5220:"ca5d07c5",5330:"0dbb0a98",5428:"0eff0b7d",5430:"3e14fda0",5468:"aeac59d9",5475:"51e7b092",5616:"818b5c81",5737:"60730604",5782:"948d8261",5899:"f7dd1707",5935:"0bb691d4",6074:"434f1349",6078:"45b1b10c",6397:"50c161c8",6429:"608c0303",6492:"a39b36e9",6512:"84113fc6",6632:"ee864194",6723:"ae1b4a6e",6901:"c8129fb9",7089:"24154790",7105:"b0d4334f",7156:"f11c32fd",7327:"73ee8dac",7383:"474a2794",7387:"30f493af",7414:"9dc07f00",7674:"597a294c",7841:"f30a63da",7914:"d13e805a",7915:"2a33d06c",7918:"4e93f2ea",7986:"dda5b73c",8028:"60a01f2d",8211:"2afa16e4",8245:"b3fa5fb7",8322:"452bde70",8351:"ff1ae09c",8411:"d5f77dd9",8421:"da7d56b5",8446:"d57507eb",8448:"74793820",8459:"0649efc4",8482:"33d34c4c",8631:"f01bc2b9",8650:"539c4d59",8684:"6b2af1b1",8788:"d0696e1f",8986:"8d5055ba",9041:"2db91b91",9052:"46c293d7",9085:"04b392a7",9095:"3b4874c2",9152:"89d67324",9158:"8d449ffe",9173:"6bb0c0be",9197:"c45ba8d1",9386:"748bde0d",9514:"f8b9d3b1",9667:"701bfbfd",9671:"2d84ca74",9701:"ef9ed8a0",9724:"78111b20",9735:"4ad3505d",9796:"df80072f",9817:"f8efd3cc",9836:"841f945e",9837:"50dff18d",9856:"5998cd96",9859:"08512c81",9944:"10afb270",9984:"639ca4eb",9995:"d1e49386"}[e]+".js",t.miniCssF=e=>{},t.g=function(){if("object"==typeof globalThis)return globalThis;try{return this||new Function("return this")()}catch(e){if("object"==typeof window)return window}}(),t.o=(e,c)=>Object.prototype.hasOwnProperty.call(e,c),d={},t.l=(e,c,a,b)=>{if(d[e])d[e].push(c);else{var f,r;if(void 0!==a)for(var o=document.getElementsByTagName("script"),n=0;n<o.length;n++){var i=o[n];if(i.getAttribute("src")==e||i.getAttribute("data-webpack")=="so:"+a){f=i;break}}f||(r=!0,(f=document.createElement("script")).charset="utf-8",f.timeout=120,t.nc&&f.setAttribute("nonce",t.nc),f.setAttribute("data-webpack","so:"+a),f.src=e),d[e]=[c];var u=(c,a)=>{f.onerror=f.onload=null,clearTimeout(l);var b=d[e];if(delete d[e],f.parentNode&&f.parentNode.removeChild(f),b&&b.forEach((e=>e(a))),c)return c(a)},l=setTimeout(u.bind(null,void 0,{type:"timeout",target:f}),12e4);f.onerror=u.bind(null,f.onerror),f.onload=u.bind(null,f.onload),r&&document.head.appendChild(f)}},t.r=e=>{"undefined"!=typeof Symbol&&Symbol.toStringTag&&Object.defineProperty(e,Symbol.toStringTag,{value:"Module"}),Object.defineProperty(e,"__esModule",{value:!0})},t.p="/operating-systems/325/",t.gca=function(e){return e={14580385:"6632",17896441:"7918",18331331:"2055",32839693:"3063",94458749:"6512","463aadd7":"13","6b326dfe":"24","935f2afb":"53",c7d5d005:"180",c92640ae:"213","03dc0c9b":"214",f808e6c0:"373","96a31749":"488","577dcf4c":"556","98c71577":"675","7f023807":"820","95637cbd":"842","4e29cae1":"937","62966fbb":"968","04d8a21d":"983","0277d735":"1018",b407248a:"1101",fbc1cab8:"1118","91ac0728":"1157",f54b55c1:"1265","997e6ee2":"1329",c4d6228b:"1482","2330fd66":"1487",fbacb3d5:"1625","60905a9d":"1746","8de34314":"1758","374a2386":"1765",d2f41667:"1771","918b3e21":"1786","3c30233f":"1901","0fa0bebd":"1967","14ee73ae":"2202",e4b3f4c8:"2232","1dccb566":"2279",c2609098:"2417",ac5c3a27:"2456",d309dd16:"2472",bd909c58:"2590","2e030903":"2661","8f35a413":"2713",d2954435:"2736","1ef36804":"2764","0438abee":"2815","8ca589d3":"2827","6e6dee7f":"2838","2828cd91":"2845",f6eb4965:"3004","0c19000f":"3068","1f391b9e":"3085",e46ccb2a:"3126",a7bc80c4:"3320",eae0e5d1:"3334",a315d4d8:"3425","6e95b748":"3470","2c270c24":"3540","31a6b50d":"3675","5b1b8bbd":"3684",a8d01eab:"3711","68eeb637":"3742",a0ac5395:"3788",b95e0710:"3807",ab4aa734:"3851",fdef1607:"3866","4931bb70":"3867",d509b9f5:"3920","2bde47d5":"4006","487d1817":"4126","89d3ad7d":"4148","59897f9f":"4207","81b85611":"4222","1548d5c7":"4272",cc8fb1fa:"4346","692011d4":"4350","1ffc5c5f":"4379","5d7f8186":"4426","59ad4d8f":"4461",ade537b6:"4470",d754500f:"4823","3e3393a3":"4881","56fa2c9d":"4980","15f618ea":"5139","6e77dc18":"5220","34746f8c":"5330","0f51dda5":"5428","625a19b4":"5430","23c6ae47":"5468","7e98c1d8":"5475","1b1148a8":"5616","144ccec8":"5737","0275a3b2":"5782","232c749b":"5899",b672ac57:"5935","8209a29d":"6074","5ebe6805":"6078","65ab3714":"6397","62a2c47b":"6429",aecc3d85:"6492","8ec866b0":"6723","5e10bb01":"6901","924f80ad":"7089","97b00277":"7105","65687b6f":"7156","3e478533":"7327",ca6b73ec:"7383",d6e5c209:"7387","393be207":"7414","8d5b82ca":"7674",a191e07d:"7841","09e11287":"7914","1891e676":"7915","87bfa638":"7986",b5c587af:"8028","0f890721":"8211","4c341edc":"8245","5894dc17":"8322","392776e2":"8351","267b5415":"8411","23374ca6":"8421",e0921ae2:"8446","50ed9da3":"8448","5c4ba3bf":"8459",cbc996c5:"8482","007cf997":"8631","3e17b32d":"8650",f4dcab90:"8684","9f99d3fc":"8788","2641b427":"8986","0bbd68f9":"9041",ddc3a2ab:"9052",ce181f15:"9085",ce0d7f6c:"9095","1e0b7734":"9152",fe11e54c:"9158","70ad9ac2":"9173",e88d4a6f:"9197",fecbe7cc:"9386","1be78505":"9514",fc7881a9:"9667","35edd654":"9671","5b157b4b":"9701","4c165629":"9724",c54826dc:"9735","7931b02c":"9796","14eb3368":"9817","9dd394c3":"9836","092edce8":"9837","49cee3f0":"9856","432299a8":"9859","928d0c11":"9944","6bda9475":"9984","97fe4cb3":"9995"}[e]||e,t.p+t.u(e)},(()=>{var e={1303:0,532:0};t.f.j=(c,a)=>{var d=t.o(e,c)?e[c]:void 0;if(0!==d)if(d)a.push(d[2]);else if(/^(1303|532)$/.test(c))e[c]=0;else{var b=new Promise(((a,b)=>d=e[c]=[a,b]));a.push(d[2]=b);var f=t.p+t.u(c),r=new Error;t.l(f,(a=>{if(t.o(e,c)&&(0!==(d=e[c])&&(e[c]=void 0),d)){var b=a&&("load"===a.type?"missing":a.type),f=a&&a.target&&a.target.src;r.message="Loading chunk "+c+" failed.\n("+b+": "+f+")",r.name="ChunkLoadError",r.type=b,r.request=f,d[1](r)}}),"chunk-"+c,c)}},t.O.j=c=>0===e[c];var c=(c,a)=>{var d,b,f=a[0],r=a[1],o=a[2],n=0;if(f.some((c=>0!==e[c]))){for(d in r)t.o(r,d)&&(t.m[d]=r[d]);if(o)var i=o(t)}for(c&&c(a);n<f.length;n++)b=f[n],t.o(e,b)&&e[b]&&e[b][0](),e[b]=0;return t.O(i)},a=self.webpackChunkso=self.webpackChunkso||[];a.forEach(c.bind(null,0)),a.push=c.bind(null,a.push.bind(a))})()})();