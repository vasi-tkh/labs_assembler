// .data
 //s: .string "%d "

.globl Task1_asm
.globl Task3_asm
.globl Task4_i_asm
.globl Task4_asm
.globl Task5_asm
.globl Task6_term
.globl Task6_two_sum
.globl Task6_asm

Task1_asm:

    sub $8, %rsp
    cmp $8, %ecx
    setae %al
    add $8, %rsp
    ret

Task3_asm:

    sub $8, %rsp
    #define mem_i (%rsp)

    movq %xmm0, %rcx

    cmp 7, %rcx
    ja greater

    mov %rcx, mem_i
    fldl mem_i
    fsin
    fstpl mem_i
    movq mem_i, %xmm0

    jmp end_check

    greater:
    movq 2, %xmm0

    end_check:
    #undef mem_i
    add $8, %rsp
    ret

Task4_i_asm:

    sub $16, %rsp

    #define I (%rsp)

    movq %rcx, I
    movq %rcx, %rax

    movq $2, %rcx
    movl $0, %edx
    idiv %rcx

    cmp $0, %edx
    je first_eq

    movq I, %rax
    movq $3, %rcx
    imul %rcx
    inc %rax

    first_eq:

    #undef I
    add $16, %rsp
    ret

Task4_asm:

    sub $16, %rsp
    #define N (%rsp)
    #define X 8(%rsp)

    movq %rbx, 8(%rsp)
    dec %rcx
    movq %rcx, N
    movq %rdx, %rax
    movq $0, %rbx

    begin_iteration:

    cmp %rbx, N
    je end_loop

    movq %rax, X
    // lea s(%rdx), %rcx
    movq %rax, %rdx
    sub $32, %rsp
    call printf
    add $32, %rsp

    movq X, %rcx
    sub $32, %rsp
    call Task4_i_asm
    add $32, %rsp

    inc %rbx
    jmp begin_iteration

    end_loop:
    movq 8(%rsp), %rbx
    #undef N
    add $16, %rsp
    ret

Task5_asm:
    sub $8, %rsp

    movq %rcx, %rdi
    movq $0, %rcx
    movq $255, (%rdi,%rcx,4)
    movq $1, %rcx
    begin_iteration_5:

    cmp %rdx, %rcx
    je end_loop_5

    movq %rcx, %r8
    movq %rdx, %r9
    dec %rcx
    movq (%rdi, %rcx, 4), %rcx

    sub $32, %rsp
    call Task4_i_asm
    add $32, %rsp

    movq %r8, %rcx
    movq %r9, %rdx
    movq %rax, (%rdi, %rcx, 4)
    inc %rcx

    jmp begin_iteration_5

    end_loop_5:
    add $8, %rsp
    ret

Task6_term:

    sub $16, %rsp
    #define mem_i (%rsp)

    movq %rcx, mem_i
    movq %rcx, %rax

    movq $2, %rcx
    movl $0, %edx
    idiv %rcx

    fldl mem_i
    fldl 3
    fadd
    fldl 3
    fdiv

    cmp $0, %edx
    je plus

    fldz
    fsub

    plus:

    fstpl mem_i
    movq mem_i, %xmm0
    #undef mem_i
    add $16, %rsp
    ret


Task6_two_sum:

    sub $8, %rsp

    vaddpd %xmm1, %xmm0, %xmm2 // s  = a + b
    vsubpd %xmm0, %xmm2, %xmm3 // bs = s - a
    vsubpd %xmm3, %xmm2, %xmm4 // as = s - sb
    vsubpd %xmm3, %xmm1, %xmm1 // b - bs
    vsubpd %xmm4, %xmm0, %xmm0 // a - as
    vaddpd %xmm1, %xmm0, %xmm3 // (b - bs) + (a - as)
    vaddpd %xmm2, %xmm3, %xmm0 // s = s + (b - bs) + (a - as)

    add $8, %rsp
    ret


Task6_asm:

    sub $16, %rsp
    #define eps (%rsp)

    movq %xmm0, eps
    movq %rbx, 8(%rsp)

    movq $0, %rbx  // счетчик

    movq $0, %rcx
    movq %rcx, %xmm0 // i-ое слагаемое
    movq %rcx, %xmm1 // итоговая сумма

    begin_iteration_6:

    movq %rbx, %rcx
    sub $32, %rsp
    call Task6_term
    add $32, %rsp

    movq $10000000, %rdx

    vpabsd %xmm0, %xmm2
    movq %xmm2, %rcx
    cmp %rcx, eps
    jge end_loop_6

    vmovapd %xmm0, %xmm2
    vmovapd %xmm1, %xmm0
    vmovapd %xmm2, %xmm1

    sub $32, %rsp
    call Task6_two_sum
    add $32, %rsp

    vmovapd %xmm0, %xmm2
    vmovapd %xmm1, %xmm0
    vmovapd %xmm2, %xmm1

    inc %rbx
    jmp begin_iteration_6

    end_loop_6:

    vmovapd %xmm1, %xmm0

    movq 8(%rsp), %rbx
    #undef eps
    #undef term_i
    add $16, %rsp
    ret

