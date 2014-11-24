	.file	"tp4_cpp.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z13nouveauCercle5Coordjj
	.type	_Z13nouveauCercle5Coordjj, @function
_Z13nouveauCercle5Coordjj:
.LFB1236:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1236
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$16, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -32(%rbp)
	movl	%esi, -20(%rbp)
	movl	%edx, -24(%rbp)
	movq	-32(%rbp), %r12
	movl	$40, %edi
.LEHB0:
	call	_Znwm
.LEHE0:
	movq	%rax, %rbx
	movl	-24(%rbp), %edx
	movl	-20(%rbp), %eax
	movl	%edx, %ecx
	movl	%eax, %edx
	movq	%r12, %rsi
	movq	%rbx, %rdi
.LEHB1:
	call	_ZN6CercleC1E5Coordjj
.LEHE1:
	movq	%rbx, %rax
	jmp	.L5
.L4:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r12, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume
.LEHE2:
.L5:
	addq	$16, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1236:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1236:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1236-.LLSDACSB1236
.LLSDACSB1236:
	.uleb128 .LEHB0-.LFB1236
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB1236
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L4-.LFB1236
	.uleb128 0
	.uleb128 .LEHB2-.LFB1236
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1236:
	.text
	.size	_Z13nouveauCercle5Coordjj, .-_Z13nouveauCercle5Coordjj
	.globl	_Z11faireDessinPP5Formej
	.type	_Z11faireDessinPP5Formej, @function
_Z11faireDessinPP5Formej:
.LFB1237:
	.cfi_startproc
	.cfi_personality 0x3,__gxx_personality_v0
	.cfi_lsda 0x3,.LLSDA1237
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r12
	pushq	%rbx
	subq	$32, %rsp
	.cfi_offset 12, -24
	.cfi_offset 3, -32
	movq	%rdi, -40(%rbp)
	movl	%esi, -44(%rbp)
	movl	$16, %edi
.LEHB3:
	call	_Znwm
.LEHE3:
	movq	%rax, %rbx
	movl	$0, %ecx
	movl	$480, %edx
	movl	$640, %esi
	movq	%rbx, %rdi
.LEHB4:
	call	_ZN7CanevasC1Ejjj
.LEHE4:
	movq	%rbx, -32(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L7
.L8:
	movl	-20(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
.LEHB5:
	call	_ZN7Canevas13dessinerFormeEP5Forme
	addl	$1, -20(%rbp)
.L7:
	movl	-20(%rbp), %eax
	cmpl	-44(%rbp), %eax
	jb	.L8
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_Z11ecrireFramePK7Canevas
	jmp	.L11
.L10:
	movq	%rax, %r12
	movq	%rbx, %rdi
	call	_ZdlPv
	movq	%r12, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume
.LEHE5:
.L11:
	addq	$32, %rsp
	popq	%rbx
	popq	%r12
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1237:
	.section	.gcc_except_table
.LLSDA1237:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1237-.LLSDACSB1237
.LLSDACSB1237:
	.uleb128 .LEHB3-.LFB1237
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB1237
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L10-.LFB1237
	.uleb128 0
	.uleb128 .LEHB5-.LFB1237
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE1237:
	.text
	.size	_Z11faireDessinPP5Formej, .-_Z11faireDessinPP5Formej
	.globl	_Z15desallouerFormeP5Forme
	.type	_Z15desallouerFormeP5Forme, @function
_Z15desallouerFormeP5Forme:
.LFB1238:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	cmpq	$0, -8(%rbp)
	je	.L12
	movq	-8(%rbp), %rax
	movq	(%rax), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rdx
	movq	%rdx, %rdi
	call	*%rax
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1238:
	.size	_Z15desallouerFormeP5Forme, .-_Z15desallouerFormeP5Forme
	.align 2
	.globl	_ZN7Canevas13dessinerFormeEP5Forme
	.type	_ZN7Canevas13dessinerFormeEP5Forme, @function
_ZN7Canevas13dessinerFormeEP5Forme:
.LFB1239:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	-16(%rbp), %rax
	movq	(%rax), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	-8(%rbp), %rcx
	movq	-16(%rbp), %rdx
	movq	%rcx, %rsi
	movq	%rdx, %rdi
	call	*%rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1239:
	.size	_ZN7Canevas13dessinerFormeEP5Forme, .-_ZN7Canevas13dessinerFormeEP5Forme
	.align 2
	.globl	_ZN7Canevas13assignerPixelEiij
	.type	_ZN7Canevas13assignerPixelEiij, @function
_ZN7Canevas13assignerPixelEiij:
.LFB1240:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	%esi, -12(%rbp)
	movl	%edx, -16(%rbp)
	movl	%ecx, -20(%rbp)
	movl	-12(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jae	.L16
	movl	-16(%rbp), %edx
	movq	-8(%rbp), %rax
	movl	8(%rax), %eax
	cmpl	%eax, %edx
	jae	.L16
	cmpl	$0, -12(%rbp)
	js	.L16
	cmpl	$0, -16(%rbp)
	jns	.L17
.L16:
	jmp	.L15
.L17:
	movq	-8(%rbp), %rax
	movq	(%rax), %rdx
	movq	-8(%rbp), %rax
	movl	8(%rax), %ecx
	movl	-16(%rbp), %eax
	imull	%eax, %ecx
	movl	-12(%rbp), %eax
	addl	%ecx, %eax
	movl	%eax, %eax
	salq	$2, %rax
	addq	%rax, %rdx
	movl	-20(%rbp), %eax
	movl	%eax, (%rdx)
.L15:
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1240:
	.size	_ZN7Canevas13assignerPixelEiij, .-_ZN7Canevas13assignerPixelEiij
	.align 2
	.globl	_ZN7Canevas13assignerPixelE5Coordj
	.type	_ZN7Canevas13assignerPixelE5Coordj, @function
_ZN7Canevas13assignerPixelE5Coordj:
.LFB1241:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$24, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -20(%rbp)
	movl	-12(%rbp), %edx
	movl	-16(%rbp), %esi
	movl	-20(%rbp), %ecx
	movq	-8(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN7Canevas13assignerPixelEiij
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1241:
	.size	_ZN7Canevas13assignerPixelE5Coordj, .-_ZN7Canevas13assignerPixelE5Coordj
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1246:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L20
	cmpl	$65535, -8(%rbp)
	jne	.L20
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L20:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1246:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z13nouveauCercle5Coordjj, @function
_GLOBAL__sub_I__Z13nouveauCercle5Coordjj:
.LFB1247:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1247:
	.size	_GLOBAL__sub_I__Z13nouveauCercle5Coordjj, .-_GLOBAL__sub_I__Z13nouveauCercle5Coordjj
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z13nouveauCercle5Coordjj
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.8.1 20130603 (Red Hat 4.8.1-1)"
	.section	.note.GNU-stack,"",@progbits
