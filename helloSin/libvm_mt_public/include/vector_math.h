// vector_math.h
/**
 * @Author      : jshen, longbiao  
 * @Date        : 2021-1-27  
 * @Tips        : ./bin/mkrename 16 32 'lvector double' 'lvector float' 'lvector signed int' 'lvector signed int' __MT3K_INTRIN   > vector_math.h  
 *
 * Vector Math - The MT3000 SIMD library for Evaluating Elementary Functions  
 * Vector Math - 为MT3000实现的向量SIMD基础数学库  
 *   
 *   
 * Vector Math函数库为MT3000实现了C99标准下定义的所有"实"浮点数学函数的向量版本,该库里面的所有函数会利用
 * MT3000中的SIMD指令进行基础函数计算.  
 *   
 *   
 * Vector Math函数库支持的浮点标准  
 * Vector Math函数库为C99标准下定义的实浮点数学函数均提供了单精度和双精度浮点版本  
 *   
 *   
 * Vector Math函数库的精度情况  
 * Vector Math函数库为C99标准下定义的数学函数均提供了最大误差1.0ulp的版本,并同时为大部分提供了最大
 * 误差3.5ulp的版本,为性能和精度提供不同的选择.精度越高性能越慢,反之亦然.  
 *   
 *   
 * Vector Math 在MT3000上不支持非规格数运算  
 * 0,由于MT3000的浮点部件不支持非规格数,所以Vector Math在MT3000上对非规格数有限,大部分函数不支持非规格数.  
 * 1,如果Vector Math函数的输入为非规格数,则Vector Math函数会将该输入视作符号相同的浮点零(+0.0或者-0.0).  
 * 2,如果Vector Math函数的结果理论值为非规格数,则Vector Math会将结果舍入为符号相等的浮点零(+0.0或者-0.0).  
 * 3,部分函数由于其运算的特殊性,可以准确的计算(符合函数的设计精度标准,即最大误差为1.0ulp或者3.5ulp)非规格数,其分别是: @todo : 待完善  
 * 4,具体情况会在下面各个函数API接口文档中说明.  
 *   
 *   
 * Vector Math使用的变量类型  
 * Vector Math函数库使用了MT3000 向量intrinsic中定义lvector double, lvector float, lvector signed int来分别
 * 进行双精度/单精度浮点运算,以及32bit大小的补码整数运算.并将这些变量类型作为函数输入类型和返回值类型.  
 * lvector double代表双精度浮点数double类型的向量版本,一个lvector double向量变量包含16个双精度浮点数.  
 * lvector float 代表单精度浮点数float类型的向量版本, 一个lvector float 向量变量包含32个单精度浮点数.  
 * lvector signed int代表32bits补码类型int的向量版本, 一个lvector signed int向量变量包含32个32bits补码值.  
 *   
 * 同时Vector Math函数库内定义了lvector_double2, lvector_float2两种特殊向量变量类型,lvector_double2包含了
 * 两个lvector double,而lvector_float2包含了两个lvector float.分别用于单双精度情况下有两个返回值的数学函数
 * 计算中,以同时返回该函数的两个计算结果.  
 *   
 *   
 * Vector Math实现的函数接口  
 * @todo : 待完善  
 *   
 * Vector Math函数库在MT3000中的错误处理  
 * Vector Math内函数在MT3000上不会对任何浮点错误进行异常处理,需要使用者检查结果自行捕获.  
 *   
 *    
 * Vector Math 函数库的函数命名规范说明( vm_xxx[d|f][16|32]_[u10|u35|u05] )  
 * 字符串"vm_"         : 代表该向量数学库vector math的缩写  
 * 字符串"xxx"         : 代表该向量函数对应的数学运算,比如sin  
 * 字符串"d"或者"f"    : 代表该函数是单精度(f)还是双精度(d)浮点操作  
 * 数字16或者32        : 代表该向量函数的向量单元中浮点数元素个数,单精度为32个,双精度为16个.  
 * 最后以_u开头的字符串 : 代表该函数的精度(ulp为单位),当前vector_math为math.h的函数都提供了1.0ulp(_u10)及
 *                       以上精度0.5ulp(_05)的版本,绝大部分还提供了3.5ulp(_u35)精度版本.   
*/



#ifndef __VECTOR_MATH_H
#define __VECTOR_MATH_H
#include <compiler/m3000.h>

/**
 * Vector Math函数库中为MT3000额外定义的向量变量类型
 *
 * lvector_double2类型用于存储两个lvector double变量,定义在vector_math.h中,其定义方式如下:
*/
typedef struct {
  lvector double x, y;
} lvector_double2;

/**
 * lvector_float2类型用于存储两个lvector float变量,定义在vector_math.h中,其定义方式如下:
*/
typedef struct {
  lvector float x, y;
} lvector_float2;


/**
 * \brief vecotr Math中为MT3000实现的向量数学函数  
*/

//Trigonometric Functions

/**
 *\brief 最大误差1.0ulp的双精度"向量"正弦函数(sin)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_sind16_u10(lvector double a);


/**
 *\brief 最大误差1.0ulp的双精度"向量"正弦函数(sin)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector float vm_sinf32_u10(lvector float a);


/**
 *\brief 最大误差3.5ulp的双精度"向量"正弦函数(sin)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_sind16_u35(lvector double a);


/**
 *\brief 最大误差3.5ulp的单精度"向量"正弦函数(sin)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector float vm_sinf32_u35(lvector float a);



/**
 * Vectorized double precision cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"余弦函数(cos)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_cosd16_u10(lvector double a);


/**
 * Vectorized single precision cose function with 1.0 ULP error bound
 *  最大误差1.0ulp的单精度"向量"余弦函数(cos)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector float vm_cosf32_u10(lvector float a);


/**
 * Vectorized double precision cose function with 3.5 ULP error bound
 *  最大误差3.5ulp的双精度"向量"余弦函数(cos)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_cosd16_u35(lvector double a);


/**
 * Vectorized single precision cose function with 3.5 ULP error bound
 *  最大误差3.5ulp的单精度"向量"余弦函数(cos)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector float vm_cosf32_u35(lvector float a);



/**
 * Vectorized double precision tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"正切函数(tan)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_tand16_u10(lvector double a);


/**
 * Vectorized float precision tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"正切函数(tan)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
 * @todo : 是否需要说明该函数在MT3000上出现的1.0ulp误差的问题.
*/
lvector float vm_tanf32_u10(lvector float a);


/**
 * Vectorized double precision tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"正切函数(tan)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
*/
lvector double vm_tand16_u35(lvector double a);


/**
 * Vectorized float precision tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"正切函数(tan)
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 对于NaN输入: 返回NaN
 * 对于Inf输入: 对于正负Inf值, 返回NaN
 * @todo : 是否需要说明该函数在MT3000上出现的1.0ulp误差的问题.
*/
lvector float vm_tanf32_u35(lvector float a);




/**
 * Vectorized double precision combined sine and cosine function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"正弦(sin)和 余弦(cos)组合函数
 * 
 * Evaluates the sine and cosine functions of a value in a at a time, and store the two \
 * values in x and y elements in the returned value, respectively. The error bound of the\
 * returned values is 1.0 ULP. If a is a NaN or infinity, a NaN is returned. 
 * 该函数同时计算向量变量a的sine操作与cose操作的结果,并把结果存储在lvector_double2类型变量的x与\
 * y元素中并返回结果.该函数的最大误差是1.0ulp,同时如果输入a是NaN或者infinity, 则会返回NaN.
*/
lvector_double2 vm_sincosd16_u10(lvector double a);
/**
 * Vectorized single precision combined sine and cosine function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"正弦(sin)和 余弦(cos)组合函数
 * 
 * Evaluates the sine and cosine functions of a value in a at a time, and store the two \
 * values in x and y elements in the returned value, respectively. The error bound of the\
 * returned values is 1.0 ULP. If a is a NaN or infinity, a NaN is returned. 
 * 该函数同时计算向量变量a的sine操作与cose操作的结果,并把结果存储在lvector_float2类型变量的x与\
 * y元素中并返回结果.该函数的最大误差是1.0ulp,同时如果输入a是NaN或者infinity, 则会返回NaN.
*/
lvector_float2 vm_sincosf32_u10(lvector float a);
/**
 * Vectorized double precision combined sine and cosine function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"正弦(sin)和 余弦(cos)组合函数
 * 
 * Evaluates the sine and cosine functions of a value in a at a time, and store the two \
 * values in x and y elements in the returned value, respectively. The error bound of the\
 * returned values is 3.5 ULP. If a is a NaN or infinity, a NaN is returned. 
 * 该函数同时计算向量变量a的sine操作与cose操作的结果,并把结果存储在lvector_double2类型变量的x与\
 * y元素中并返回结果.该函数的最大误差是3.5ulp,同时如果输入a是NaN或者infinity, 则会返回NaN.
*/
lvector_double2 vm_sincosd16_u35(lvector double a);
/**
 * Vectorized single precision combined sine and cosine function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"正弦(sin)和 余弦(cos)组合函数
 * 
 * Evaluates the sine and cosine functions of a value in a at a time, and store the two \
 * values in x and y elements in the returned value, respectively. The error bound of the\
 * returned values is 3.5 ULP. If a is a NaN or infinity, a NaN is returned. 
 * 该函数同时计算向量变量a的sine操作与cose操作的结果,并把结果存储在lvector_float2类型变量的x与\
 * y元素中并返回结果.该函数的最大误差是3.5ulp,同时如果输入a是NaN或者infinity, 则会返回NaN.
*/
lvector_float2 vm_sincosf32_u35(lvector float a) ;

/**
 * Vectorized double precision sine pi function with 0.506 ULP error bound, evaluate \
 * sin( πa ) for given a with 0.506 ULP error bound
 * 最大误差0.506ulp的双精度"向量"sine pi函数,该函数用于计算输入a的sin( πa )值.
*/
lvector double vm_sinpid16_u05(lvector double a);
/**
 * Vectorized single precision sine pi function with 0.506 ULP error bound, evaluate \
 * sin( πa ) for given a with 0.506 ULP error bound
 * 最大误差0.506ulp的单精度"向量"sine pi函数,该函数用于计算输入a的sin( πa )值.
*/
lvector float vm_sinpif32_u05(lvector float a);

/**
 * Vectorized double precision cose pi function with 0.506 ULP error bound, evaluate \
 * cos( πa ) for given a with 0.506 ULP error bound
 * 最大误差0.506ulp的双精度"向量"cose pi函数,该函数用于计算输入a的cos( πa )值.
*/
lvector double vm_cospid16_u05(lvector double a);
/**
 * Vectorized single precision cose pi function with 0.506 ULP error bound, evaluate \
 * cos( πa ) for given a with 0.506 ULP error bound
 * 最大误差0.506ulp的单精度"向量"cose pi函数,该函数用于计算输入a的cos( πa )值.
*/
lvector float vm_cospif32_u05(lvector float a);

/**
 * Vectorized double precision combined sine and cosine function with 0.506 ULP error bound,\
 *  evaluate sin( πa ) and cos( πa ) for given a simultaneously with 0.506 ULP error bound
 * 最大误差0.506ulp的双精度"向量"sine和cose组合函数,该函数用于同时计算输入a的sin( πa ) and cos( πa ) 的值.
*/
lvector_double2 vm_sincospid16_u05(lvector double a);
/**
 * Vectorized single precision combined sine and cosine function with 0.506 ULP error bound,\
 *  evaluate sin( πa ) and cos( πa ) for given a simultaneously with 0.506 ULP error bound
 * 最大误差0.506ulp的单精度"向量"sine和cose组合函数,该函数用于同时计算输入a的sin( πa ) and cos( πa ) 的值.
*/
lvector_float2 vm_sincospif32_u05(lvector float a);
/**
 * Vectorized double precision combined sine and cosine function with 3.5 ULP error bound,\
 *  evaluate sin( πa ) and cos( πa ) for given a simultaneously with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"sine和cose组合函数,该函数用于同时计算输入a的sin( πa ) and cos( πa ) 的值.
*/
lvector_double2 vm_sincospid16_u35(lvector double a);
/**
 * Vectorized single precision combined sine and cosine function with 3.5 ULP error bound,\
 *  evaluate sin( πa ) and cos( πa ) for given a simultaneously with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"sine和cose组合函数,该函数用于同时计算输入a的sin( πa ) and cos( πa ) 的值.
*/
lvector_float2 vm_sincospif32_u35(lvector float a);



//Inverse Trigonometric Functions
//反三角函数
/**
 * Vectorized double precision arc sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反正弦函数(arch sin).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector double vm_asind16_u10(lvector double a);


/**
 * Vectorized single precision arc sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"反正弦函数(arch sin).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector float vm_asinf32_u10(lvector float a);


/**
 * Vectorized double precision arc sine function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"反正弦函数(arch sin).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector double vm_asind16_u35(lvector double a);


/**
 * Vectorized single precision arc sine function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"反正弦函数(arch sin).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector float vm_asinf32_u35(lvector float a);



/**
 * Vectorized double precision arc cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反余弦函数(arch cos).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector double vm_acosd16_u10(lvector double a);


/**
 * Vectorized single precision arc cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"反余弦函数(arch cos).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector float vm_acosf32_u10(lvector float a);


/**
 * Vectorized double precision arc cose function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"反余弦函数(arch cos).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector double vm_acosd16_u35(lvector double a);


/**
 * Vectorized single precision arc cose function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"反余弦函数(arch cos).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入
 * 输入为NaN   : 返回NaN
 * 输入为+-0.0 : 返回+-0.0
 * 输入在[-1.0, +1.0]之外:返回NaN
*/
lvector float vm_acosf32_u35(lvector float a);



/**
 * Vectorized double precision arc tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反正切函数(arch tan).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN     : 返回NaN
 * 输入为+-0.0   : 返回+-0.0
 * 输入在为+-Inf : 返回+pi/2 或者 -pi/2 (@todo : 待确认)
*/
lvector double vm_atand16_u10(lvector double a);


/**
 * Vectorized single precision arc tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"反正切函数(arch tan).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN     : 返回NaN
 * 输入为+-0.0   : 返回+-0.0
 * 输入在为+-Inf : 返回+pi/2 或者 -pi/2 (@todo : 待确认)
*/
lvector float vm_atanf32_u10(lvector float a);


/**
 * Vectorized double precision arc tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"反正切函数(arch tan).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN     : 返回NaN
 * 输入为+-0.0   : 返回+-0.0
 * 输入在为+-Inf : 返回+pi/2 或者 -pi/2 (@todo : 待确认)
*/
lvector double vm_atand16_u35(lvector double a);


/**
 * Vectorized single precision arc tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"反正切函数(arch tan).
 *
 * 对于非规格数输入:该函数可以正确处理非规格数的输入(@todo : 待修复代码)
 * 输入为NaN     : 返回NaN
 * 输入为+-0.0   : 返回+-0.0
 * 输入在为+-Inf : 返回+pi/2 或者 -pi/2 (@todo : 待确认)
*/
lvector float vm_atanf32_u35(lvector float a);



/**
 * Vectorized double precision arc tangent function of two variables with 1.0 ULP error bound,\
 * This functions evaluates the arc tangent function of (y / x). 
 * 最大误差1.0ulp的双精度"向量"反正切函数(arch tan).该函数针对输入x和y,计算(y / x)值的反正切函数(arch tan)结果
*/
lvector double vm_atan2d16_u10(lvector double y, lvector double x);
/**
 * Vectorized single precision arc tangent function of two variables with 1.0 ULP error bound,\
 * This functions evaluates the arc tangent function of (y / x). 
 * 最大误差1.0ulp的单精度"向量"反正切函数(arch tan).该函数针对输入x和y,计算(y / x)值的反正切函数(arch tan)结果
*/
lvector float vm_atan2f32_u10(lvector float y, lvector float x);
/**
 * Vectorized double precision arc tangent function of two variables with 3.5 ULP error bound,\
 * This functions evaluates the arc tangent function of (y / x). 
 * 最大误差3.5ulp的双精度"向量"反正切函数(arch tan).该函数针对输入x和y,计算(y / x)值的反正切函数(arch tan)结果
*/
lvector double vm_atan2d16_u35(lvector double y, lvector double x);
/**
 * Vectorized single precision arc tangent function of two variables with 3.5 ULP error bound,\
 * This functions evaluates the arc tangent function of (y / x). 
 * 最大误差3.5ulp的单精度"向量"反正切函数(arch tan).该函数针对输入x和y,计算(y / x)值的反正切函数(arch tan)结果
*/
lvector float vm_atan2f32_u35(lvector float y, lvector float x);

//Hyperbolic functions and inverse hyperbolic functions

/**
 * Vectorized double precision hyperbolic sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"双曲正弦函数
*/
lvector double vm_sinhd16_u10(lvector double a);
/**
 * Vectorized single precision hyperbolic sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"双曲正弦函数
*/
lvector float vm_sinhf32_u10(lvector float a);
/**
 * Vectorized double precision hyperbolic sine function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"双曲正弦函数
*/
lvector double vm_sinhd16_u35(lvector double a);
/**
 * Vectorized single precision hyperbolic sine function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"双曲正弦函数
*/
lvector float vm_sinhf32_u35(lvector float a);

/**
 * Vectorized double precision hyperbolic cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"双曲余弦函数
*/
lvector double vm_coshd16_u10(lvector double a);
/**
 * Vectorized single precision hyperbolic cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"双曲余弦函数
*/
lvector float vm_coshf32_u10(lvector float a);
/**
 * Vectorized double precision hyperbolic cose function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"双曲余弦函数
*/
lvector double vm_coshd16_u35(lvector double a);
/**
 * Vectorized single precision hyperbolic cose function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"双曲余弦函数
*/
lvector float vm_coshf32_u35(lvector float a);

/**
 * Vectorized double precision hyperbolic tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"双曲正切函数
*/
lvector double vm_tanhd16_u10(lvector double a);
/**
 * Vectorized single precision hyperbolic tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"双曲正切函数
*/
lvector float vm_tanhf32_u10(lvector float a);
/**
 * Vectorized double precision hyperbolic tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"双曲正切函数
*/
lvector double vm_tanhd16_u35(lvector double a);
/**
 * Vectorized single precision hyperbolic tangent function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"双曲正切函数
*/
lvector float vm_tanhf32_u35(lvector float a);


/**
 * Vectorized double precision inverse hyperbolic sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反双曲正弦函数
*/
lvector double vm_asinhd16_u10(lvector double a);
/**
 * Vectorized single precision inverse hyperbolic sine function with 1.0 ULP error bound
 * 最大误差1.0ulp的d单精度"向量"反双曲正弦函数
*/
lvector float vm_asinhf32_u10(lvector float a);
/**
 * Vectorized double precision inverse hyperbolic cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反双曲余弦函数
*/
lvector double vm_acoshd16_u10(lvector double a);
/**
 * Vectorized single precision inverse hyperbolic cose function with 1.0 ULP error bound
 * 最大误差1.0ulp的d单精度"向量"反双曲余弦函数
*/
lvector float vm_acoshf32_u10(lvector float a);
/**
 * Vectorized double precision inverse hyperbolic tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"反双曲正切函数
*/
lvector double vm_atanhd16_u10(lvector double a);
/**
 * Vectorized single precision inverse hyperbolic tangent function with 1.0 ULP error bound
 * 最大误差1.0ulp的d单精度"向量"反双曲正切函数
*/
lvector float vm_atanhf32_u10(lvector float a);


//Power, exponential, and logarithmic functions
/**
 * Vectorized double precision natural logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"对数函数(log)
 * 
 * 输入正非规格数 : -Inf
 * 输入为NaN     : 返回NaN
 * 输入为1.0     : 返回+0.0
 * 输入为+Inf    : 返回+Inf
 * 输入为+-0     : -HUGE_VAL @todo : 待确认
 * 输入为负数    : 返回Nan
*/
lvector double vm_logd16_u10(lvector double a);
/**
 * Vectorized float precision natural logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"对数函数(log)
 * 
 * 输入正非规格数 : -Inf
 * 输入为NaN     : 返回NaN
 * 输入为1.0     : 返回+0.0
 * 输入为+Inf    : 返回+Inf
 * 输入为+-0     : -HUGE_VALF @todo : 待确认
 * 输入为负数    : 返回Nan
*/
lvector float vm_logf32_u10(lvector float a);
/**
 * Vectorized double precision natural logarithmic function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"对数函数(log)
 * 
 * 输入正非规格数 : -Inf
 * 输入为NaN     : 返回NaN
 * 输入为1.0     : 返回+0.0
 * 输入为+Inf    : 返回+Inf
 * 输入为+-0     : -HUGE_VAL @todo : 待确认
 * 输入为负数    : 返回NaN
*/
lvector double vm_logd16_u35(lvector double a);
/**
 * Vectorized float precision natural logarithmic function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"对数函数(log)
 * 
 * 输入正非规格数 : -Inf
 * 输入为NaN     : 返回NaN
 * 输入为1.0     : 返回+0.0
 * 输入为+Inf    : 返回+Inf
 * 输入为+-0     : -HUGE_VAL @todo : 待确认
 * 输入为负数    : 返回NaN
*/
lvector float vm_logf32_u35(lvector float a);


/**
 * Vectorized double precision base-10 logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"对数函数(log),该对数函数(log)以10为底数.
*/
lvector double vm_log10d16_u10(lvector double a);
/**
 * Vectorized single precision base-10 logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"对数函数(log),该对数函数(log)以10为底数.
*/
lvector float vm_log10f32_u10(lvector float a);
/**
 * Vectorized double precision base-2 logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"对数函数(log),该对数函数(log)以2为底数.
*/
lvector double vm_log2d16_u10(lvector double a);
/**
 * Vectorized single precision base-2 logarithmic function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"对数函数(log),该对数函数(log)以2为底数.
*/
lvector float vm_log2f32_u10(lvector float a);
/**
 * Vectorized double precision logarithm of one plus argument with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度向量对数函数(log),该函数计算输入a + 1.0的对数函数(log)结果.
*/
lvector double vm_log1pd16_u10(lvector double a);
/**
 * Vectorized single precision logarithm of one plus argument with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度向量对数函数(log),该函数计算输入a + 1.0的对数函数(log)结果.
*/
lvector float vm_log1pf32_u10(lvector float a);


/**
 * Vectorized double precision base-e exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"指数函数(exp), 该函数以自然对数e为底数.
 * 
 * 输入为非规格数 :
 * 输入为[-7.444401e+02, -7.083964e+02]之间的值:由于理论结果为"非规格数",所以返回+0.0 @todo : 待核实
 * 输入NaN       : 返回NaN
 * 输入为+Inf    : 返回+Inf
 * 输入为-Inf    : 返回+0.0
 * 结果underflow : 返回+0.0
 * 结果overlow   : 返回+Inf @todo : 待确认
*/
lvector double vm_expd16_u10(lvector double a);
/**
 * Vectorized single precision base-e exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"指数函数(exp), 该函数以自然对数e为底数.
 * 
 * 输入为非规格数 :
 * 输入为[-103.278929903, -87.3365448704]之间的值:由于理论结果为"非规格数",所以返回+0.0 @todo : 待核实
 * 输入NaN       : 返回NaN
 * 输入为+Inf    : 返回+Inf
 * 输入为-Inf    : 返回+0.0
 * 结果underflow : 返回+0.0
 * 结果overlow   : 返回+Inf @todo : 待确认
*/
lvector float vm_expf32_u10(lvector float a);
/**
 * Vectorized double precision base-2 exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"指数函数(exp), 该函数以2为底数.
*/
lvector double vm_exp2d16_u10(lvector double a);
/**
 * Vectorized single precision base-2 exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"指数函数(exp), 该函数以2为底数.
*/
lvector float vm_exp2f32_u10(lvector float a);
/**
 * Vectorized double precision base-10 exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"指数函数(exp), 该函数以10为底数.
*/
lvector double vm_exp10d16_u10(lvector double a);
/**
 * Vectorized single precision base-10 exponential function function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"指数函数(exp), 该函数以10为底数.
*/
lvector float vm_exp10f32_u10(lvector float a);
/**
 * Vectorized double precision base-e exponential function minus 1 with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"指数函数(exp), 该函数以自然对数e为底数,并将结果减去1.0
*/
lvector double vm_expm1d16_u10(lvector double a);
/**
 * Vectorized single precision base-e exponential function minus 1 with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"指数函数(exp), 该函数以自然对数e为底数,并将结果减去1.0
*/
lvector float vm_expm1f32_u10(lvector float a);

/**
 * Vectorized double precision square root function with 0.5001 ULP error bound
 * 最大误差0.5001ulp的双精度"向量"求平方根函数
*/
lvector double vm_sqrtd16(lvector double a);
/**
 * Vectorized single precision square root function with 0.5001 ULP error bound
 * 最大误差0.5001ulp的单精度"向量"求平方根函数
*/
lvector float vm_sqrtf32(lvector float a);
/**
 * Vectorized double precision square root function with 0.5001 ULP error bound
 * 最大误差0.5001ulp的双精度"向量"求平方根函数
*/
lvector double vm_sqrtd16_u05(lvector double a);
/**
 * Vectorized single precision square root function with 0.5001 ULP error bound
 * 最大误差0.5001ulp的单精度"向量"求平方根函数
*/
lvector float vm_sqrtf32_u05(lvector float a);
/**
 * Vectorized double precision square root function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"求平方根函数
*/
lvector double vm_sqrtd16_u35(lvector double a);
/**
 * Vectorized single precision square root function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"求平方根函数
*/
lvector float vm_sqrtf32_u35(lvector float a);

/**
 * Vectorized double precision cubic root function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"求立方根函数
*/
lvector double vm_cbrtd16_u10(lvector double a);
/**
 * Vectorized single precision cubic root function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"求立方根函数
*/
lvector float vm_cbrtf32_u10(lvector float a);
/**
 * Vectorized double precision cubic root function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量"求立方根函数
*/
lvector double vm_cbrtd16_u35(lvector double a);
/**
 * Vectorized single precision cubic root function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量"求立方根函数
*/
lvector float vm_cbrtf32_u35(lvector float a);

/**
 * Vectorized double precision 2D Euclidian distance function with 0.5 ULP error bound
 * 最大误差0.5ulp的双精度"向量" 2D Euclidian distance函数
*/
lvector double vm_hypotd16_u05(lvector double, lvector double);
/**
 * Vectorized single precision 2D Euclidian distance function with 0.5 ULP error bound
 * 最大误差0.5ulp的单精度"向量" 2D Euclidian distance函数
*/
lvector float vm_hypotf32_u05(lvector float, lvector float);
/**
 * Vectorized double precision 2D Euclidian distance function with 3.5 ULP error bound
 * 最大误差3.5ulp的双精度"向量" 2D Euclidian distance函数
*/
lvector double vm_hypotd16_u35(lvector double, lvector double);
/**
 * Vectorized single precision 2D Euclidian distance function with 3.5 ULP error bound
 * 最大误差3.5ulp的单精度"向量" 2D Euclidian distance函数
*/
lvector float vm_hypotf32_u35(lvector float, lvector float);

/**
 * Vectorized double precision power function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"power函数
*/
lvector double vm_powd16_u10(lvector double, lvector double);
/**
 * Vectorized float precision power function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"power函数
*/
lvector float vm_powf32_u10(lvector float, lvector float);


//Error and gamma functions
/**
 * Vectorized double precision log gamma function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"log gamma函数
*/
lvector double vm_lgammad16_u10(lvector double a);
/**
 * Vectorized single precision log gamma function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"log gamma函数
*/
lvector float vm_lgammaf32_u10(lvector float a);
/**
 * Vectorized double precision gamma function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"gamma函数
*/
lvector double vm_tgammad16_u10(lvector double a);
/**
 * Vectorized single precision gamma function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"gamma函数
*/
lvector float vm_tgammaf32_u10(lvector float a);

/**
 * Vectorized double precision error function with 1.0 ULP error bound
 * 最大误差1.0ulp的双精度"向量"error函数
*/
lvector double vm_erfd16_u10(lvector double a);
/**
 * Vectorized single precision error function with 1.0 ULP error bound
 * 最大误差1.0ulp的单精度"向量"error函数
*/
lvector float vm_erff32_u10(lvector float a);
/**
 * Vectorized double precision  complementary error function with 1.5 ULP error bound
 * 最大误差1.5ulp的双精度"向量"complementary error函数
*/
lvector double vm_erfcd16_u15(lvector double a);
/**
 * Vectorized single precision  complementary error function with 1.5 ULP error bound
 * 最大误差1.5ulp的单精度"向量"complementary error函数
*/
lvector float vm_erfcf32_u15(lvector float a);

//Nearest integer functions
/**
 * Vectorized double precision function for rounding to integer towards zero
 * 最大误差0.5ulp的双精度向量浮点舍入函数,该函数使用向零舍入模式将浮点数a舍入到最近的"浮点整数".
*/
lvector double vm_truncd16(lvector double a);
/**
 * Vectorized single precision function for rounding to integer towards zero
 * 最大误差0.5ulp的单精度向量浮点舍入函数,该函数使用向零舍入模式将浮点数a舍入到最近的"浮点整数".
*/
lvector float vm_truncf32(lvector float a);
/**
 * Vectorized double precision function for rounding to integer towards negative infinity
 * 最大误差0.5ulp的双精度向量浮点舍入函数,该函数使用向负无穷大舍入模式将浮点数a舍入到最近的"浮点整数".
*/
lvector double vm_floord16(lvector double a);
/**
 * Vectorized single precision function for rounding to integer towards negative infinity
 * 最大误差0.5ulp的单精度向量浮点舍入函数,该函数使用向负无穷大舍入模式将浮点数a舍入到最近的"浮点整数".
*/
lvector float vm_floorf32(lvector float a);
/**
 * Vectorized double precision function for rounding to integer towards positive infinity
 * 最大误差0.5ulp的双精度向量浮点舍入函数,该函数使用向正无穷大舍入模式将浮点数a舍入到最近的"浮点整数"..
*/
lvector double vm_ceild16(lvector double a);
/**
 * Vectorized single precision function for rounding to integer towards positive infinity
 * 最大误差0.5ulp的单精度向量浮点舍入函数,该函数使用向正无穷大舍入模式将浮点数a舍入到最近的"浮点整数".
*/
lvector float vm_ceilf32(lvector float a);

/**
 * Vectorized double precision function for rounding to nearest integer,  round to integer away from zero
 * 最大误差0.5ulp的双精度向量浮点舍入函数,该函数使用最近舍入模式(偏向无穷大).
*/
lvector double vm_roundd16(lvector double a);
/**
 * Vectorized single precision function for rounding to nearest integer,  round to integer away from zero\
 * 最大误差0.5ulp的单精度向量浮点舍入函数,该函数使用最近舍入模式(偏向无穷大).
*/
lvector float vm_roundf32(lvector float a);
/**
 * Vectorized double precision function for rounding to nearest integer, round to integer, ties round to even
 * 最大误差0.5ulp的双精度向量浮点舍入函数,该函数使用最近舍入模式(偏向偶数).
*/
lvector double vm_rintd16(lvector double a);
/**
 * Vectorized single precision function for rounding to nearest integer, round to integer, ties round to even
 * 最大误差0.5ulp的单精度向量浮点舍入函数,该函数使用最近舍入模式(偏向偶数).
*/
lvector float vm_rintf32(lvector float a);

//Other Base functions
/**
 * Vectorized double precision function for fused multiply-accumulation
 * 完全舍入(最大误差0.5ulp)的双精度"向量"乘加运算
*/
lvector double vm_fmad16(lvector double a, lvector double b, lvector double c);
/**
 * Vectorized single precision function for fused multiply-accumulation
 * 完全舍入(最大误差0.5ulp)的单精度"向量"乘加运算
*/
lvector float vm_fmaf32(lvector float a, lvector float b, lvector float c);

/**
 * Vectorized double precision FP remainder
 * 完全舍入(最大误差0.5ulp)的单精度"向量"求余数运算
*/
lvector double vm_fmodd16(lvector double a, lvector double b);
/**
 * Vectorized double precision FP remainder
 * 完全舍入(最大误差0.5ulp)的单精度"向量"求余数运算
*/
lvector float vm_fmodf32(lvector float a, lvector float b);

/**
 * Vectorized double precision function for multiplying by integral power of 2
 * (This math operation only double precision version in vector math)
 * 完全舍入(最大误差0.5ulp)的双精度"向量"乘2次幂函数,该函数会将a乘以2的b次幂.
 * (该函数只有双精度版本)
*/
lvector double vm_ldexpd16(lvector double a, lvector signed int b);
/**
 * Vectorized double precision function for obtaining fractional component of an FP number
 * 完全舍入(最大误差0.5ulp)的双精度"向量"浮点数求尾数函数,该函数求单精度浮点数的尾数部分
*/
lvector double vm_frfrexpd16(lvector double a);
/**
 * Vectorized single precision function for obtaining fractional component of an FP number
 * 完全舍入(最大误差0.5ulp)的单精度"向量"浮点数求尾数函数,该函数求单精度浮点数的尾数部分
*/
lvector float vm_frfrexpf32(lvector float a);
/**
 * Vectorized double precision function for obtaining fractional component of an FP number
 * (This math operation only double precision version in vector math)
 * 完全舍入(最大误差0.5ulp)的双精度"向量"浮点数求指数函数,该函数求单精度浮点数的指数部分
 * (该函数只有双精度版本)
*/
lvector signed int vm_expfrexpd16(lvector double a);
/**
 * Vectorized double precision function for getting integer exponent
 * (This math operation only double precision version in vector math)
 * 双精度"向量"浮点数求"整数"指数函数,该函数求单精度浮点数的指数部分,并以整数返回.
 * (该函数只有双精度版本)
*/
lvector signed int vm_ilogbd16(lvector double a);
/**
 * Vectorized double precision signed integral and fractional values
 * 双精度"向量"浮点数拆分函数,该函数将浮点数a的整数部分和小数部分分别存放在lvector_double2类型的x和y元素中.
*/
lvector_double2 vm_modfd16(lvector double a);
/**
 * Vectorized single precision signed integral and fractional values
 * 单精度"向量"浮点数拆分函数,该函数将浮点数a的整数部分和小数部分分别存放在lvector_float2类型的x和y元素中.
*/
lvector_float2 vm_modff32(lvector float a);
/**
 * Vectorized double precision function for calculating the absolute value
 * 双精度"向量"浮点绝对值函数
*/
lvector double  vm_fabsd16(lvector double a);
/**
 * Vectorized single precision function for calculating the absolute value
 * 单精度"向量"浮点绝对值函数
*/
lvector float vm_fabsf32(lvector float a);
/**
 * Vectorized double precision function for determining maximum of two values
 * 双精度"向量"求最大值函数,该函数求向量a与向量b各对元素的最大值.
*/
lvector double  vm_fmaxd16(lvector double a, lvector double b);
/**
 * Vectorized single precision function for determining maximum of two values
 * 单精度"向量"求最大值函数,该函数求向量a与向量b各对元素的最大值.
*/
lvector float vm_fmaxf32(lvector float a, lvector float b);
/**
 * Vectorized double precision function for determining minimum of two values
 * 双精度"向量"求最小值函数,该函数求向量a与向量b各对元素的最小值.
*/
lvector double  vm_fmind16(lvector double a, lvector double b);
/**
 * Vectorized single precision function for determining minimum of two values
 * 单精度"向量"求最小值函数,该函数求向量a与向量b各对元素的最小值.
*/
lvector float vm_fminf32(lvector float a, lvector float b);
/**
 * Vectorized double precision function to calculate positive difference of two values
 * 双精度"向量"求"正"差值函数,该函数返回a - b的差值, 如果a < b, 则返回0.0;
*/
lvector double  vm_fdimd16(lvector double a, lvector double b);
/**
 * Vectorized single precision function to calculate positive difference of two values
 * 单精度"向量"求"正"差值函数,该函数返回a - b的差值, 如果a < b, 则返回0.0;
*/
lvector float vm_fdimf32(lvector float a, lvector float b);
/**
 * Vectorized double precision function for copying signs
 * 双精度"向量"浮点数符号复制函数,该函数将b的符号复制给a并返回.
*/
lvector double  vm_copysignd16(lvector double a, lvector double b);
/**
 * Vectorized single precision function for copying signs
 * 单精度"向量"浮点数符号复制函数,该函数将b的符号复制给a并返回.
*/
lvector float vm_copysignf32(lvector float a, lvector float b);
/**
 * Vectorized double precision function for obtaining the next representable FP value
 * 双精度"向量"nextafter函数,该函数返回参数a在参赛b方向下的最近的浮点数
*/
lvector double  vm_nextafterd16(lvector double a, lvector double b);
/**
 * Vectorized single precision function for obtaining the next representable FP value
 * 单精度"向量"nextafter函数,该函数返回参数a在参赛b方向下的最近的浮点数
*/
lvector float vm_nextafterf32(lvector float a, lvector float b);

/**
 * 双精度向量浮点除法函数，该函数计算lvector double向量类型变量a和b中的对应的每个浮点元素
 * ai和bi的除法值（ai/bi）,并将结果存储于lvector double变量中返回。
*/
lvector double vm_fdivd16(lvector double a, lvector double b);
/**
 * 单精度向量浮点除法函数，该函数计算lvector float向量类型变量a和b中的对应的每个浮点元素
 * ai和bi的除法值（ai/bi）,并将结果存储于lvector float变量中返回。
*/
lvector float  vm_fdivf32(lvector float a, lvector float b);
/**
 * 双精度向量求倒数函数，该函数计算lvector double向量类型变量a每个元素的倒数值，
 * 并将结果存储于lvector double变量中返回。
*/
lvector double vm_frecd16(lvector double a);
/**
 * 单精度向量求倒数函数，该函数计算lvector float向量类型变量a每个元素的倒数值，
 * 并将结果存储于lvector float变量中返回。
*/
lvector float  vm_frecf32(lvector float a);

#endif
