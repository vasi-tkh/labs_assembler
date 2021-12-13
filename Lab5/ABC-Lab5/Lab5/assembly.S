.globl Task4_asm_fpu
.globl Task6_asm

Task4_asm_fpu:

    sub $8, %rsp

    #define mem_i (%rsp)
    movq %xmm0, mem_i

    fld1            // загрузка единицы
    fldl mem_i      // загрузка x
    fprem           // получение дробной части x
    f2xm1           // 2^{x}-1
    fld1            // загрузка единицы
    fadd            // 2^{x}
    fxch            // теперь на вершине стека лежит единица
    fldl mem_i      // загрузка x
    fxch            // теперь на вершнине стека лежит единица
    fscale          // 1*2^[x]
    fxch            // теперь на вершине стека лежит x
    fstpl mem_i     // выгрузка x из стека
    fmul            // 2^[x]*2^{x}
    fld1            // загрузка единицы
    fsubr           // 2^x-1
    fldl mem_i      // загрузка x
    fld1            // загрузка единицы
    fadd            // 1+x
    fmul            // (2^x-1)*(1+x)
    fld1            // загрузка единицы
    fld1            // загрузка единицы
    fadd            // 1+1 = 2
    fmul            // 2*(2^x-1)*(1+x)
    fstpl mem_i
    movq mem_i, %xmm0

    #undef mem_i
    add $8, %rsp
    ret


Task6_asm:

    sub $16, %rsp

    #define mem_x (%rsp)
    #define mem_y 8(%rsp)
    movq %xmm0, mem_x
    movq %xmm1, mem_y

    // 4.6*x^y-1.3

    fldl mem_y      // загрузка y
    fldl mem_x      // загрузка x
    fyl2x           // y*log_2(x) <=> log_2(x^y)
    fstpl mem_x     // выгрузка значения из стека

    fld1            // загрузка единицы
    fldl mem_x      // загрузка log_2(x^y)
    fprem           // получение дробной части log_2(x^y)
    f2xm1           // 2^{log_2(x^y)}-1
    fld1            // загрузка единицы
    fadd            // 2^{log_2(x^y)}
    fxch            // теперь на вершине стека лежит единица
    fldl mem_x      // загрузка log_2(x^y)
    fxch            // теперь на вершине стека лежит единица
    fscale          // 1*2^[log_2(x^y)]
    fxch            // теперь на вершине стека лежит log_2(x^y)
    fstpl mem_x     // выгрузка x из стека
    fmul            // 2^[log_2(x^y)]*2^{log_2(x^y)} = 2^(log_2(x^y)) = x^y

    fldl 2          // загрузка 2
    fmul            // a*x^y
    fldl 3          // загрузка 3
    fsubr           // a*x^y-b

    fstpl mem_x
    movq mem_x, %xmm0

    #undef mem_x
    #undef mem_y
    add $16, %rsp
    ret

