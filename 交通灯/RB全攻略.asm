assume cs:code,ds:data,ss:stack
; 将标号所在段和一个段寄存器联系起来，否则编译的时候无法确定标号的
; 段地址在哪个寄存器，这种联系是编译器需要的
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

data segment
	num db 3fh,06h,5bh,4fh,66h,6dh,7dh,07h,7fh,6fh
data ends
; 用于数码管倒计时显示，这是数码管显示0-9 的段码，比如num[3] = 4FH 从C口输出
; 到数码管，数码管就会显示 3 《龙》
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

stack segment stack
	dw 64 dup(?)
stack ends
; 堆栈段，用于调用于保护寄存器，使得寄存器在被多次使用时造成数据丢失
; 尤其在子函数中具有极高的应用，栈是汇编语言 的支柱之一
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 代码段，传说中的主函数
code segment
start:
	mov ax,data	; 初始化数据段寄存器
	mov ds,ax	; 在display 函数中会用到num[bx]，这是必不可少的前提(龙)
	
	mov al,82h	; 初始化8255 B口输入，其它均为方式0和输出 
	out 63h,al	; 控制寄存器地址为63h 这是唐都仪器规定的
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; begin 这是主程序循环，为交通灯能够持续工作的动力来源
	begin:
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		in al,61h	; B口地址为61H 接受拨动开关的信息，送到AL，必须是AL
		; 在in 和 out 中，只能用AX或AL 来存放从端口中读入的数据或要发送到
		; 端口的数据。访问8位端口时用al,访问16位端口时用AX。
		mov bl,al
		; 把al 的值临时赋给bl，用来检测拨动开关K0是否被按下，如果按下的话
		; 即为1 这是要转向手动控制模式 《吴》
		and bl,01h
		;拨动开关如果为零则转向智能控制,否则手动控制
		jz code_smart	; z->zero 其实就是检测标志寄存器CF 是否为零
			call hand	; 调用hand 子函数 《吴》
			jmp short code_next
		code_smart:
			mov bx,0	; 将寄存器清零，因为event 函数中的时间时候bx dx
			mov dx,0	; 决定的,如果没有调用hand 函数的手动设置时间,必须清零《兰》
			call smart
		code_next:
	jmp begin
	
exit:
	nop
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称：手动控制台(吴稀钰)
; 参数：无
; 功能：实现完全手动控制灯亮灯灭和对灯亮时间进行调控
; 说明：K1为1时转向完全手动控制，即K7,K6,K5对L7,L6L5,L4
;		控制,K4,K3,K2 对L3,L2L1,L0 控制,K1为0时K7,K6,K5
; 		控制东西方向时间,k5=5s,k6=10s,k7=20S K4,k3,k2控制
;		南北方向时间,同东西方向.
; 注意：不完全手动控制将时间写入DX,BX调用event函数来实现
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
hand:
	push ax			; 
	push bx			;
	push dx			;将子函数中用到的寄存器全部入栈保护，别忘了出栈
	push cx			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	mov bl,al	; 判断K1 是否按下，如37行
	and bl,02h	;
	jz hand_s1	; 如果为零转向半自动手动控制时间, 否则完全手动控制，先看半自动控制的讲解
		hand_s1_s:			; 完全手动控制，看起来伸长的代码却没有什么技术含量
		
			push ax			; push pop 永远是一对
				mov al,0h	; 当用户调至完全手动控制第一件事情是什么？
				out 62h,al  ; 将倒计时失效,对62h 正是连接数码管的命脉，让它全部为0
			pop ax
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; 当bl = 1010 0000b 注意最左边3位，我们要在这一段最终完成
			;   bl = 1001 0000b 因为用K7 K6 K5 控制4个LED ,K6控制中间两个灯泡
			; 只需将第五位移到第四位，第六位复制移到第五位即可
			mov bl,al		; 为什么要赋给bl? 如果不明白就先看下面半自动的讲解
			and bl,0e0h		; e0h = ? 对 1110 0000b 显然是提取K7 K6 K5 的信息
			mov dl,bl		; 显然不能用bl 直接处理，如同mov bl,al 明白吧？
			and dl,20h		; 如果直接处理就会丢掉信息，这是干嘛？ 20H = 0010 0000b 提取K5信息
			shr dl,1		; 好吧dl 现在存的K5信息，为什么要右移一位？因为K5是控制L4 右转灯的
			or bl,dl		; 把dl 得到的K5信息放在bl 的第4位，因为bl 7、6、5才存有信息，当然第5位已经被提取到第4位
			and bl,0dfh		; dfh = 1101 1111b 为什么？ 因为要清除bl 第5位信息，别忘了它已经转移到了第4位
			mov dl,bl		; 把bl 继续暂存与dl
			and dl,40h		; 40h = 0100 0000h 单独提取出第6位信息
			shr dl,1		; 将第6位右移一位到了第5位
			or bl,dl		; 上面4步就是将bl 第6位复制一位移到第5位，我用最笨办法实现
			
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; 下面同上面，相信你可以搞定了
			mov bh,al
			and bh,01ch
			shr bh,1
			mov dl,bh
			and dl,02h
			shr dl,1
			or bh,dl
			and bh,0fdh
			mov dl,bh
			and dl,04h
			shr dl,1
			or bh,dl
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; 将处理好的开关信息从端口60H 输出即A口
			push ax
				mov al,0
				or al,bh
				or al,bl
				not al
				out 60h,al
			pop ax
			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			; 最后不要忘了检查开关状态是否改变
			in al,61h
			mov bl,al
			and bl,02h
			jz hand_next
			mov bl,al
			and bl,01h
			jz hand_next
		jmp hand_s1_s
	hand_s1:			; 半自动手动控制时间
		mov bl,al		
		; 看又用bl 来暂存al 的值，因为al 为B口拨动开关的信息，所以不能改变，下面可能还要用
		and bl,0e0h		; e0h = 1110 0000b 对 先来处理 K7、K6、K5 开关的值，即东西方向时间
		mov cl,5		; 1110 0000b 向右移5位等于多少？ 0000 00111 这样直接乘以5就可以得到时间
		shr bl,cl		; 可以shr bl,1 ，但如果移位 > 1 必须用CL
		push ax			; 保护ax,因为乘法mul 必须要用AX
			mov al,bl	; 上面把处理好的值赋给al
			mov bl,5	; 请参看mul 指令规则，不能mul 5 所以你将知道为什么要这样
			mul bl		; mul bl 就相当于 ax = al*bl
			mov bh,al	; 把相乘得到的值赋给bh 
			shr al,1	; 右移一位相当于除以二 5/2 = 2
			mov bl,al	; 把除以2 得到的结果赋给bl 
		pop ax			; push pop 永远是一对存在
		; 不要忘记半自动控制的任务，将拨动开关调节的时间计算出来赋给bx,dx
		; bl 为东西方向的左转灯需要增加的时间,bh为直行绿灯需要增加的时间
		; 我们规定左转绿灯增加的时间永远是直行绿灯的一半，因为99%情况下直行
		; 的车要比左转车多很多 下面当然就是要处理 K4 K3 K2 得到数值，相信你可以搞定
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		
		mov dl,al
		and dl,01ch
		mov cl,2
		shr dl,cl
		push ax
			mov al,dl
			mov dl,5
			mul dl
			mov dh,al
			shr al,1
			mov dl,al
		pop ax
		; 这是你已经完成了半自动调节的时间的所有任务，你把计算的到的时间
		; 放在了BX,DX寄存器中，在没有恢复之前别忘了调用兰奇的event 函数
		; 去把这些信息显示出来
		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		call event
	hand_next:
		nop
hand_ret:		; 我习惯将 hand_ret 和hand 配合使用,看起来程序清晰，这只是我个人习惯
	pop cx		; 注意出栈顺序和ret ，下同
	pop dx		; call 指令为将当前IP 或 CS和IP压入栈 再转移
	pop bx		; RET 指令恢复IP call 和 ret 配合使用构成了汇编的子程序
	pop ax		;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称：智能控制台()
; 功能：扩展接口，以便以后对增加的设备近视智能化控制
;		提高效率,留有7个拨动控制开关，扩展余地丰富
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
smart:
	push ax
	mov al,0h
	out 60h,al
	nop
smart_ret:
	pop ax
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称：事件-红绿灯工作一个周期当做一个事件(兰奇)
; 参数: bl,bh,dl,dh
; 功能：由bl,bh控制东西方向时间, dl,dh控制南北方向
;       默认时间为左转25 直行40, 由8255端口A输出控制
;		LED 灯显示
; 注意：调用之前如果不是手动设置，则必须清零
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
event:			; 关于函数一些东西请看上面hand 函数
	push ax
	push cx
	push bx
	push dx
	push di
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 如果你还不知道bl, bh, dl, dh 含义敬请看上面的上面的上面
	add bl,10	; 这是初始化时间，知道为什么加么
	add bh,20	; 因为吴稀钰那边可能已经将时间处理好放在了BX,DX
	add dl,10	; 不管她处理没有，你这都得加个初始化时间对吧
	add dh,20	; 凡事不能总靠别人，如果她没给你处理，岂不交通灯是0秒
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 初始化时间
	mov ax,0	; 为什么要初始化时间？这主要是给龙毅的display 函数所用
	add al,bh	; 因为我们之前用的是换一次绿灯倒计时一次，有点乱，所以
	add al,bl	; 我们要显示个总时间，总时间怎么得到？就在这里，放在哪里？
	add al,14	; 放在一个很少被用的寄存器里我们最终选用di，10秒？有个共用十秒噢。
	mov di,ax	; 看。。。。。。
	
	; 直行灯亮
	mov al,8eh	; 8eh = ? 1000 11110b 什么意思？东西方向直行灯亮，中间那两个，右转当然灯都亮。
	out 60h,al	; 将亮灯情况从A端口送出
	mov cl,bh	; bh 是啥来着？ 哦，吴稀钰处理好的东西直行时间和我原有的那30秒
	call delay	; 魏强只管cl 里面有多少时间，你cl = 多少，我就延迟几秒
	
	; 直行左转共亮10秒
	mov al,0eh	; 何为共亮？ 呵呵。。。。 同上
	out 60h,al
	mov cl,7
	call delay
	
	; 直行绿灯闪烁
	push cx		; 在闪烁三次时候别忘了保存CX ，PUSH POP 永远是一对
		mov cx,3
		event_s1:
			dec di			; 闪烁就是 亮一下 不亮一下，对吧，你懂得
			; 为什么要di 减一？别忘了魏强只管调用人家的 delay 和delay1s 时才负责减一这些活儿
			mov al,6eh		; 6eh = 0110 1110b
			out 60h,al
			call delay500ms
			mov al,0eh		; 0eh = 0000 1110b 看上面有什么不同？明白了吧..
			out 60h,al	
			call delay500ms
		loop event_s1
	pop cx
	
	; 直行黄灯亮2秒
	mov al,04eh  ; 0100 1110
	out 60h,al
	mov cl,2
	call delay
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 恭喜，你已经具有了独立分析问题的能力，下面我就不管了
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
	; 左转灯亮
	sub bl,3
	mov al,6eh
	out 60h,al
	mov cl,bl
	call delay
	; 左转绿灯闪烁
	push cx
		mov cx,3
		event_s2:
			dec di
			mov al,0eeh
			out 60h,al
			call delay500ms
			mov al,6eh
			out 60h,al
			call delay500ms
		loop event_s2
	pop cx
	
	; 左转黄灯亮2秒
	mov al,0aeh  ;1010 1110
	out 60h,al
	mov cl,2
	call delay
	
	; 同上
	; 初始化时间
	mov ax,0
	add al,dh
	add al,dl
	add al,14
	mov di,ax
	
	; 直行灯亮
	mov al,0e8h
	out 60h,al
	mov cl,dh
	call delay
	
	; 直行左转共亮10秒
	mov al,0e0h
	out 60h,al
	mov cl,7
	call delay
	; 直行绿灯闪烁
	push cx
		mov cx,3
		event_s3:
			dec di
			mov al,0e6h
			out 60h,al
			call delay500ms
			mov al,0e0h
			out 60h,al
			call delay500ms
		loop event_s3
	pop cx
	; 直行黄灯亮2秒
	mov al,0e4h 
	out 60h,al
	mov cl,2
	call delay
	; 左转灯亮
	sub dl,3
	mov al,0e6h
	out 60h,al
	mov cl,dl
	call delay
	
	; 左转绿灯闪烁
	push cx
		mov cx,3
		event_s4:
			dec di
			mov al,0eeh
			out 60h,al
			call delay500ms
			mov al,0e6h
			out 60h,al
			call delay500ms
		loop event_s4
	pop cx
	
	; 左转黄灯亮2秒
	mov al,0eah 
	out 60h,al
	mov cl,2
	call delay
	
event_ret:
	pop di
	pop dx
	pop bx
	pop cx
	pop ax
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称：数码管显示(龙毅)
; 参数: di,配合ds:num[bx] 中的数码管数码使用
; 功能: 用两个7段数码管显示di中的数字
; 注意：需调用30ms延时和 用到8255端口A中0和4引脚循环
;		选通两个数码管,利用大约15ms 视觉暂留实现显示
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
display:	; 虽然这个函数短小，但精炼，也是咱们最具技术含量的子函数
	push bx
	push ax
	push dx
	
	mov dx,ax
	mov ax,di
	
	mov bl,10			; 为什么？
	div bl				; div 是什么，呵呵，你懂了，如果不知道，就看上面的上面的上面
	; 对，我们已经将ax 中的数字分离出来了，十位个位数，个位数不就是10的余数么，在ah 中呢
	push ax		; ax 数据入栈保护
		mov al,dl	; 为什么？别忘了上面的交换，在数码管片选的时候不要忘记它借用的A端口的引脚
		or al,01h	; 先把0 引脚对应的右边数码管屏蔽掉
		out 60h,al	; 从A端口输出
	pop ax
	
	mov bh,0	
	mov bl,al		; 你应该懂得，al 存有要显示的十进制数字
	mov al,num[bx]	; 直接调用num[] 数组显示，别忘了看下24和25行
	out 62h,al		; 数码管连接的C端口
	call delay10ms	; 嗯 超短的10ms 延时
	; 如果老师问，为什么不把数组写到子函数里面？说实话，我试了，会出现点麻烦
	; 得了，懒得改了，我还是对直接放到顶端比较熟练
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 下同
	mov al,dl
	or al,10h
	out 60h,al
	mov bh,0
	mov bl,ah
	mov al,num[bx]
	out 62h,al
	call delay10ms
display_ret:
	pop dx
	pop ax
	pop bx
	ret
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;	魏强
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称：延时函数
; 参数: cl
; 功能：延时cl 秒
; 注意：程序模拟延时,不精确,可实现10分钟内
;		精确显示和delay1s 配合使用
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay:	; 先看hand 子函数中的一些注意事项，包括子函数入栈
	push cx
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 强哥，你这四个延时函数，真霸气
	; 因为咱们规定只用cl 来显示时间，所以把ch = 0是个相当好的习惯
	; loop 指令知道吧，就是cx 等于多少就循环几次
	mov ch,0
	delay_s1:
		call delay1s	; 对，如果cl = 5 就调用5次一秒，所以变成5秒了，对吧
	loop delay_s1
delay_ret:
	pop cx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称: 延时1秒子程序
; 功能: 配合display 还是和delay30ms可
;		完成数码管显示
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay1s:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	; 这里为什么要出来个di，是这样的，兰奇那边会统计下要允许通行的总时间
	; 他把这个总时间存在了di 中，至于为什么，你得问他，至少说明这个di 已经被
	; 他占用了，龙毅的display 是通过你的延时函数来调用的，总得有个沟通的桥梁
	; 别忘了他的倒计时的就是总时间，而每一秒都是在你这儿实现的，所以通过你这座
	; 桥梁来实现倒计时是再适合不过的选择，而这个di 正是兰奇给你的，而你得
	; 负责每秒后都减一
	cmp di,0	; 还记得栈溢出么，这里变成0一定得判断下，如果继续减就会出事
	je delay1s_next	; cmp = compare 比较di,0 如果di 为0 就转到 delay1s_next 不减了
		dec di
	delay1s_next:
	; 一秒 = 1000ms = 500ms + 500ms 对吧
	call delay500ms
	call delay500ms
delay1s_ret:
	ret
	
delay500ms:
	push cx
	
	mov cx,25	; 循环25次
	delay500ms_s1:
		call display ; 龙毅这小子的函数里面要调用两次你的delay10ms 这不正好20ms 20*25=？ 明白了吧
	loop delay500ms_s1
delay500ms_ret:
	pop cx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 名称: 10ms延迟，专供display 显示所需
; 功能：判断是否完全手动控制被按下
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay10ms:
	push cx
	push ax
	push bx
	mov cx,560	; 这个数字是通过实验得出的
	delay10ms_s1:	; 原本计划延迟么就一个空函数让他延就好了，正是加入了这么一段
					; 整整节省了一个 8259 这里面是个判断语句，老师问你，你就说我给你加的就好了
		in al,61h	; 从B 口读出拨动开关的状态
		mov bl,al	; 至少我已经养成了不直接用al 的习惯，汗
		and bl,03h
		cmp bl,3	; 如果是完全手动状态，直接跳到程序开始执行，即start
		jne delay10ms_next
			mov sp,80h	; 把汇编程序跳到开始执行大不了就一个恢复堆栈指针sp,看程序开始64*2=128 = 80h
			mov ax,stack	; 嗯恢复栈的段寄存器
			mov ss,ax
			jmp start		; 嗯跳出去
		delay10ms_next:
	loop delay10ms_s1
delay10ms_ret:
	pop bx
	pop ax
	pop cx
	ret
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
code ends
end start