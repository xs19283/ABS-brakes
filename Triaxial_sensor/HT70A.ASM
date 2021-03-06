; Generated by holtek-gcc v3.13, Thu Jul 19 22:38:34 2018
; 
; Configuration:
;       with long instruction
;       Multi-ROM, Multi-RAM
;       bits_per_rom_unit:16
;       with mp1
;       with tbhp, address(0x9)
;          Use tabrd-const
;       
; SFR address of long-instruction arch:
;    mp0 = -1,1,0
;    mp1 = 4,3,2
;    mp2 = 14,13,12
;    tbp = 9,7,8
;    acc = 5
;    pcl = 6
;    status = 10
;    bp = 11
;    intc = 48
;       
; use 'tabrdc' instead of 'tabrd'
;       

#pragma translator "holtek-gcc 4.6.4" "3.13" "build 20130711"
; Rebuild 26

ir equ [2]
mp equ [3]
sbp equ [4]
acc equ [5]
bp equ [11]
tblp equ [7]
tbhp equ [9]
status equ [10]
c equ [10].0
ac equ [10].1
z equ [10].2
ov equ [10].3
cz equ [10].6
sc equ [10].7
intc equ [48]

extern ra:byte
extern rb:byte
extern rc:byte
extern rd:byte
extern re:byte
extern rf:byte
extern rg:byte
extern rh:byte
extern _Crom2Prom:near
extern _Crom2PromNext:near
@HCCINIT	.section 'data'
@HCCINIT0	.section 'data'

#pragma debug scope 1 1
	extern __DELAY3:near
	extern __DELAYX3:near
	extern __DELAYX6:near
	extern __DELAYY5:near
	extern __DELAYY3:near
	extern _builtin_holtek_delay_2:byte
___pa equ [18]
public _Slave
#pragma debug scope 2 1
#line 33 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
_Slave .section 'code'
_Slave proc
_L2:
#line 36 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	snz [18].7
	jmp _L2
#line 37 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	mov a,[18]
	mov ra,a
_L4:
#line 38 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	snz [18].7
	jmp _L4
	jmp _L2
	ret
_Slave endp
#line 38 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
#pragma debug scope 1 1
___wdtc equ [62]
___pac equ [19]
___simc0 equ [108]
___simc2 equ [111]
___simd equ [110]
public _main
#pragma debug scope 3 1
#line 14 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
IFDEF WITH_DEFAULT_STARTUP
extern _main_initial0:near
extern _main_startup:near
ENDIF

ROMBANK 0 @start
@start .section com_l 'code'
_main_startup1:
@start .section com_e 'code'
	mov a,bank _main
	mov bp,a
	jmp _main

_main .section 'code'
_main proc
#line 16 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	mov a,175
	mov [62],a
#line 17 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	set [19].6
	set [19].7
	clr [19].5
#line 18 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	mov a,64
	mov [108],a
#line 19 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	mov a,32
	mov [111],a
#line 20 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	set [108].1
_L11:
#line 23 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	clr [111].1
#line 24 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	clr [110]
#line 25 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	sz [111].1
	jmp _L11
#line 26 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
	fcall _Slave
	jmp $
_main endp

@dummy proc
	call _main
@dummy endp

#line 26 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
#pragma debug scope 1 1
#pragma debug struct_begin 42 "__pa_bits"
#pragma debug field 21 8 0 1 "__pa0" ;0,1
#pragma debug field 21 8 0 1 "__pa1" ;1,1
#pragma debug field 21 8 0 1 "__pa2" ;2,1
#pragma debug field 21 8 0 1 "__pa3" ;3,1
#pragma debug field 21 8 0 1 "__pa4" ;4,1
#pragma debug field 21 8 0 1 "__pa5" ;5,1
#pragma debug field 21 8 0 1 "__pa6" ;6,1
#pragma debug field 21 8 0 1 "__pa7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 43 ""
#pragma debug field 2 42 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 43 1 ___pa "__pa" 1
#pragma debug struct_begin 44 "__pac_bits"
#pragma debug field 21 8 0 1 "__pac0" ;0,1
#pragma debug field 21 8 0 1 "__pac1" ;1,1
#pragma debug field 21 8 0 1 "__pac2" ;2,1
#pragma debug field 21 8 0 1 "__pac3" ;3,1
#pragma debug field 21 8 0 1 "__pac4" ;4,1
#pragma debug field 21 8 0 1 "__pac5" ;5,1
#pragma debug field 21 8 0 1 "__pac6" ;6,1
#pragma debug field 21 8 0 1 "__pac7" ;7,1
#pragma debug struct_end
#pragma debug union_begin 45 ""
#pragma debug field 2 44 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 45 1 ___pac "__pac" 1
#pragma debug struct_begin 46 "__wdtc_bits"
#pragma debug field 21 8 0 1 "__ws0" ;0,1
#pragma debug field 21 8 0 1 "__ws1" ;1,1
#pragma debug field 21 8 0 1 "__ws2" ;2,1
#pragma debug field 21 8 0 1 "__we0" ;3,1
#pragma debug field 21 8 0 1 "__we1" ;4,1
#pragma debug field 21 8 0 1 "__we2" ;5,1
#pragma debug field 21 8 0 1 "__we3" ;6,1
#pragma debug field 21 8 0 1 "__we4" ;7,1
#pragma debug struct_end
#pragma debug union_begin 47 ""
#pragma debug field 2 46 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 47 1 ___wdtc "__wdtc" 1
#pragma debug struct_begin 48 "__simc0_bits"
#pragma debug field 21 8 0 1 ;0,1
#pragma debug field 21 8 0 1 "__simen" ;1,1
#pragma debug field 21 8 0 1 "__simdeb0" ;2,1
#pragma debug field 21 8 0 1 "__simdeb1" ;3,1
#pragma debug field 21 8 0 1 ;4,1
#pragma debug field 21 8 0 1 "__sim0" ;5,1
#pragma debug field 21 8 0 1 "__sim1" ;6,1
#pragma debug field 21 8 0 1 "__sim2" ;7,1
#pragma debug struct_end
#pragma debug union_begin 49 ""
#pragma debug field 2 48 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 49 1 ___simc0 "__simc0" 1
#pragma debug variable 8 1 ___simd "__simd" 1
#pragma debug struct_begin 50 "__simc2_bits"
#pragma debug field 21 8 0 1 "__trf" ;0,1
#pragma debug field 21 8 0 1 "__wcol" ;1,1
#pragma debug field 21 8 0 1 "__csen" ;2,1
#pragma debug field 21 8 0 1 "__mls" ;3,1
#pragma debug field 21 8 0 1 "__ckeg" ;4,1
#pragma debug field 21 8 0 1 "__ckpolb" ;5,1
#pragma debug field 21 8 0 2 ;6,2
#pragma debug struct_end
#pragma debug union_begin 51 ""
#pragma debug field 2 50 "bits"
#pragma debug field 0 8 "byte"
#pragma debug union_end
#pragma debug variable 51 1 ___simc2 "__simc2" 1
IFDEF ISR_SYSTEM_STACK_BEFORE_2014_12_23
ELSE
ENDIF
#line 14 "D:\IIIT\Documents\HTK_Project\HT70A\HT70A.c"
@code .section at 0 'code'
	clr bp
	jmp _main_startup1


; 
; Generated by holtek-gcc v3.13, Thu Jul 19 22:38:34 2018
; Rebuild 26
; end of file
